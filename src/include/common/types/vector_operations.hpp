//===----------------------------------------------------------------------===//
//
//                         DuckDB
//
// execution/vector/vector_operations.hpp
//
// Author: Mark Raasveldt
//
//===----------------------------------------------------------------------===//

#pragma once

#include <functional>

#include "common/types/vector.hpp"

namespace duckdb {

// VectorOperations contains a set of operations that operate on sets of
// vectors. In general, the operators must all have the same type, otherwise an
// exception is thrown.
struct VectorOperations {
	typedef void (*vector_function)(Vector &left, Vector &right,
	                                Vector &result);

	//===--------------------------------------------------------------------===//
	// Numeric Operations
	//===--------------------------------------------------------------------===//
	// A + B
	static void Add(Vector &left, Vector &right, Vector &result);
	// A - B
	static void Subtract(Vector &left, Vector &right, Vector &result);
	// A * B
	static void Multiply(Vector &left, Vector &right, Vector &result);
	// A / B
	static void Divide(Vector &left, Vector &right, Vector &result);
	// A % B
	static void Modulo(Vector &left, Vector &right, Vector &result);
	// ABS(A)
	static void Abs(Vector &left, Vector &result);

	// NOT(A)
	static void Not(Vector &left, Vector &result);

	// IS NOT NULL(A)
	static void IsNotNull(Vector &left, Vector &result);

	// IS NULL (A)
	static void IsNull(Vector &left, Vector &result);

	// A + B
	static void Add(Vector &left, int64_t right, Vector &result);
	// A - B
	static void Subtract(Vector &left, int64_t right, Vector &result);
	// A * B
	static void Multiply(Vector &left, int64_t right, Vector &result);
	// A / B
	static void Divide(Vector &left, int64_t right, Vector &result);
	// A % B
	static void Modulo(Vector &left, int64_t right, Vector &result);

	// A + B
	static void Add(int64_t left, Vector &right, Vector &result);
	// A - B
	static void Subtract(int64_t left, Vector &right, Vector &result);
	// A * B
	static void Multiply(int64_t left, Vector &right, Vector &result);
	// A / B
	static void Divide(int64_t left, Vector &right, Vector &result);
	// A % B
	static void Modulo(int64_t left, Vector &right, Vector &result);

	//===--------------------------------------------------------------------===//
	// Boolean Operations
	//===--------------------------------------------------------------------===//
	// A && B
	static void And(Vector &left, Vector &right, Vector &result);
	// A || B
	static void Or(Vector &left, Vector &right, Vector &result);

	//===--------------------------------------------------------------------===//
	// Comparison Operations
	//===--------------------------------------------------------------------===//
	// A == B
	static void Equals(Vector &left, Vector &right, Vector &result);
	// A != B
	static void NotEquals(Vector &left, Vector &right, Vector &result);
	// A > B
	static void GreaterThan(Vector &left, Vector &right, Vector &result);
	// A >= B
	static void GreaterThanEquals(Vector &left, Vector &right, Vector &result);
	// A < B
	static void LessThan(Vector &left, Vector &right, Vector &result);
	// A <= B
	static void LessThanEquals(Vector &left, Vector &right, Vector &result);

	//===--------------------------------------------------------------------===//
	// Aggregates
	//===--------------------------------------------------------------------===//
	// SUM(A)
	static Value Sum(Vector &source);
	// COUNT(A)
	static Value Count(Vector &source);
	// MAX(A)
	static Value Max(Vector &left);
	// MIN(A)
	static Value Min(Vector &left);
	// Returns whether or not a vector has a NULL value
	static bool HasNull(Vector &left);
	// Maximum string length of the vector, only works on string vectors!
	static Value MaximumStringLength(Vector &left);
	// Check if any value is true in a bool vector
	static Value AnyTrue(Vector &left);
	// Check if all values are true in a bool vector
	static Value AllTrue(Vector &left);

	// CASE expressions, ternary op
	static void Case(Vector &check, Vector &res_true, Vector &res_false,
	                 Vector &result);

	// Returns true if the vector contains an instance of Value
	static bool Contains(Vector &vector, Value &value);

