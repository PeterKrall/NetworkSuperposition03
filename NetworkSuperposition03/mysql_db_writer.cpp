#ifdef USE_MYSQL
#include "mysql_db_writer.h"
#include "database_parameter.inc"
#include <mysql.h>
#include "configuration.h"

namespace persistence
{
    using namespace model;
    MySQLdbWriter::MySQLdbWriter(char* model_run_key) : Writer(model_run_key)
    {
        connection = mysql_init(NULL);
        // Establish a MySQL connection
        if (
            !mysql_real_connect (
                                  connection
                                , DB_HOST
                                , DB_USER
                                , DB_PWD
                                , DATABASE_NAME
                                , PORT
                                , socket
                                , 0 // option
                                )
                                || mysql_autocommit(connection, true)
            )
        {
            throw mysql_error(connection);
        }
        char query[4096];
        sprintf_s   (
            query
                    , "insert into header "
                    "( "
                    "  model_run_key "
                    " ,strain_1_transmission_probability_aggregated_net_fluctuation "
                    " ,strain_1_transmission_probability_aggregated_stable_net "
                    " ,strain_1_transmission_probability_basic_net_luctuation "
                    " ,strain_1_transmission_probability_basic_stable_net "
                    " ,strain_2_transmission_probability_aggregated_net_fluctuation "
                    " ,strain_2_transmission_probability_aggregated_stable_net "
                    " ,strain_2_transmission_probability_basic_net_fluctuation "
                    " ,strain_2_transmission_probability_basic_stable_net "
                    " ,aggregated_net_with_fluctuation_number "
                    " ,aggregated_net_with_fluctuation_size "
                    " ,aggregated_stable_net_size "
                    " ,basic_net_with_fluctuation_fluctuation "
                    " ,basic_net_with_fluctuation_number "
                    " ,basic_net_with_fluctuation_size "
                    " ,basic_stable_net_size "
                    " ,population_size "
                    " ,strain1_random_transmission_probability "
                    " ,strain2_random_transmission_probability "
                    " ,shuffle_stable_nets "
                    ") values ( "
                    " '%s' ,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d "
                    ") "
                    , model_run_key
                    , model::Configuration::configuration->strain_1_transmission_probability_in_aggregated_net_with_fluctuation
                    , model::Configuration::configuration->strain_1_transmission_probability_in_aggregated_stable_net
                    , model::Configuration::configuration->strain_1_transmission_probability_in_basic_net_with_fluctuation
                    , model::Configuration::configuration->strain_1_transmission_probability_in_basic_stable_net
                    , model::Configuration::configuration->strain_2_transmission_probability_in_aggregated_net_with_fluctuation
                    , model::Configuration::configuration->strain_2_transmission_probability_in_aggregated_stable_net
                    , model::Configuration::configuration->strain_2_transmission_probability_in_basic_net_with_fluctuation
                    , model::Configuration::configuration->strain_2_transmission_probability_in_basic_stable_net
                    , model::Configuration::configuration->aggregated_net_with_fluctuation_number
                    , model::Configuration::configuration->aggregated_net_with_fluctuation_size
                    , model::Configuration::configuration->aggregated_stable_net_size
                    , model::Configuration::configuration->basic_net_with_fluctuation_fluctuation
                    , model::Configuration::configuration->basic_net_with_fluctuation_number
                    , model::Configuration::configuration->basic_net_with_fluctuation_size
                    , model::Configuration::configuration->basic_stable_net_size
                    , model::Configuration::configuration->population_size
                    , model::Configuration::configuration->strain1_random_transmission_probability
                    , model::Configuration::configuration->strain2_random_transmission_probability
                    , (model::Configuration::configuration->shuffle_stable_nets?1:0)
                    );
        if (mysql_query(connection, query))
        {
            throw mysql_error(connection);
        }
    } // open connection and write header
    
    MySQLdbWriter::~MySQLdbWriter()
    {
        mysql_close(connection);
    }
    MySQLdbWriter* MySQLdbWriter::instance = nullptr;
    model::Writer* MySQLdbWriter::create(char* model_run_key) { return (instance = new MySQLdbWriter(model_run_key)); }
    void MySQLdbWriter::destroy(model::Writer* writer)
    {
        if (instance == nullptr || writer != instance)
        {
            throw "oops";
        }
        delete instance;
        instance = nullptr;
    }

    void MySQLdbWriter::persist_population_state(PopulationState* population_state)
    {
        char query[4096];
        sprintf_s   (
            query
                    , "insert into population_state "
                    "( "
                    "  model_run_key "
                    " ,generation "
                    " ,new_activity "
                    " ,new_strain1_activity "
                    " ,new_strain2_activity "
                    " ,initial_state "
                    " ,strain1_activity "
                    " ,strain2_activity "
                    " ,post_strain1_activity "
                    " ,post_strain2_activity "
                    " ,nets_with_fluctuation_and_strain1_activity "
                    " ,nets_with_fluctuation_and_strain2_activity "
                    ") values ( "
                    " '%s' ,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d "
                    ") "
                    , model_run_key
                    , population_state->length_of_activity
                    , population_state->new_activity
                    , population_state->new_strain1_activity
                    , population_state->new_strain2_activity
                    , population_state->initial_state
                    , population_state->strain1_activity
                    , population_state->strain2_activity
                    , population_state->post_strain1_activity
                    , population_state->post_strain2_activity
                    , population_state->nets_with_fluctuation_and_strain1_activity
                    , population_state->nets_with_fluctuation_and_strain2_activity
                    );
        if (mysql_query(connection, query))
        {
            throw mysql_error(connection);
        }
    }
    bool MySQLdbWriter::is_activated = activate_conditionally();

    bool MySQLdbWriter::activate_conditionally()
    {
#ifndef USE_FILE_OUTPUT
        Writer::open_writer = &MySQLdbWriter::create;
        Writer::close_writer = &MySQLdbWriter::destroy;
        return true;
#else
        return false;
#endif // NOT use file
    }
}
#endif // USE mysql