#ifndef FILE_AND_MYSQL_WRITER
#define FILE_AND_MYSQL_WRITER
#include "file_writer.h"
#include "mysql_db_writer.h"

namespace persistence
{
	// file-writing plus mysql-db implementation of Writer interface

	class FileAndMySQLdbWriter : public virtual FileWriter ,  public virtual MySQLdbWriter
	{
	protected:
		FileAndMySQLdbWriter(char* model_run_key);
		~FileAndMySQLdbWriter();
	public:
		virtual void persist_population_state(model::PopulationState* population_state);
		static model::Writer* create(char* model_run_key);
		static void destroy(model::Writer*);
		static bool is_activated;
		static bool activate_conditionally();
	private:
		static FileAndMySQLdbWriter* instance;
	};
}

#endif // !FILE_AND_MYSQL_WRITER




