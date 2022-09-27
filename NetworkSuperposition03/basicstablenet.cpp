#include "basicstablenet.h"
#include <malloc.h>

namespace model
{

    BasicStableNet::BasicStableNet(unsigned int offset)
        :Net()
    {
        members = (Individual**)(malloc(sizeof(Individual*)*(size=Configuration::configuration->basic_stable_net_size)));
        for (unsigned int i = 0; i < Configuration::configuration->basic_stable_net_size; ++i)
        {
            Individual* member = *(Population::instance->get_members()+offset+i);
            *(members+i) = member;
            member->register_net(this);
        }
    }
    void* BasicStableNet::get_class_id() { return &class_id; }
    void* BasicStableNet::class_identifier = &class_id;
    unsigned int BasicStableNet::class_id;
    double BasicStableNet::get_strain1_transmission_probability()
    {
        return ((double)(Configuration::configuration->strain_1_exposition_in_basic_stable_net))/10000.0;
    }
    double BasicStableNet::get_strain2_transmission_probability()
    {
        return ((double)(Configuration::configuration->strain_2_exposition_in_basic_stable_net))/10000.0;
    }
} // namespace model
