//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/catalog/dependency_manager.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include "duckdb/catalog/catalog_entry.hpp"
#include "duckdb/catalog/catalog_set.hpp"
#include "duckdb/catalog/dependency.hpp"
#include "duckdb/catalog/catalog_entry_map.hpp"
#include "duckdb/catalog/catalog_transaction.hpp"
#include "duckdb/catalog/catalog_entry/dependency_set_catalog_entry.hpp"

#include <functional>

namespace duckdb {
class DuckCatalog;
class ClientContext;
class DependencyList;
class DependencyCatalogEntry;

//! The DependencyManager is in charge of managing dependencies between catalog entries
class DependencyManager {
	friend class CatalogSet;

public:
	explicit DependencyManager(DuckCatalog &catalog);

	//! Scans all dependencies, returning pairs of (object, dependent)
	void Scan(ClientContext &context,
	          const std::function<void(CatalogEntry &, CatalogEntry &, DependencyType)> &callback);

	void AddOwnership(CatalogTransaction transaction, CatalogEntry &owner, CatalogEntry &entry);

private:
	DuckCatalog &catalog;
	CatalogSet connections;

private:
	bool IsSystemEntry(CatalogEntry &entry) const;
	DependencySetCatalogEntry &GetOrCreateDependencySet(CatalogTransaction transaction, CatalogEntry &entry);
	optional_ptr<DependencySetCatalogEntry> GetDependencySet(CatalogTransaction transaction, CatalogEntry &entry);
	// Alternative to get the latest entry if no CatalogTransaction is available.
	optional_ptr<DependencySetCatalogEntry> GetDependencySet(CatalogEntry &entry);

	struct LookupResult {
	public:
		LookupResult(optional_ptr<CatalogEntry> entry);
		LookupResult(optional_ptr<CatalogSet> set, optional_ptr<MappingValue> mapping_value,
		             optional_ptr<CatalogEntry> entry);

	public:
		optional_ptr<CatalogSet> set;
		optional_ptr<MappingValue> mapping_value;
		optional_ptr<CatalogEntry> entry;
	};
	LookupResult LookupEntry(CatalogTransaction transaction, CatalogEntry &dependency);

	void CleanupDependencies(CatalogTransaction transaction, CatalogEntry &entry);

public:
	static string MangleName(CatalogType type, const string &schema, const string &name);
	static string MangleName(CatalogEntry &entry);
	static void UnmangleName(const string &mangled, CatalogType &type, string &schema, string &name);

private:
	void AddObject(CatalogTransaction transaction, CatalogEntry &object, DependencyList &dependencies);
	void DropObject(CatalogTransaction transaction, CatalogEntry &object, bool cascade);
	void AlterObject(CatalogTransaction transaction, CatalogEntry &old_obj, CatalogEntry &new_obj);
};

} // namespace duckdb