	//===--------------------------------------------------------------------===//
	// Scatter methods
	//===--------------------------------------------------------------------===//
	struct Scatter {
		// dest[i] = source.data[i]
		static void Set(Vector &source, Vector &dest);
		// dest[i] += source.data[i]
		static void Add(Vector &source, Vector &dest);
		// dest[i] = max(dest[i], source.data[i])
		static void Max(Vector &source, Vector &dest);
		// dest[i] = min(dest[i], source.data[i])
		static void Min(Vector &source, Vector &dest);
		// dest[i] = dest[i] + 1
		static void AddOne(Vector &source, Vector &dest);
		//! dest[i] = dest[i]
		static void SetFirst(Vector &source, Vector &dest);
		// dest[i] = dest[i] + source
		static void Add(int64_t source, void **dest, size_t length);
	};
	// make sure dest.count is set for gather methods!
	struct Gather {
		// dest.data[i] = ptr[i]
		static void Set(Vector &source, Vector &dest);
	};
	//===--------------------------------------------------------------------===//
	// Hash functions
	//===--------------------------------------------------------------------===//
	// HASH(A)
	static void Hash(Vector &source, Vector &result);
	// COMBINE(A, HASH(B))
	static void CombineHash(Vector &left, Vector &right, Vector &result);

	//===--------------------------------------------------------------------===//
	// Generate functions
	//===--------------------------------------------------------------------===//
	static void GenerateSequence(Vector &source, int64_t start = 0,
	                             int64_t increment = 1);
	//===--------------------------------------------------------------------===//
	// Helpers
	//===--------------------------------------------------------------------===//
	// Copy the data from source to target, casting if the types don't match
	static void Cast(Vector &source, Vector &result);
	// Copy the data of <source> to the target location
	static void Copy(Vector &source, void *target, size_t offset = 0,
	                 size_t element_count = 0);
	// Copy the data of <source> to the target vector
	static void Copy(Vector &source, Vector &target, size_t offset = 0);
	// Copy the data of <source> to the target location, setting null values to
	// NullValue<T>
	static void CopyNull(Vector &source, void *target, size_t offset = 0,
	                     size_t element_count = 0);
	// Appends the data of <source> to the target vector, setting the nullmask
	// for any NullValue<T> of source
	static void AppendNull(Vector &source, Vector &target);

	// Set all elements of the vector to the given constant value
	static void Set(Vector &result, Value value);
	//! For every value in result, set result[i] = left[sel_vector[i]]
	static void ApplySelectionVector(Vector &left, Vector &result,
	                                 sel_t *sel_vector);
	//===--------------------------------------------------------------------===//
	// Exec
	//===--------------------------------------------------------------------===//
	//! Exec over the set of indexes, calls the callback function with (i) =
	//! index, dependent on selection vector and (k) = count
	static void Exec(Vector &vector,
	                 std::function<void(size_t i, size_t k)> fun,
	                 size_t offset = 0, size_t count = 0) {
		size_t i = offset;
		if (count == 0) {
			count = vector.count;
		} else {
			count += offset;
		}
		if (vector.sel_vector) {
			//#pragma GCC ivdep
			for (; i + 8 < count; i += 8) {
				fun(vector.sel_vector[i + 0], i + 0);
				fun(vector.sel_vector[i + 1], i + 1);
				fun(vector.sel_vector[i + 2], i + 2);
				fun(vector.sel_vector[i + 3], i + 3);
				fun(vector.sel_vector[i + 4], i + 4);
				fun(vector.sel_vector[i + 5], i + 5);
				fun(vector.sel_vector[i + 6], i + 6);
				fun(vector.sel_vector[i + 7], i + 7);
			}

			//#pragma GCC ivdep
			for (; i < count; i++) {
				fun(vector.sel_vector[i], i);
			}
		} else {
			//#pragma GCC ivdep
			for (; i + 8 < count; i += 8) {
				fun(i + 0, i + 0);
				fun(i + 1, i + 1);
				fun(i + 2, i + 2);
				fun(i + 3, i + 3);
				fun(i + 4, i + 4);
				fun(i + 5, i + 5);
				fun(i + 6, i + 6);
				fun(i + 7, i + 7);
			}
			//#pragma GCC ivdep
			for (; i < count; i++) {
				fun(i, i);
			}
		}
	}

	//! Exec over a specific type. Note that it is up to the caller to verify
	//! that the vector passed in has the correct type for the iteration! This
	//! is effectively equivalent to calling ::Exec() and performing data[i] for
	//! every entry
	template <typename T, bool IGNORE_NULL = false>
	static void ExecType(Vector &vector,
	                     std::function<void(T &value, size_t i, size_t k)> fun,
	                     size_t offset = 0, size_t limit = 0) {
		auto data = (T *)vector.data;
		VectorOperations::Exec(vector,
		                       [&](size_t i, size_t k) {
			                       if (!IGNORE_NULL || !vector.nullmask[i]) {
				                       fun(data[i], i, k);
			                       }
		                       },
		                       offset, limit);
	}
};
} // namespace duckdb
