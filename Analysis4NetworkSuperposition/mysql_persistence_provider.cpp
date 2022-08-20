#ifdef USE_MYSQL
#include "mysql_persistence_provider.h"
#include "database_parameter.inc"
#include "configuration.h"

namespace persistence
{
    MySQLPersistenceProvider::MySQLPersistenceProvider() : PersistenceProvider()
    {
        connection = mysql_init(NULL);
        // Establish a MySQL connection
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
            throw mysql_error(connection);
        }
    } // open connection and write header

    MySQLPersistenceProvider::~MySQLPersistenceProvider()
    {
        mysql_close(connection);
    }
    MySQLPersistenceProvider* MySQLPersistenceProvider::instance = nullptr;
    PersistenceProvider* MySQLPersistenceProvider::get_instance()
    { 
        return (instance==nullptr?(instance = new MySQLPersistenceProvider()):instance);
    }
    void MySQLPersistenceProvider::close_instance(PersistenceProvider* persistence_provider)
    {
        if (instance == nullptr || persistence_provider != instance) { throw "oops"; }
        delete instance;
        instance = nullptr;
    }

    bool MySQLPersistenceProvider::is_activated = activate();

    bool MySQLPersistenceProvider::activate()
    {
        PersistenceProvider::get_persistence_provider_instance_implementation
            = &MySQLPersistenceProvider::get_instance;
        PersistenceProvider::close_persistence_provider_instance_implementation
            = &MySQLPersistenceProvider::close_instance;
        return true;
    }
    std::vector<model::Configuration*>* MySQLPersistenceProvider::read_configurations()
    {
        try {
            std::vector<model::Configuration*>* configurations = new std::vector<model::Configuration*>();
            char query[4096];
            sprintf_s(
                query
                , "select distinct "
                "  label "
                " ,initial_strain1cases "
                " ,initial_strain2cases "
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
                " ,first_strain2_appearance "
                " from header");
            MYSQL_STMT* stmt = mysql_stmt_init(connection);
            mysql_stmt_prepare(stmt, query, -1);
            if (mysql_stmt_execute(stmt)) { throw mysql_error(connection); }
            MYSQL_BIND bind[29];
            my_bool is_null[29];
            unsigned long length[29];
            unsigned long long_values[26];
            char* text_values[3];
            char b0[129]; text_values[0] = &b0[0];
            char b1[129]; text_values[1] = &b1[0];
            char b2[129]; text_values[2] = &b2[0];
            memset(bind, 0, sizeof(bind));
            for (int i = 0; i < 3; ++i)
            {
                bind[i].buffer_type = MYSQL_TYPE_STRING; bind[i].buffer = text_values[i]; bind[i].buffer_length = 128; bind[i].is_null = &is_null[0]; bind[i].length = &length[i];
            }
            for (int i = 3; i < 29; ++i)
            {
                bind[i].buffer_type = MYSQL_TYPE_LONG; bind[i].buffer = (char*)(&(long_values[i - 3])); bind[i].is_null = &is_null[0]; bind[i].length = &length[i];
            }
            mysql_stmt_bind_result(stmt, bind);
            while (mysql_stmt_fetch(stmt) != MYSQL_NO_DATA)
            {
                model::Configuration* comfiguration
                    = new model::Configuration(long_values[0], long_values[1], long_values[2], long_values[3], long_values[4],
                        long_values[5], long_values[6], long_values[7], long_values[8], long_values[9], long_values[10],
                        long_values[11], long_values[12], long_values[13], long_values[14], long_values[15], long_values[16],
                        long_values[17], long_values[18], long_values[19], long_values[20], long_values[21], long_values[22],
                        long_values[23], long_values[24], long_values[25], text_values[1], text_values[2], "n.a.", text_values[0]);
                configurations->push_back(comfiguration);
            }
            mysql_stmt_close(stmt);
            return configurations;
        }
        catch (...)
        {
            printf("oops - that's an error in the program");
            return nullptr;
        }
    }
    std::vector<std::string*>* MySQLPersistenceProvider::read_model_runs(model::Configuration* configuration)
    {
        try
        {
            std::vector<std::string*>* model_runs = new std::vector<std::string*>();
            char query[4096];
            sprintf_s
            (
                query
                , "select model_run_key from header where "
                "     label = '%s' "
                " and initial_strain1cases = '%s' "
                " and initial_strain2cases = '%s' "
                " and strain_1_transmission_probability_aggregated_net_fluctuation = %d "
                " and strain_1_transmission_probability_aggregated_stable_net = %d "
                " and strain_1_transmission_probability_basic_net_fluctuation = %d "
                " and strain_1_transmission_probability_basic_stable_net = %d "
                " and strain_2_transmission_probability_aggregated_net_fluctuation = %d "
                " and strain_2_transmission_probability_aggregated_stable_net = %d "
                " and strain_2_transmission_probability_basic_net_fluctuation = %d "
                " and strain_2_transmission_probability_basic_stable_net = %d "
                " and aggregated_net_with_fluctuation_number = %d "
                " and aggregated_net_with_fluctuation_size = %d "
                " and aggregated_stable_net_size = %d "
                " and basic_net_with_fluctuation_fluctuation = %d "
                " and basic_net_with_fluctuation_number = %d "
                " and basic_net_with_fluctuation_size = %d "
                " and basic_stable_net_size = %d "
                " and population_size = %d "
                " and strain1_random_transmission_probability = %d "
                " and strain2_random_transmission_probability = %d "
                " and shuffle_stable_nets = %d "
                " and strain_1_contagiousness_begin = %d "
                " and strain_1_contagiousness_end = %d "
                " and strain_2_contagiousness_begin = %d "
                " and strain_2_contagiousness_end = %d "
                " and immunity_reduction_time = %d "
                " and immunity_reduction_weight = %d "
                " and first_strain2_appearance = %d "
                , configuration->label.c_str()
                , configuration->initial_strain1cases.c_str()
                , configuration->initial_strain2cases.c_str()
                , configuration->strain_1_transmission_probability_in_aggregated_net_with_fluctuation
                , configuration->strain_1_transmission_probability_in_aggregated_stable_net
                , configuration->strain_1_transmission_probability_in_basic_net_with_fluctuation
                , configuration->strain_1_transmission_probability_in_basic_stable_net
                , configuration->strain_2_transmission_probability_in_aggregated_net_with_fluctuation
                , configuration->strain_2_transmission_probability_in_aggregated_stable_net
                , configuration->strain_2_transmission_probability_in_basic_net_with_fluctuation
                , configuration->strain_2_transmission_probability_in_basic_stable_net
                , configuration->aggregated_net_with_fluctuation_number
                , configuration->aggregated_net_with_fluctuation_size
                , configuration->aggregated_stable_net_size
                , configuration->basic_net_with_fluctuation_fluctuation
                , configuration->basic_net_with_fluctuation_number
                , configuration->basic_net_with_fluctuation_size
                , configuration->basic_stable_net_size
                , configuration->population_size
                , configuration->strain1_random_transmission_probability
                , configuration->strain2_random_transmission_probability
                , configuration->aggregated_stable_net_shuffle
                , configuration->strain_1_contagiousness_begin
                , configuration->strain_1_contagiousness_end
                , configuration->strain_2_contagiousness_begin
                , configuration->strain_2_contagiousness_end
                , configuration->immunity_reduction_time_of_strain1_for_strain_2_exposition
                , configuration->immunity_reduction_weight_of_strain1_for_strain_2_exposition
                , configuration->first_strain2_appearance
            );
            MYSQL_STMT* stmt = mysql_stmt_init(connection);
            mysql_stmt_prepare(stmt, query, -1);
            if (mysql_stmt_execute(stmt)) { throw mysql_error(connection); }
            MYSQL_BIND bind[1];
            my_bool is_null[1];
            unsigned long length[1];
            char* text_values[1];
            char b0[129]; text_values[0] = &b0[0];
            memset(bind, 0, sizeof(bind));
            for (int i = 0; i < 1; ++i)
            {
                bind[i].buffer_type = MYSQL_TYPE_STRING; bind[i].buffer = text_values[i]; bind[i].buffer_length = 128; bind[i].is_null = &is_null[0]; bind[i].length = &length[i];
            }
            mysql_stmt_bind_result(stmt, bind);
            while (mysql_stmt_fetch(stmt) != MYSQL_NO_DATA)
            {
                std::string* model_run = new std::string(text_values[0]);
                model_runs->push_back(model_run);
            }
            mysql_stmt_close(stmt);

            return model_runs;
        }
        catch (...)
        {
            printf("oops - that's an error in the program");
            return nullptr;
        }

    }
    std::vector<model::PopulationState*>* MySQLPersistenceProvider::read_population_states(std::string* model_run_key)
    {
        try
        {
            std::vector<model::PopulationState*>* population_states = new std::vector<model::PopulationState*>();
            char query[4096];
            sprintf_s
            (
                query
                , "select  "
                "  generation"
                " ,new_activity"
                " ,new_strain1_activity"
                " ,new_strain2_activity"
                " ,initial_state"
                " ,strain1_activity"
                " ,strain2_activity"
                " ,post_strain1_activity"
                " ,post_strain2_activity"
                " ,nets_with_fluctuation_and_strain1_activity"
                " ,nets_with_fluctuation_and_strain2_activity"
                " from population_state"
                "  where model_run_key = '%s' "
                "  order by generation"
                , model_run_key->c_str()
            );
            MYSQL_STMT* stmt = mysql_stmt_init(connection);
            mysql_stmt_prepare(stmt, query, -1);
            if (mysql_stmt_execute(stmt)) { throw mysql_error(connection); }
            MYSQL_BIND bind[11];
            my_bool is_null[11];
            unsigned long length[11];
            unsigned long long_values[11];
            memset(bind, 0, sizeof(bind));
            for (int i = 0; i < 11; ++i)
            {
                bind[i].buffer_type = MYSQL_TYPE_LONG; bind[i].buffer = (char*)(&(long_values[i])); bind[i].is_null = &is_null[0]; bind[i].length = &length[i];
            }
            mysql_stmt_bind_result(stmt, bind);
            while (mysql_stmt_fetch(stmt) != MYSQL_NO_DATA)
            {
                model::PopulationState* population_state
                    = new model::PopulationState(long_values[0], long_values[1], long_values[2], long_values[3], long_values[4], long_values[5]
                        , long_values[6], long_values[7], long_values[8], long_values[9], long_values[10]);
                population_states->push_back(population_state);
            }
            mysql_stmt_close(stmt);
            return population_states;
        }
        catch (...)
        {
            printf("oops - that's an error in the program");
            return nullptr;
        }
    }
    

}
#endif // USE mysql