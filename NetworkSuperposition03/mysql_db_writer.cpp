#ifdef USE_MYSQL
#include "mysql_db_writer.h"
#include "database_parameter.inc"
#include <mysql.h>
#include "configuration.h"
#include <iostream>
namespace persistence
{
    using namespace model;
    MySQLdbWriter::MySQLdbWriter(char* model_run_key) : Writer(model_run_key)
    {
        std::cout << "started\n";
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
                    " ,label "
                    " ,strain_1_transmission_probability_aggregated_net_fluctuation "
                    " ,strain_1_transmission_probability_aggregated_stable_net "
                    " ,strain_1_transmission_probability_basic_net_fluctuation "
                    " ,strain_1_transmission_probability_basic_stable_net "
                    " ,strain_2_transmission_probability_aggregated_net_fluctuation "
                    " ,strain_2_transmission_probability_aggregated_stable_net "
                    " ,strain_2_transmission_probability_basic_net_fluctuation "
                    " ,strain_2_transmission_probability_basic_stable_net "
                    " ,aggregated_net_with_fluctuation_number "
                    " ,aggregated_net_with_fluctuation_size "
                    " ,aggregated_stable_net_size "
                    " ,aggregated_stable_net_number "
                    " ,basic_net_with_fluctuation_fluctuation "
                    " ,basic_net_with_fluctuation_number "
                    " ,basic_net_with_fluctuation_size "
                    " ,basic_stable_net_size "
                    " ,population_size "
                    " ,strain1_random_transmission_probability "
                    " ,strain2_random_transmission_probability "
                    " ,shuffle_stable_nets "
                    " ,strain_1_contagiousness_begin "
                    " ,strain_1_contagiousness_end "
                    " ,strain_2_contagiousness_begin "
                    " ,strain_2_contagiousness_end "
                    " ,immunity_reduction_time " 
                    " ,immunity_reduction_weight "
                    " ,initial_strain1cases "
                    " ,initial_strain2cases "
                    " ,first_strain2_appearance "
                    " ,environmental_constraints_change_time "
                    " ,environmental_constraints_change_weight"
                    ") values ( "
                    " '%s','%s',%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,'%s','%s',%d, %d, %d "
                    ") "
                    , model_run_key
                    , model::Configuration::configuration->label.c_str()
                    , model::Configuration::configuration->strain_1_exposition_in_aggregated_net_with_fluctuation
                    , model::Configuration::configuration->strain_1_exposition_in_aggregated_stable_net
                    , model::Configuration::configuration->strain_1_exposition_in_basic_net_with_fluctuation
                    , model::Configuration::configuration->strain_1_exposition_in_basic_stable_net
                    , model::Configuration::configuration->strain_2_exposition_in_aggregated_net_with_fluctuation
                    , model::Configuration::configuration->strain_2_exposition_in_aggregated_stable_net
                    , model::Configuration::configuration->strain_2_exposition_in_basic_net_with_fluctuation
                    , model::Configuration::configuration->strain_2_exposition_in_basic_stable_net
                    , model::Configuration::configuration->aggregated_net_with_fluctuation_number
                    , model::Configuration::configuration->aggregated_net_with_fluctuation_size
                    , model::Configuration::configuration->aggregated_stable_net_size
                    , model::Configuration::configuration->aggregated_stable_net_number
                    , model::Configuration::configuration->basic_net_with_fluctuation_fluctuation
                    , model::Configuration::configuration->basic_net_with_fluctuation_number
                    , model::Configuration::configuration->basic_net_with_fluctuation_size
                    , model::Configuration::configuration->basic_stable_net_size
                    , model::Configuration::configuration->population_size
                    , model::Configuration::configuration->strain1_random_transmission_probability
                    , model::Configuration::configuration->strain2_random_transmission_probability
                    , model::Configuration::configuration->aggregated_stable_net_shuffle
                    , model::Configuration::configuration->strain_1_contagiousness_begin
                    , model::Configuration::configuration->strain_1_contagiousness_end
                    , model::Configuration::configuration->strain_2_contagiousness_begin
                    , model::Configuration::configuration->strain_2_contagiousness_end
                    , model::Configuration::configuration->immunity_reduction_time_of_strain1_for_strain_2_exposition
                    , model::Configuration::configuration->immunity_reduction_weight_of_strain1_for_strain_2_exposition
                    , model::Configuration::configuration->initial_strain1cases.c_str()
                    , model::Configuration::configuration->initial_strain2cases.c_str()
                    , model::Configuration::configuration->first_strain2_appearance
                    , model::Configuration::configuration->environmental_constraints_change_time
                    , model::Configuration::configuration->environmental_constraints_change_weight
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
        std::fill_n(query, 4095, '\0');
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
        int x = 0;
        if (( x = mysql_query(connection, query)) != 0)
        {
            std::cout << "error " << x << " try to reconnect\n";
            if (
                !mysql_real_connect(
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
                std::cout << "error trying to reconnect\n";
                throw mysql_error(connection);
            }
            if ((x = mysql_query(connection, query)) != 0)
            {
                std::cout << "error " << x << "after trying to reconnect\n";
                throw mysql_error(connection);
            }
        }
    }
    static bool is_activated = MySQLdbWriter::activate_conditionally();

    bool MySQLdbWriter::activate_conditionally()
    {
#ifndef USE_FILE_OUTPUT
        if (Writer::open_writer == nullptr)
        {
            Writer::open_writer = &MySQLdbWriter::create;
            Writer::close_writer = &MySQLdbWriter::destroy;
        }
        return true;
#else
        return false;
#endif // NOT use combined db|file-writer
    }
    
}
#endif // USE mysql