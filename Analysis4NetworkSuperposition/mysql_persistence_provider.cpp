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

    static bool is_activated = MySQLPersistenceProvider::activate();

    bool MySQLPersistenceProvider::activate()
    {
        if (PersistenceProvider::get_persistence_provider_instance_implementation == nullptr)
        {
            PersistenceProvider::get_persistence_provider_instance_implementation
                = &MySQLPersistenceProvider::get_instance;
            PersistenceProvider::close_persistence_provider_instance_implementation
                = &MySQLPersistenceProvider::close_instance;
        }
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
    void MySQLPersistenceProvider::persist(analysis::ModelRunStatistics* model_run_statistics, const char* model_run_key)
    {
        char query[4096];
        try
        {
            sprintf_s
            (
                  query
                , "update header set "
                "  max = %d "
                ", max_1 = %d "
                ", max_2= %d "
                ", max_post_1= %d "
                ", post_1= %d "
                ", post_2= %d "
                ", initial= %d "
                ", length= %d "
                ", time_to_dominance= %d "
                ", first_close_max= %d "
                ", last_close_max= %d "
                ", time_to_complete_replacement= %d "
                ", immunity_at_peak = %f "
                ", immunity_at_end = %f "
                ", immunity_at_last_90pcnt_max = %f "
                ", immunity_at_last_75pcnt_max = %f "
                ", immunity_at_complete_replacement = %f "
                " where model_run_key = '%s' "
                , model_run_statistics->max
                , model_run_statistics->max_1
                , model_run_statistics->max_2
                , model_run_statistics->max_post_1
                , model_run_statistics->post_1
                , model_run_statistics->post_2
                , model_run_statistics->initial
                , model_run_statistics->length
                , model_run_statistics->time_to_dominance
                , model_run_statistics->first_close_max
                , model_run_statistics->last_close_max
                , model_run_statistics->time_to_complete_replacement
                , model_run_statistics->immunity_at_peak
                , model_run_statistics->immunity_at_end
                , model_run_statistics->immunity_at_last_90pcnt_max
                , model_run_statistics->immunity_at_last_75pcnt_max
                , model_run_statistics->immunity_at_complete_replacement
                , model_run_key
            );
            
            MYSQL_STMT* stmt = mysql_stmt_init(connection);
            mysql_stmt_prepare(stmt, query, -1);
            if (mysql_stmt_execute(stmt)) { throw mysql_error(connection); }
            mysql_stmt_close(stmt);
        }
        catch (...)
        {
            printf("oops - that's an error in the program");
        }
    }
    void MySQLPersistenceProvider::erase_configuration_statistics()
    {
        char query[4096];
        try
        {
            sprintf_s
            (
                query
                , "delete from configuration_statistics"
            );
            MYSQL_STMT* stmt = mysql_stmt_init(connection);
            mysql_stmt_prepare(stmt, query, -1);
            if (mysql_stmt_execute(stmt)) { throw mysql_error(connection); }
            mysql_stmt_close(stmt);
        }
        catch (...)
        {
            printf("oops - that's an error in the program");
        }
    }
    void MySQLPersistenceProvider::insert_configuration_statistics(analysis::ConfigurationStatistics& configuration_statistics)
    {
        char query[8192];
        sprintf_s(
            query
            , "insert into configuration_statistics "
            "( "
            "  label "
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
            " ,initial_strain1cases "
            " ,initial_strain2cases "
            " ,first_strain2_appearance "
            " ,number_of_runs "
            " ,max_max_new "
            " ,min_max_new "
            " ,mean_max_new "
            " ,standard_deviation_max_new "
            " ,max_max1_new "
            " ,min_max1_new "
            " ,mean_max1_new "
            " ,standard_deviation_max1_new "
            " ,max_max2_new "
            " ,min_max2_new "
            " ,mean_max2_new "
            " ,standard_deviation_max2_new "
            " ,max_max_post1 "
            " ,min_max_post1 "
            " ,mean_max_post1 "
            " ,standard_deviation_max_post1 "
            " ,max_post1_at_end "
            " ,min_post1_at_end "
            " ,mean_post1_at_end "
            " ,standard_deviation_post1_at_end "
            " ,max_post2_at_end "
            " ,min_post2_at_end "
            " ,mean_post2_at_end "
            " ,standard_deviation_post2_at_end "
            " ,max_length "
            " ,min_length "
            " ,mean_length "
            " ,standard_deviation_length "
            " ,max_time_to_complete_replacement "
            " ,min_time_to_complete_replacement "
            " ,mean_time_to_complete_replacement "
            " ,standard_deviation_time_to_complete_replacement "
            " ,max_time_to_dominance "
            " ,min_time_to_dominance "
            " ,mean_time_to_dominance "
            " ,standard_deviation_time_to_dominance "
            " ,max_immunity_at_peak "
            " ,min_immunity_at_peak "
            " ,mean_immunity_at_peak "
            " ,standard_deviation_immunity_at_peak "
            " ,max_immunity_at_end "
            " ,min_immunity_at_end "
            " ,mean_immunity_at_end "
            " ,standard_deviation_immunity_at_end "
            " ,max_immunity_at_complete_replacement "
            " ,min_immunity_at_complete_replacement "
            " ,mean_immunity_at_complete_replacement "
            " ,standard_deviation_immunity_at_complete_replacement "
            " ,max_immunity_at_last_90pcnt_max "
            " ,min_immunity_at_last_90pcnt_max "
            " ,mean_immunity_at_last_90pcnt_max "
            " ,standard_deviation_immunity_at_last_90pcnt_max "
            " ,max_immunity_at_last_75pcnt_max "
            " ,min_immunity_at_last_75pcnt_max "
            " ,mean_immunity_at_last_75pcnt_max "
            " ,standard_deviation_immunity_at_last_75pcnt_max "
            ") values ( "
            " '%s',%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,'%s','%s',%d, %d "
            " ,%d, %d, %f, %f"
            " ,%d, %d, %f, %f"
            " ,%d, %d, %f, %f"
            " ,%d, %d, %f, %f"
            " ,%d, %d, %f, %f"
            " ,%d, %d, %f, %f"
            " ,%d, %d, %f, %f"
            " ,%d, %d, %f, %f"
            " ,%d, %d, %f, %f"
            " ,%f, %f, %f, %f"
            " ,%f, %f, %f, %f"
            " ,%f, %f, %f, %f"
            " ,%f, %f, %f, %f"
            " ,%f, %f, %f, %f"
            ") "
            , configuration_statistics.label.c_str()
            , configuration_statistics.strain_1_transmission_probability_in_aggregated_net_with_fluctuation
            , configuration_statistics.strain_1_transmission_probability_in_aggregated_stable_net
            , configuration_statistics.strain_1_transmission_probability_in_basic_net_with_fluctuation
            , configuration_statistics.strain_1_transmission_probability_in_basic_stable_net
            , configuration_statistics.strain_2_transmission_probability_in_aggregated_net_with_fluctuation
            , configuration_statistics.strain_2_transmission_probability_in_aggregated_stable_net
            , configuration_statistics.strain_2_transmission_probability_in_basic_net_with_fluctuation
            , configuration_statistics.strain_2_transmission_probability_in_basic_stable_net
            , configuration_statistics.aggregated_net_with_fluctuation_number
            , configuration_statistics.aggregated_net_with_fluctuation_size
            , configuration_statistics.aggregated_stable_net_size
            , configuration_statistics.basic_net_with_fluctuation_fluctuation
            , configuration_statistics.basic_net_with_fluctuation_number
            , configuration_statistics.basic_net_with_fluctuation_size
            , configuration_statistics.basic_stable_net_size
            , configuration_statistics.population_size
            , configuration_statistics.strain1_random_transmission_probability
            , configuration_statistics.strain2_random_transmission_probability
            , configuration_statistics.aggregated_stable_net_shuffle
            , configuration_statistics.strain_1_contagiousness_begin
            , configuration_statistics.strain_1_contagiousness_end
            , configuration_statistics.strain_2_contagiousness_begin
            , configuration_statistics.strain_2_contagiousness_end
            , configuration_statistics.immunity_reduction_time_of_strain1_for_strain_2_exposition
            , configuration_statistics.immunity_reduction_weight_of_strain1_for_strain_2_exposition
            , configuration_statistics.initial_strain1cases.c_str()
            , configuration_statistics.initial_strain2cases.c_str()
            , configuration_statistics.first_strain2_appearance
            , configuration_statistics.number_of_runs
            , configuration_statistics.max_max_new
            , configuration_statistics.min_max_new
            , configuration_statistics.mean_max_new
            , configuration_statistics.standard_deviation_max_new
            , configuration_statistics.max_max1_new
            , configuration_statistics.min_max1_new
            , configuration_statistics.mean_max1_new
            , configuration_statistics.standard_deviation_max1_new
            , configuration_statistics.max_max2_new
            , configuration_statistics.min_max2_new
            , configuration_statistics.mean_max2_new
            , configuration_statistics.standard_deviation_max2_new
            , configuration_statistics.max_max_post1
            , configuration_statistics.min_max_post1
            , configuration_statistics.mean_max_post1
            , configuration_statistics.standard_deviation_max_post1
            , configuration_statistics.max_post1_at_end
            , configuration_statistics.min_post1_at_end
            , configuration_statistics.mean_post1_at_end
            , configuration_statistics.standard_deviation_post1_at_end
            , configuration_statistics.max_post2_at_end
            , configuration_statistics.min_post2_at_end
            , configuration_statistics.mean_post2_at_end
            , configuration_statistics.standard_deviation_post2_at_end
            , configuration_statistics.max_length
            , configuration_statistics.min_length
            , configuration_statistics.mean_length
            , configuration_statistics.standard_deviation_length
            , configuration_statistics.max_time_to_complete_replacement
            , configuration_statistics.min_time_to_complete_replacement
            , configuration_statistics.mean_time_to_complete_replacement
            , configuration_statistics.standard_deviation_time_to_complete_replacement
            , configuration_statistics.max_time_to_dominance
            , configuration_statistics.min_time_to_dominance
            , configuration_statistics.mean_time_to_dominance
            , configuration_statistics.standard_deviation_time_to_dominance
            , configuration_statistics.max_immunity_at_peak
            , configuration_statistics.min_immunity_at_peak
            , configuration_statistics.mean_immunity_at_peak
            , configuration_statistics.standard_deviation_immunity_at_peak
            , configuration_statistics.max_immunity_at_end
            , configuration_statistics.min_immunity_at_end
            , configuration_statistics.mean_immunity_at_end
            , configuration_statistics.standard_deviation_immunity_at_end
            , configuration_statistics.max_immunity_at_complete_replacement
            , configuration_statistics.min_immunity_at_complete_replacement
            , configuration_statistics.mean_immunity_at_complete_replacement
            , configuration_statistics.standard_deviation_immunity_at_complete_replacement
            , configuration_statistics.max_immunity_at_last90pcnt_max
            , configuration_statistics.min_immunity_at_last90pcnt_max
            , configuration_statistics.mean_immunity_at_last90pcnt_max
            , configuration_statistics.standard_deviation_immunity_at_last90pcnt_max
            , configuration_statistics.max_immunity_at_last75pcnt_max
            , configuration_statistics.min_immunity_at_last75pcnt_max
            , configuration_statistics.mean_immunity_at_last75pcnt_max
            , configuration_statistics.standard_deviation_immunity_at_last75pcnt_max
            );
        if (mysql_query(connection, query))
        {
            throw mysql_error(connection);
        }
    }

}
#endif // USE mysql