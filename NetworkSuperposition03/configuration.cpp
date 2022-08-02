
#include "configuration.h"
namespace model {

    Configuration::Configuration()
    : strain_1_transmission_probability_in_aggregated_net_with_fluctuation (50)
    , strain_1_transmission_probability_in_aggregated_stable_net (200)
    , strain_1_transmission_probability_in_basic_net_with_fluctuation (500)
    , strain_1_transmission_probability_in_basic_stable_net (1000)
    , strain_2_transmission_probability_in_aggregated_net_with_fluctuation(75)
    , strain_2_transmission_probability_in_aggregated_stable_net (300)
    , strain_2_transmission_probability_in_basic_net_with_fluctuation (750)
    , strain_2_transmission_probability_in_basic_stable_net (1500)
    , aggregated_net_with_fluctuation_number (1)
    , aggregated_net_with_fluctuation_size (150)
    , aggregated_stable_net_size (14)
    , basic_net_with_fluctuation_fluctuation(10)
    , basic_net_with_fluctuation_number (5)
    , basic_net_with_fluctuation_size (42)
    , basic_stable_net_size (3)
    , population_size(1680000)
    , strain1_random_transmission_probability(100)
    , strain2_random_transmission_probability(150)
    , shuffle_stable_nets(true)
    , strain_1_contagiousness_begin(3)
    , strain_1_contagiousness_end(5)
    , strain_2_contagiousness_begin(3)
    , strain_2_contagiousness_end(5)
    , immunity_reduction_time_of_strain1_for_strain_2_exposition(5000)
    , immunity_reduction_weight_of_strain1_for_strain_2_exposition(50)
    , first_strain2_appearance(100)
    , initial_strain1cases("3,5,7,11,13")
    , initial_strain2cases("71,73,79,83,89")
    , output_directory("c:/temp/")
    {}
    Configuration::Configuration
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
    , bool shuffle_stable_nets    
    //
    , unsigned int strain_1_contagiousness_begin
    , unsigned int strain_1_contagiousness_end
    , unsigned int strain_2_contagiousness_begin
    , unsigned int strain_2_contagiousness_end
    , unsigned int immunity_reduction_time_of_strain1_for_strain_2_exposition
    , unsigned int immunity_reduction_weight_of_strain1_for_strain_2_exposition
    , const char* initial_strain1cases
    , const char* initial_strain2cases
    , unsigned int first_strain2_appearance
    , const char* output_directory
    )
    : strain_1_transmission_probability_in_aggregated_net_with_fluctuation (strain_1_transmission_probability_in_aggregated_net_with_fluctuation)
    , strain_1_transmission_probability_in_aggregated_stable_net (strain_1_transmission_probability_in_aggregated_stable_net)
    , strain_1_transmission_probability_in_basic_net_with_fluctuation (strain_1_transmission_probability_in_basic_net_with_fluctuation)
    , strain_1_transmission_probability_in_basic_stable_net (strain_1_transmission_probability_in_basic_stable_net)
    , strain_2_transmission_probability_in_aggregated_net_with_fluctuation (strain_2_transmission_probability_in_aggregated_net_with_fluctuation)
    , strain_2_transmission_probability_in_aggregated_stable_net (strain_2_transmission_probability_in_aggregated_stable_net)
    , strain_2_transmission_probability_in_basic_net_with_fluctuation (strain_2_transmission_probability_in_basic_net_with_fluctuation)
    , strain_2_transmission_probability_in_basic_stable_net (strain_2_transmission_probability_in_basic_stable_net)
    , aggregated_net_with_fluctuation_number (aggregated_net_with_fluctuation_number)
    , aggregated_net_with_fluctuation_size (aggregated_net_with_fluctuation_size)
    , aggregated_stable_net_size (aggregated_stable_net_size)
    , basic_net_with_fluctuation_fluctuation(basic_net_with_fluctuation_fluctuation)
    , basic_net_with_fluctuation_number (basic_net_with_fluctuation_number)
    , basic_net_with_fluctuation_size (basic_net_with_fluctuation_size)
    , basic_stable_net_size (basic_stable_net_size)
    , population_size(population_size)
    , strain1_random_transmission_probability(strain1_random_transmission_probability)
    , strain2_random_transmission_probability(strain2_random_transmission_probability)
    , shuffle_stable_nets(shuffle_stable_nets)
    , strain_1_contagiousness_begin(strain_1_contagiousness_begin)
    , strain_1_contagiousness_end(strain_1_contagiousness_end)
    , strain_2_contagiousness_begin(strain_2_contagiousness_begin)
    , strain_2_contagiousness_end(strain_2_contagiousness_end)
    , immunity_reduction_time_of_strain1_for_strain_2_exposition(immunity_reduction_time_of_strain1_for_strain_2_exposition)
    , immunity_reduction_weight_of_strain1_for_strain_2_exposition(immunity_reduction_weight_of_strain1_for_strain_2_exposition)
    , first_strain2_appearance(first_strain2_appearance)
    , initial_strain1cases(initial_strain1cases)
    , initial_strain2cases(initial_strain2cases)
    , output_directory(output_directory)
    {}



    Configuration* Configuration::configuration = new Configuration();

} // namespace modell
