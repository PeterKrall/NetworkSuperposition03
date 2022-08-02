#ifndef MODEL_AGGREGATEDNETWITHFLUCTUATION_H
#define MODEL_AGGREGATEDNETWITHFLUCTUATION_H

#include "net.h"
#include "basicnetwithfluctuation.h"
namespace model
{

    class AggregatedNetWithFluctuation : virtual public model::Net
    {
    public:
        AggregatedNetWithFluctuation(BasicNetWithFluctuation** basic_nets);
        void* get_class_id();
        static unsigned int class_id;
        virtual double get_strain1_transmission_probability();
        virtual double get_strain2_transmission_probability();
        static void* class_identifier;
        virtual void update_transmission_probabilities();
    private:
        BasicNetWithFluctuation** basic_nets;
        virtual void update_content();
        unsigned int actual_size = 0;
    };

} // namespace model

#endif // MODEL_AGGREGATEDNETWITHFLUCTUATION_H
