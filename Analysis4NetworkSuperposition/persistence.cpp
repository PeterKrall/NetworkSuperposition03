#include "persistence.h"

namespace persistence
{
	PersistenceProvider::PersistenceProvider() {}
	PersistenceProvider::~PersistenceProvider() {}
	get_persistence_provider_function* PersistenceProvider::get_persistence_provider_instance()
	{
		return get_persistence_provider_instance_implementation;
	}
	close_persistence_provider_function* PersistenceProvider::close_persistence_provider_instance()
	{
		return close_persistence_provider_instance_implementation;
	}
	
	get_persistence_provider_function* PersistenceProvider::get_persistence_provider_instance_implementation = nullptr; // pointer to the derived classes implmentation
	close_persistence_provider_function* PersistenceProvider::close_persistence_provider_instance_implementation = nullptr; // pointer to the derived classes implmentation;
};