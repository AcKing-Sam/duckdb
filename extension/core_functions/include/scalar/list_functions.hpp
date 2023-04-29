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

struct ListAggregateFun {
	static constexpr const char *Name = "list_aggregate";
	static constexpr const char *Parameters = "list,name";
	static constexpr const char *Description = "Executes the aggregate function name on the elements of list.";
	static constexpr const char *Example = "list_aggregate([1, 2, NULL], 'min')";

	static ScalarFunction GetFunction();
};

struct ArrayAggregateFun {
	using ALIAS = ListAggregateFun;

	static constexpr const char *Name = "array_aggregate";
};

struct ListAggrFun {
	using ALIAS = ListAggregateFun;

	static constexpr const char *Name = "list_aggr";
};

struct ArrayAggrFun {
	using ALIAS = ListAggregateFun;

	static constexpr const char *Name = "array_aggr";
};

struct AggregateFun {
	using ALIAS = ListAggregateFun;

	static constexpr const char *Name = "aggregate";
};

struct ListDistinctFun {
	static constexpr const char *Name = "list_distinct";
	static constexpr const char *Parameters = "list";
	static constexpr const char *Description =
	    "Removes all duplicates and NULLs from a list. Does not preserve the original order.";
	static constexpr const char *Example = "list_distinct([1, 1, NULL, -3, 1, 5])";

	static ScalarFunction GetFunction();
};

struct ArrayDistinctFun {
	using ALIAS = ListDistinctFun;

	static constexpr const char *Name = "array_distinct";
};

struct ListUniqueFun {
	static constexpr const char *Name = "list_unique";
	static constexpr const char *Parameters = "list";
	static constexpr const char *Description = "Counts the unique elements of a list.";
	static constexpr const char *Example = "list_unique([1, 1, NULL, -3, 1, 5])";

	static ScalarFunction GetFunction();
};

struct ArrayUniqueFun {
	using ALIAS = ListUniqueFun;

	static constexpr const char *Name = "array_unique";
};

struct ListValueFun {
	static constexpr const char *Name = "list_value";
	static constexpr const char *Parameters = "any,...";
	static constexpr const char *Description = "Create a LIST containing the argument values.";
	static constexpr const char *Example = "list_value(4, 5, 6)";

	static ScalarFunction GetFunction();
};

struct ListPackFun {
	using ALIAS = ListValueFun;

	static constexpr const char *Name = "list_pack";
};

struct ListSliceFun {
	static constexpr const char *Name = "list_slice";
	static constexpr const char *Parameters = "list,begin,end";
	static constexpr const char *Description = "Extract a sublist using slice conventions. NULLs are interpreted as "
	                                           "the bounds of the LIST. Negative values are accepted.";
	static constexpr const char *Example = "list_slice(l, 2, NULL)";

	static ScalarFunction GetFunction();
};

struct ArraySliceFun {
	using ALIAS = ListSliceFun;

	static constexpr const char *Name = "array_slice";
};

struct ListSortFun {
	static constexpr const char *Name = "list_sort";
	static constexpr const char *Parameters = "list";
	static constexpr const char *Description = "Sorts the elements of the list.";
	static constexpr const char *Example = "list_sort([3, 6, 1, 2])";

	static ScalarFunctionSet GetFunctions();
};

struct ArraySortFun {
	using ALIAS = ListSortFun;

	static constexpr const char *Name = "array_sort";
};

struct ListReverseSortFun {
	static constexpr const char *Name = "list_reverse_sort";
	static constexpr const char *Parameters = "list";
	static constexpr const char *Description = "Sorts the elements of the list in reverse order.";
	static constexpr const char *Example = "list_reverse_sort([3, 6, 1, 2])";

	static ScalarFunctionSet GetFunctions();
};

struct ArrayReverseSortFun {
	using ALIAS = ListReverseSortFun;

	static constexpr const char *Name = "array_reverse_sort";
};

struct ListTransformFun {
	static constexpr const char *Name = "list_transform";
	static constexpr const char *Parameters = "list,lambda";
	static constexpr const char *Description =
	    "Returns a list that is the result of applying the lambda function to each element of the input list. See the "
	    "Lambda Functions section for more details.";
	static constexpr const char *Example = "list_transform([1, 2, 3], x -> x + 1)";

	static ScalarFunction GetFunction();
};

struct ArrayTransformFun {
	using ALIAS = ListTransformFun;

	static constexpr const char *Name = "array_transform";
};

struct ListApplyFun {
	using ALIAS = ListTransformFun;

	static constexpr const char *Name = "list_apply";
};

struct ArrayApplyFun {
	using ALIAS = ListTransformFun;

	static constexpr const char *Name = "array_apply";
};

struct ApplyFun {
	using ALIAS = ListTransformFun;

	static constexpr const char *Name = "apply";
};

struct ListFilterFun {
	static constexpr const char *Name = "list_filter";
	static constexpr const char *Parameters = "list,lambda";
	static constexpr const char *Description =
	    "Constructs a list from those elements of the input list for which the lambda function returns true.";
	static constexpr const char *Example = "list_filter([3, 4, 5], x -> x > 4)";

	static ScalarFunction GetFunction();
};

struct ArrayFilterFun {
	using ALIAS = ListFilterFun;

	static constexpr const char *Name = "array_filter";
};

struct FilterFun {
	using ALIAS = ListFilterFun;

	static constexpr const char *Name = "filter";
};

struct GenerateSeriesFun {
	static constexpr const char *Name = "generate_series";
	static constexpr const char *Parameters = "start,stop,step";
	static constexpr const char *Description =
	    "Create a list of values between start and stop - the stop parameter is inclusive";
	static constexpr const char *Example = "generate_series(2, 5, 3)";

	static ScalarFunctionSet GetFunctions();
};

struct ListRangeFun {
	static constexpr const char *Name = "range";
	static constexpr const char *Parameters = "start,stop,step";
	static constexpr const char *Description =
	    "Create a list of values between start and stop - the stop parameter is exclusive";
	static constexpr const char *Example = "range(2, 5, 3)";

	static ScalarFunctionSet GetFunctions();
};

} // namespace duckdb
