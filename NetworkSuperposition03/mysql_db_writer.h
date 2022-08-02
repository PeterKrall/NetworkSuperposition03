#ifdef USE_MYSQL
#ifndef MYSQL_DB_WRITER
#define MYSQL_DB_WRITER
#include "writer.h"
#include <mysql.h>
namespace persistence
{
	// file-writing plus mysql-db implementation of Writer interface

	class MySQLdbWriter : public virtual model::Writer
	{
	protected:
		MySQLdbWriter(char* model_run_key);
		~MySQLdbWriter();
	public:
		virtual void persist_population_state(model::PopulationState* population_state);
	private:
		static model::Writer* create(char* model_run_key);
		static void destroy(model::Writer*);
		static bool is_activated;
		static bool activate_conditionally();
	private:
		static MySQLdbWriter* instance;
		MYSQL* connection = nullptr;
		char* socket = nullptr;
	};
}
#endif
#endif // USE_MYSQL
