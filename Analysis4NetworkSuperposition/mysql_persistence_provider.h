#ifndef MYSQL_PERSISENCY_PROVIDER_H
#define MYSQL_PERSISENCY_PROVIDER_H
#ifdef USE_MYSQL
#include "persistence.h"
#include  <mysql.h>
namespace persistence
{ 
	class MySQLPersistenceProvider : public virtual PersistenceProvider
	{
	protected:
		MySQLPersistenceProvider();
		~MySQLPersistenceProvider();
	public:
		virtual std::vector<model::Configuration*>* read_configurations() final;
		virtual std::vector<std::string*>* read_model_runs(model::Configuration* configuration) final;
		virtual std::vector<model::PopulationState*>* read_population_states(std::string* model_run_key) final;
		virtual void persist(analysis::ModelRunStatistics* model_run_statistics, const char* model_run_key) final;
		virtual void erase_configuration_statistics() final;
		virtual void insert_configuration_statistics(analysis::ConfigurationStatistics& configuration_statistics) final;
		static bool activate();
	private:
		static PersistenceProvider* get_instance();
		static void close_instance(PersistenceProvider*);	
	private:
		static MySQLPersistenceProvider* instance;
		MYSQL* connection = nullptr;
		char* socket = nullptr;
	};
}
#endif
#endif // USE_MYSQL
