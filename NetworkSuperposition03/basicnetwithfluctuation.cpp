#include "basicnetwithfluctuation.h"
#include "strain1state.h"
#include "strain2state.h"
#include <malloc.h>

namespace model
{

    BasicNetWithFluctuation::BasicNetWithFluctuation(AggregatedStableNet** aggregated_stable_nets)
        :Net()
    {
        this->aggregated_stable_nets = aggregated_stable_nets;
        members = (Individual**)(malloc(sizeof(Individual*)*(size=Configuration::configuration->basic_net_with_fluctuation_size)));
        unsigned int actual_size = 0;
        while (actual_size != Configuration::configuration->basic_net_with_fluctuation_size)
        {
            *(members+actual_size) = get_next_member();
            actual_size++;
        }
    }
    bool BasicNetWithFluctuation:: BasicNetWithFluctuation::has_strain1_actvity()
    {
        for (unsigned int i = 0; i < size; i++)
        {
            Individual* member = *(members+i);
            if (member->get_spreader_state_builder() == Strain1State::get_state_builder()) { return true; }
        }
        return false;
    }
    bool BasicNetWithFluctuation::has_strain2_actvity()
    {
        for (unsigned int i = 0; i < size; i++)
        {
            Individual* member = *(members+i);
            if (member->get_spreader_state_builder() == Strain2State::get_state_builder()) { return true; }
        }
        return false;
    }

    void* BasicNetWithFluctuation::get_class_id() { return &class_id; }
    void* BasicNetWithFluctuation::class_identifier = &class_id;
    unsigned int BasicNetWithFluctuation::class_id;
    double BasicNetWithFluctuation::get_strain1_transmission_probability()
    {
        return ((double)(Configuration::configuration->strain_1_transmission_probability_in_basic_net_with_fluctuation))/10000.0;
    }
    double BasicNetWithFluctuation::get_strain2_transmission_probability()
    {
        return ((double)(Configuration::configuration->strain_2_transmission_probability_in_basic_net_with_fluctuation))/10000.0;
    }
    void BasicNetWithFluctuation::update_transmission_probabilities()
    {
        unsigned int fluctuation_count = 0;
        while (fluctuation_count++ != Configuration::configuration->basic_net_with_fluctuation_fluctuation)
        {
            unsigned int position = rand()%size;
            Individual* former_member = *(members+position);
            former_member->deregister_net(this);
            *(members+position) = get_next_member();
        }
        Net::update_transmission_probabilities();
    }
    Individual* BasicNetWithFluctuation::get_next_member()
    {
        Individual* individual = Population::instance->get_random_member();
        if (!individual->is_included(this))
        {
            individual->register_net(this);
            return individual;
        }
        else
        {
            return get_next_member();
        }
    }
} // namespace model
