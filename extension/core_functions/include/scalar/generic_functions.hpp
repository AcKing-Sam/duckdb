//===----------------------------------------------------------------------===//
//                         DuckDB
//
// scalar/generic_functions.hpp
//
//
//===----------------------------------------------------------------------===//
// This file is generated by scripts/generate_functions.py

#pragma once

#include "duckdb/function/function_set.hpp"

namespace duckdb {

struct AliasFun {
	static constexpr const char *Name = "alias";
	static constexpr const char *Parameters = "expr";
	static constexpr const char *Description = "Returns the name of a given expression";
	static constexpr const char *Example = "alias(42 + 1)";

	static ScalarFunction GetFunction();
};

struct CurrentSettingFun {
	static constexpr const char *Name = "current_setting";
	static constexpr const char *Parameters = "setting_name";
	static constexpr const char *Description = "Return the current value of the configuration setting";
	static constexpr const char *Example = "current_setting('access_mode')";

	static ScalarFunction GetFunction();
};

struct ErrorFun {
	static constexpr const char *Name = "error";
	static constexpr const char *Parameters = "message";
	static constexpr const char *Description = "Throws the given error message";
	static constexpr const char *Example = "error('access_mode')";

	static ScalarFunction GetFunction();
};

struct HashFun {
	static constexpr const char *Name = "hash";
	static constexpr const char *Parameters = "param";
	static constexpr const char *Description =
	    "Returns an integer with the hash of the value. Note that this is not a cryptographic hash.";
	static constexpr const char *Example = "hash('🦆')";

	static ScalarFunction GetFunction();
};

struct LeastFun {
	static constexpr const char *Name = "least";
	static constexpr const char *Parameters = "arg1, arg2, ...";
	static constexpr const char *Description = "Returns the lowest value of the set of input parameters.";
	static constexpr const char *Example = "least(42, 84)";

	static ScalarFunctionSet GetFunctions();
};

struct GreatestFun {
	static constexpr const char *Name = "greatest";
	static constexpr const char *Parameters = "arg1, arg2, ...";
	static constexpr const char *Description = "Returns the highest value of the set of input parameters.";
	static constexpr const char *Example = "greatest(42, 84)";

	static ScalarFunctionSet GetFunctions();
};

struct StatsFun {
	static constexpr const char *Name = "stats";
	static constexpr const char *Parameters = "expression";
	static constexpr const char *Description = "Returns a string with statistics about the expression. Expression can "
	                                           "be a column, constant, or SQL expression.";
	static constexpr const char *Example = "stats(5)";

	static ScalarFunction GetFunction();
};

struct TypeOfFun {
	static constexpr const char *Name = "typeof";
	static constexpr const char *Parameters = "expression";
	static constexpr const char *Description = "Returns the name of the data type of the result of the expression.";
	static constexpr const char *Example = "typeof('abc')";

	static ScalarFunction GetFunction();
};

struct CurrentQueryFun {
	static constexpr const char *Name = "current_query";
	static constexpr const char *Parameters = "";
	static constexpr const char *Description = "Returns the current query as a string";
	static constexpr const char *Example = "current_query()";

	static ScalarFunction GetFunction();
};

struct CurrentSchemaFun {
	static constexpr const char *Name = "current_schema";
	static constexpr const char *Parameters = "";
	static constexpr const char *Description = "Return the name of the currently active schema. Default is main.";
	static constexpr const char *Example = "current_schema()";

	static ScalarFunction GetFunction();
};

struct CurrentSchemasFun {
	static constexpr const char *Name = "current_schemas";
	static constexpr const char *Parameters = "include_implicit";
	static constexpr const char *Description =
	    "Return list of schemas. Pass a parameter of True to include implicit schemas.";
	static constexpr const char *Example = "current_schemas(true)";

	static ScalarFunction GetFunction();
};

struct CurrentDatabaseFun {
	static constexpr const char *Name = "current_database";
	static constexpr const char *Parameters = "";
	static constexpr const char *Description = "Return the name of the currently active database.";
	static constexpr const char *Example = "current_database()";

	static ScalarFunction GetFunction();
};

struct CurrentTransactionIdFun {
	static constexpr const char *Name = "txid_current";
	static constexpr const char *Parameters = "";
	static constexpr const char *Description = "Returns the current transaction’s ID (a BIGINT). It will assign a new "
	                                           "one if the current transaction does not have one already.";
	static constexpr const char *Example = "txid_current()";

	static ScalarFunction GetFunction();
};

struct VersionFun {
	static constexpr const char *Name = "version";
	static constexpr const char *Parameters = "";
	static constexpr const char *Description =
	    "Return the currently active version of DuckDB in this format: v0.3.2	";
	static constexpr const char *Example = "version()";

	static ScalarFunction GetFunction();
};

} // namespace duckdb
