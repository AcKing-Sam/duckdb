import os
import re
import json

aggregate_functions = ['algebraic', 'distributive']
scalar_functions = ['bit', 'blob', 'date', 'enum', 'generic', 'list', 'map', 'math', 'operators', 'random', 'string', 'struct', 'union']

header = '''//===----------------------------------------------------------------------===//
//                         DuckDB
//
// {HEADER}_functions.hpp
//
//
//===----------------------------------------------------------------------===//
// This file is generated by scripts/generate_functions.py

#pragma once

#include "duckdb/function/function_set.hpp"

namespace duckdb {

'''

footer = '''} // namespace duckdb
'''

def normalize_path_separators(x):
    return os.path.sep.join(x.split('/'))

def legal_struct_name(name):
    return name.isalnum()

def get_struct_name(function_name):
    return function_name.replace('_', ' ').title().replace(' ', '') + 'Fun'

def sanitize_string(text):
    return text.replace('"', '\\"')

all_function_types = []
all_function_types += [f'aggregate/{x}' for x in aggregate_functions]
all_function_types += [f'scalar/{x}' for x in scalar_functions]

function_type_set = {}
all_function_list = []
for path in all_function_types:
    header_path = normalize_path_separators(f'extension/core_functions/include/{path}_functions.hpp')
    json_path = normalize_path_separators(f'extension/core_functions/{path}/functions.json')
    with open(json_path, 'r') as f:
        parsed_json = json.load(f)
    new_text = header.replace('{HEADER}', path)
    for entry in parsed_json:
        function_text = ''
        if 'struct' in entry:
            struct_name = entry['struct']
        else:
            struct_name = get_struct_name(entry['name'])
        if not legal_struct_name(struct_name):
            print(f'Struct name {struct_name} is not a valid struct name!')
            exit(1)
        if struct_name in function_type_set:
            raise Exception("Duplicate entry " + struct_name)
        function_type_set[struct_name] = entry['type']
        if entry['type'] == 'scalar_function':
            function_text = 'static ScalarFunction GetFunction();'
            all_function_list.append([entry['name'], f"DUCKDB_SCALAR_FUNCTION({struct_name})"])
        elif entry['type'] == 'scalar_function_set':
            function_text = 'static ScalarFunctionSet GetFunctions();'
            all_function_list.append([entry['name'], f"DUCKDB_SCALAR_FUNCTION_SET({struct_name})"])
        elif entry['type'] == 'aggregate_function':
            function_text = 'static AggregateFunction GetFunction();'
            all_function_list.append([entry['name'], f"DUCKDB_AGGREGATE_FUNCTION({struct_name})"])
        elif entry['type'] == 'aggregate_function_set':
            function_text = 'static AggregateFunctionSet GetFunctions();'
            all_function_list.append([entry['name'], f"DUCKDB_AGGREGATE_FUNCTION_SET({struct_name})"])
        else:
            print("Unknown entry type " + entry['type'] + ' for entry ' + struct_name)
            exit(1)
        new_text += '''struct {STRUCT} {
	static constexpr const char *Name = "{NAME}";
	static constexpr const char *Parameters = "{PARAMETERS}";
	static constexpr const char *Description = "{DESCRIPTION}";
	static constexpr const char *Example = "{EXAMPLE}";

	{FUNCTION}
};

'''.replace('{STRUCT}', struct_name).replace('{NAME}', entry['name']).replace('{PARAMETERS}', entry['parameters'] if 'parameters' in entry else '').replace('{DESCRIPTION}', sanitize_string(entry['description'])).replace('{EXAMPLE}', sanitize_string(entry['example'])).replace('{FUNCTION}', function_text)
        alias_count = 1
        if 'aliases' in entry:
            for alias in entry['aliases']:
                alias_struct_name = get_struct_name(alias)
                if not legal_struct_name(alias_struct_name):
                    alias_struct_name = struct_name + 'Alias'
                    if alias_count > 1:
                        alias_struct_name += str(alias_count)
                    alias_count += 1

                aliased_type = entry['type']
                if aliased_type == 'scalar_function':
                    all_function_list.append([alias, f"DUCKDB_SCALAR_FUNCTION_ALIAS({alias_struct_name})"])
                elif aliased_type == 'scalar_function_set':
                    all_function_list.append([alias, f"DUCKDB_SCALAR_FUNCTION_SET_ALIAS({alias_struct_name})"])
                elif aliased_type == 'aggregate_function':
                    all_function_list.append([alias, f"DUCKDB_AGGREGATE_FUNCTION_ALIAS({alias_struct_name})"])
                elif aliased_type == 'aggregate_function_set':
                    all_function_list.append([alias, f"DUCKDB_AGGREGATE_FUNCTION_SET_ALIAS({alias_struct_name})"])
                else:
                    print("Unknown entry type " + aliased_type + ' for entry ' + struct_name)
                    exit(1)
                function_type_set[alias_struct_name] = aliased_type
                new_text += '''struct {STRUCT} {
	using ALIAS = {ALIAS};

	static constexpr const char *Name = "{NAME}";
};

'''.replace('{STRUCT}', alias_struct_name).replace('{NAME}', alias).replace('{ALIAS}', struct_name)
    new_text += footer
    with open(header_path, 'w+') as f:
        f.write(new_text)

function_list_file = normalize_path_separators('extension/core_functions/function_list.cpp')
with open(function_list_file, 'r') as f:
    text = f.read()

static_function = 'static StaticFunctionDefinition internal_functions[] = {'
pos = text.find(static_function)
header = text[:pos]
footer_lines = text[pos:].split('\n')
footer = ''
for i in range(len(footer_lines)):
    if len(footer_lines[i]) == 0:
        footer = '\n'.join(footer_lines[i:])
        break

new_text = header
new_text += static_function + '\n'
all_function_list = sorted(all_function_list, key=lambda x: x[0])
for entry in all_function_list:
    new_text += '\t' + entry[1] + ',\n'
new_text += '\tFINAL_FUNCTION\n};\n'
new_text += footer

with open(function_list_file, 'w+') as f:
    f.write(new_text)
