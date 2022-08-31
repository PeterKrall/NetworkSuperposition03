#ifndef PERSISTENCY_H
#define PERSISTENCY_H
#include "configuration.h"
#include "population_state.h"
#include "run_statistics.h"
#include "configuration_statistics.h"
namespace persistence
{
	typedef class PersistenceProvider* (get_persistence_provider_function());
	typedef void(close_persistence_provider_function(class PersistenceProvider* persistence_provider));
	// the interface for persistence providing classes
	class PersistenceProvider
	{
	public:
		static get_persistence_provider_function* get_persistence_provider_instance();
		static close_persistence_provider_function* close_persistence_provider_instance();
		virtual std::vector<model::Configuration*>* read_configurations() = 0;
		virtual std::vector<std::string*>* read_model_runs(model::Configuration* configuration) = 0;
		virtual std::vector<model::PopulationState*>* read_population_states(std::string* model_run_key) = 0;
		virtual void persist(analysis::ModelRunStatistics* model_run_statistics, const char* model_run_key) = 0;
		virtual void erase_configuration_statistics() = 0;
		virtual void insert_configuration_statistics(analysis::ConfigurationStatistics& configuration_statistics) = 0;
	protected:
		static get_persistence_provider_function* get_persistence_provider_instance_implementation; // pointer to the derived classes implmentation
		static close_persistence_provider_function* close_persistence_provider_instance_implementation; // pointer to the derived classes implmentation;
		PersistenceProvider();
		~PersistenceProvider();
	};
}
#endif
