#ifndef MODEL_AGGREGATEDSTABLENET_H
#define MODEL_AGGREGATEDSTABLENET_H

#include "net.h"

namespace model
{
    class AggregatedStableNet : virtual public model::Net
    {
    public:
        AggregatedStableNet(unsigned int offset);
        void* get_class_id();
        static unsigned int class_id;
        virtual double get_strain1_transmission_probability();
        virtual double get_strain2_transmission_probability();
        static void* class_identifier;
    };
} // namespace model

#endif // MODEL_AGGREGATEDSTABLENET_H
