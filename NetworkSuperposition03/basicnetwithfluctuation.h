#ifndef MODEL_BASICNETWITHFLUCTUATION_H
#define MODEL_BASICNETWITHFLUCTUATION_H

#include "net.h"
#include "aggregatedstablenet.h"
#include <vector>
namespace model
{

    class BasicNetWithFluctuation : virtual public model::Net
    {
    public:
        BasicNetWithFluctuation(AggregatedStableNet** aggregated_stable_nets);
        void* get_class_id();
        static unsigned int class_id;
        virtual double get_strain1_transmission_probability();
        virtual double get_strain2_transmission_probability();
        static void* class_identifier;
        virtual void update_transmission_probabilities();
        virtual bool has_strain1_actvity();
        virtual bool has_strain2_actvity();
    private:
        AggregatedStableNet** aggregated_stable_nets;
        Individual* get_next_member();
    };

} // namespace model

#endif // MODEL_BASICNETWITHFLUCTUATION_H
