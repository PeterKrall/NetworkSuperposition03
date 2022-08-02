#ifdef USE_FILE_OUTPUT
#ifdef USE_MYSQL
#include "file_and_mysql_db_writer.h"
#include "configuration.h"

namespace persistence
{
    using namespace model;
    FileAndMySQLdbWriter::FileAndMySQLdbWriter(char* model_run_key) :  Writer(model_run_key), FileWriter(model_run_key) ,  MySQLdbWriter(model_run_key)  { }
    FileAndMySQLdbWriter::~FileAndMySQLdbWriter() { }
    FileAndMySQLdbWriter* FileAndMySQLdbWriter::instance = nullptr;
    model::Writer* FileAndMySQLdbWriter::create(char* model_run_key) { return (instance = new FileAndMySQLdbWriter(model_run_key)); }
    void FileAndMySQLdbWriter::destroy(model::Writer* writer)
    {
        if (instance == nullptr || writer != instance)
        {
            throw "oops";
        }
        delete instance;
        instance = nullptr;
    }

    void FileAndMySQLdbWriter::persist_population_state(PopulationState* population_state)
    {
        FileWriter::persist_population_state(population_state);
        MySQLdbWriter::persist_population_state(population_state);
    }
    bool FileAndMySQLdbWriter::is_activated = activate_conditionally();

    bool FileAndMySQLdbWriter::activate_conditionally()
    {
        Writer::open_writer = &FileAndMySQLdbWriter::create;
        Writer::close_writer = &FileAndMySQLdbWriter::destroy;
        return true;
    }
}
#endif
#endif