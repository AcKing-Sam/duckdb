//===----------------------------------------------------------------------===//
//                         DuckDB
//
// scalar/list_functions.hpp
//
//
//===----------------------------------------------------------------------===//
// This file is generated by scripts/generate_functions.py

#pragma once

#include "duckdb/function/function_set.hpp"

namespace duckdb {

struct ListFlattenFun {
	static constexpr const char *Name = "flatten";
	static constexpr const char *Parameters = "nested_list";
	static constexpr const char *Description = "Flatten a nested list by one level";
	static constexpr const char *Example = "flatten([[1, 2, 3], [4, 5]])";

	static ScalarFunction GetFunction();
};

struct ListValueFun {
	static constexpr const char *Name = "list_value";
	static constexpr const char *Parameters = "any,...";
	static constexpr const char *Description = "Create a LIST containing the argument values.";
	static constexpr const char *Example = "list_value(4, 5, 6)";

	static ScalarFunction GetFunction();
};

struct ListSortFun {
	static constexpr const char *Name = "list_sort";
	static constexpr const char *Parameters = "list";
	static constexpr const char *Description = "Sorts the elements of the list.";
	static constexpr const char *Example = "list_sort([3, 6, 1, 2])";

	static ScalarFunctionSet GetFunctions();
};

struct ListReverseSortFun {
	static constexpr const char *Name = "list_reverse_sort";
	static constexpr const char *Parameters = "list";
	static constexpr const char *Description = "Sorts the elements of the list in reverse order.";
	static constexpr const char *Example = "list_reverse_sort([3, 6, 1, 2])";

	static ScalarFunctionSet GetFunctions();
};

struct ListPackFun {
	using ALIAS = ListValueFun;

	static constexpr const char *Name = "list_pack";
};

struct ArraySortFun {
	using ALIAS = ListSortFun;

	static constexpr const char *Name = "array_sort";
};

struct ArrayReverseSortFun {
	using ALIAS = ListReverseSortFun;

	static constexpr const char *Name = "array_reverse_sort";
};

}
