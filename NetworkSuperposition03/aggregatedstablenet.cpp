#include "aggregatedstablenet.h"
#include <malloc.h>
namespace model
{

    AggregatedStableNet::AggregatedStableNet(unsigned int offset)
        :Net()
    {
        members = (Individual**)(malloc(sizeof(Individual*)*(size=Configuration::configuration->aggregated_stable_net_size)));
        for (unsigned int i = 0; i < Configuration::configuration->aggregated_stable_net_size; ++i)
        {
            
            Individual* member = *(Population::instance->get_shuffled_members() + offset + i);
            *(members+i) = member;
            member->register_net(this);
        }
    }
    void* AggregatedStableNet::get_class_id() { return &class_id; }
    void* AggregatedStableNet::class_identifier = &class_id;
    unsigned int AggregatedStableNet::class_id;
    double AggregatedStableNet::get_strain1_transmission_probability()
    {
        return ((double)(Configuration::configuration->strain_1_transmission_probability_in_aggregated_stable_net))/10000.0;
    }
    double AggregatedStableNet::get_strain2_transmission_probability()
    {
        return ((double)(Configuration::configuration->strain_2_transmission_probability_in_aggregated_stable_net))/10000.0;
    }
} // namespace model
