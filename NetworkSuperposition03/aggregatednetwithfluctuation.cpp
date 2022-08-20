#include "aggregatednetwithfluctuation.h"
#include <stdlib.h>
#include "strain1state.h"
#include "strain2state.h"
#include <string>
namespace model
{

    AggregatedNetWithFluctuation::AggregatedNetWithFluctuation(BasicNetWithFluctuation** basic_nets)
        : Net()
    {
        this->basic_nets = basic_nets;
        members = (Individual**)(malloc(sizeof(Individual*)*(Configuration::configuration->aggregated_net_with_fluctuation_size)));
    }
    void* AggregatedNetWithFluctuation::get_class_id() { return &class_id; }
    void* AggregatedNetWithFluctuation::class_identifier = &class_id;
    unsigned int AggregatedNetWithFluctuation::class_id;
    double AggregatedNetWithFluctuation::get_strain1_transmission_probability()
    {
        return ((double)(Configuration::configuration->strain_1_transmission_probability_in_aggregated_net_with_fluctuation))/10000.0;
    }
    double AggregatedNetWithFluctuation::get_strain2_transmission_probability()
    {
        return ((double)(Configuration::configuration->strain_2_transmission_probability_in_aggregated_net_with_fluctuation))/10000.0;
    }
    void AggregatedNetWithFluctuation::update_transmission_probabilities()
    {
        update_content();
        Net::update_transmission_probabilities();
    }
    void AggregatedNetWithFluctuation::update_content()
    {
        while (actual_size != 0)
        {
            actual_size--;
            Individual* individual = *(members+actual_size);
            individual->deregister_net(this);
            *(members+actual_size) = nullptr;
        }
        while (actual_size != (size = Configuration::configuration->aggregated_net_with_fluctuation_size))
        {
            int r = rand()%(Configuration::configuration->basic_net_with_fluctuation_number);
            BasicNetWithFluctuation* basic_net = *(basic_nets+r);
            r = rand()%(basic_net->get_size());
            Individual* individual = *(basic_net->get_members()+r);
            if (!individual->is_included(this))
            {
                *(members+actual_size) = individual;
                individual->register_net(this);
                actual_size++;
            }
        }
        if (Configuration::configuration->generation==10)
        {
            initialize_activity(std::string(Configuration::configuration->initial_strain1cases), Strain1State::get_state_builder());
        }
        if (Configuration::configuration->generation == Configuration::configuration->first_strain2_appearance)
        {            
            initialize_activity(std::string(Configuration::configuration->initial_strain2cases), Strain2State::get_state_builder());
        }
    }
} // namespace model
