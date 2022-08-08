#ifdef USE_FILE_OUTPUT

#include "file_writer.h"
#include "configuration.h"

namespace persistence
{
    using namespace model;
	FileWriter::FileWriter(char* model_run_key) : Writer(model_run_key)
	{
        char buffer[4096];
        sprintf_s   (
                  buffer
                    , "%s%s_%s_%s.txt"
                    , Configuration::configuration->output_directory.c_str()
                    , Configuration::configuration->label.c_str()
                    , ((Configuration::configuration->shuffle_stable_nets) ? "Y" : "N")
                    , model_run_key
                    );
        out.open(buffer);
        sprintf_s(
            buffer
            ,
            "  strain_1_transmission_probability_in_aggregated_net_with_fluctuation = %d\n"
            ", strain_1_transmission_probability_in_aggregated_stable_net = %d\n"
            ", strain_1_transmission_probability_in_basic_net_with_fluctuation = %d\n"
            ", strain_1_transmission_probability_in_basic_stable_net = %d\n"
            ", strain_2_transmission_probability_in_aggregated_net_with_fluctuation = %d\n"
            ", strain_2_transmission_probability_in_aggregated_stable_net = %d\n"
            ", strain_2_transmission_probability_in_basic_net_with_fluctuation = %d\n"
            ", strain_2_transmission_probability_in_basic_stable_net = %d\n"
            ", aggregated_net_with_fluctuation_number = %d\n"
            ", aggregated_net_with_fluctuation_size = %d\n"
            ", aggregated_stable_net_size = %d\n"
            ", basic_net_with_fluctuation_fluctuation = %d\n"
            ", basic_net_with_fluctuation_number = %d\n"
            ", basic_net_with_fluctuation_size = %d\n"
            ", basic_stable_net_size = %d\n"
            ", population_size = %d\n"
            ", strain1_random_transmission_probability = %d\n"
            ", strain2_random_transmission_probability = %d\n"
            ", aggregated stable nets based on shuffled population ? %s\n"
            ", strain_1_contagiousness_begin = %d\n"
            ", strain_1_contagiousness_end = %d\n"
            ", strain_2_contagiousness_begin = %d\n"
            ", strain_2_contagiousness_end = %d\n"
            ", immunity_reduction_time_of_strain1_for_strain_2_exposition = %d\n"
            ", immunity_reduction_weight_of_strain1_for_strain_2_exposition = %d\n"
            ", initial_strain1cases = %s\n"
            ", initial_strain2cases = %s\n"
            ", first_strain2_appearance = %d\n"
            "\n"
            , Configuration::configuration->strain_1_transmission_probability_in_aggregated_net_with_fluctuation
            , Configuration::configuration->strain_1_transmission_probability_in_aggregated_stable_net
            , Configuration::configuration->strain_1_transmission_probability_in_basic_net_with_fluctuation
            , Configuration::configuration->strain_1_transmission_probability_in_basic_stable_net
            , Configuration::configuration->strain_2_transmission_probability_in_aggregated_net_with_fluctuation
            , Configuration::configuration->strain_2_transmission_probability_in_aggregated_stable_net
            , Configuration::configuration->strain_2_transmission_probability_in_basic_net_with_fluctuation
            , Configuration::configuration->strain_2_transmission_probability_in_basic_stable_net
            , Configuration::configuration->aggregated_net_with_fluctuation_number
            , Configuration::configuration->aggregated_net_with_fluctuation_size
            , Configuration::configuration->aggregated_stable_net_size
            , Configuration::configuration->basic_net_with_fluctuation_fluctuation
            , Configuration::configuration->basic_net_with_fluctuation_number
            , Configuration::configuration->basic_net_with_fluctuation_size
            , Configuration::configuration->basic_stable_net_size
            , Configuration::configuration->population_size
            , Configuration::configuration->strain1_random_transmission_probability
            , Configuration::configuration->strain2_random_transmission_probability
            , ((Configuration::configuration->shuffle_stable_nets) ? "Y" : "N")
            , Configuration::configuration->strain_1_contagiousness_begin
            , Configuration::configuration->strain_1_contagiousness_end
            , Configuration::configuration->strain_2_contagiousness_begin
            , Configuration::configuration->strain_2_contagiousness_end
            , Configuration::configuration->immunity_reduction_time_of_strain1_for_strain_2_exposition
            , Configuration::configuration->immunity_reduction_weight_of_strain1_for_strain_2_exposition
            , Configuration::configuration->initial_strain1cases.c_str()
            , Configuration::configuration->initial_strain2cases.c_str()
            , Configuration::configuration->first_strain2_appearance
        );
        out << buffer;
        out.flush();
	}
    FileWriter::~FileWriter()
    {
        out.flush();
        out.close();
    }
    FileWriter* FileWriter::instance = nullptr;
    model::Writer* FileWriter::create(char* model_run_key) { return (instance = new FileWriter(model_run_key));  }
    void FileWriter::destroy(model::Writer* writer) 
    {         
        if (instance == nullptr || writer != instance) 
        {
            throw "oops";
        }
        delete instance;
        instance = nullptr;
    }

    void FileWriter::persist_population_state(PopulationState* population_state)
    {
        char buffer[4096];
        sprintf_s(
            buffer
            , "length_of_activity = %d"
            ",new_activity = %d"
            ",new_strain1_activity = %d"
            ",new_strain2_activity = %d"
            ",initial_state = %d"
            ",strain1_activity = %d"
            ",strain2_activity = %d"
            ",post_strain1_activity = %d"
            ",post_strain2_activity = %d"
            ",nets_with_fluctuation_and_strain1_activity = %d"
            ",nets_with_fluctuation_and_strain2_activity = %d"
            "\n"
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
        out << buffer;
    }
    bool FileWriter::is_activated = activate_conditionally();
    
    bool FileWriter::activate_conditionally()
    {
#ifdef USE_PURE_FILE_OUTPUT
        Writer::open_writer = &FileWriter::create;
        Writer::close_writer = &FileWriter::destroy;
        return true;
#else
        return false;
#endif // USE_PURE_FILE_OUTPUT
    }
}

#endif