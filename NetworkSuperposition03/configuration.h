#ifndef CONFIGURATION_H
#define CONFIGURATION_H
#include <vector>
#include <string>

namespace model
{    
    class Configuration
    {
    public:
        Configuration();
        const unsigned int strain_1_transmission_probability_in_aggregated_net_with_fluctuation;
        const unsigned int strain_1_transmission_probability_in_aggregated_stable_net;
        const unsigned int strain_1_transmission_probability_in_basic_net_with_fluctuation;
        const unsigned int strain_1_transmission_probability_in_basic_stable_net;
        const unsigned int strain_2_transmission_probability_in_aggregated_net_with_fluctuation;
        const unsigned int strain_2_transmission_probability_in_aggregated_stable_net;
        const unsigned int strain_2_transmission_probability_in_basic_net_with_fluctuation;
        const unsigned int strain_2_transmission_probability_in_basic_stable_net;
        const unsigned int aggregated_net_with_fluctuation_number;
        const unsigned int aggregated_net_with_fluctuation_size;
        const unsigned int aggregated_stable_net_size;
        const unsigned int basic_net_with_fluctuation_fluctuation;
        const unsigned int basic_net_with_fluctuation_number;
        const unsigned int basic_net_with_fluctuation_size;
        const unsigned int basic_stable_net_size;
        const unsigned int population_size;
        const unsigned int strain1_random_transmission_probability;
        const unsigned int strain2_random_transmission_probability;
        //
        const unsigned int aggregated_stable_net_shuffle;
        const unsigned int strain_1_contagiousness_begin;
        const unsigned int strain_1_contagiousness_end;
        const unsigned int strain_2_contagiousness_begin;
        const unsigned int strain_2_contagiousness_end;
        const unsigned int immunity_reduction_time_of_strain1_for_strain_2_exposition;
        const unsigned int immunity_reduction_weight_of_strain1_for_strain_2_exposition;
        const std::string initial_strain1cases;
        const std::string initial_strain2cases;
        const unsigned int first_strain2_appearance;
        const std::string output_directory;
        const std::string label;
        Configuration
        (
          unsigned int strain_1_transmission_probability_in_aggregated_net_with_fluctuation
        , unsigned int strain_1_transmission_probability_in_aggregated_stable_net
        , unsigned int strain_1_transmission_probability_in_basic_net_with_fluctuation
        , unsigned int strain_1_transmission_probability_in_basic_stable_net
        , unsigned int strain_2_transmission_probability_in_aggregated_net_with_fluctuation
        , unsigned int strain_2_transmission_probability_in_aggregated_stable_net
        , unsigned int strain_2_transmission_probability_in_basic_net_with_fluctuation
        , unsigned int strain_2_transmission_probability_in_basic_stable_net
        , unsigned int aggregated_net_with_fluctuation_number
        , unsigned int aggregated_net_with_fluctuation_size
        , unsigned int aggregated_stable_net_size
        , unsigned int basic_net_with_fluctuation_fluctuation
        , unsigned int basic_net_with_fluctuation_number
        , unsigned int basic_net_with_fluctuation_size
        , unsigned int basic_stable_net_size
        , unsigned int population_size
        , unsigned int strain1_random_transmission_probability
        , unsigned int strain2_random_transmission_probability
        , unsigned int aggregated_stable_net_shuffle
        //
        , unsigned int strain_1_contagiousness_begin
        , unsigned int strain_1_contagiousness_end
        , unsigned int strain_2_contagiousness_begin
        , unsigned int strain_2_contagiousness_end
        , unsigned int first_strain2_appearance
        , unsigned int immunity_reduction_time_of_strain1_for_strain_2_exposition
        , unsigned int immunity_reduction_weight_of_strain1_for_strain_2_exposition
        , const char* initial_strain1cases
        , const char* initial_strain2cases
        , const char* output_directory
        , const char* label
        );
        //
        static Configuration* configuration;
        unsigned int generation = 0;
    };
} // namespace modell

#endif // MODELL_CONFIGURATION_H
