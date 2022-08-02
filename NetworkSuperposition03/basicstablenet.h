#ifndef MODEL_BASICSTABLENET_H
#define MODEL_BASICSTABLENET_H
#include "net.h"

namespace model
{

    class BasicStableNet : virtual public Net
    {
    public:
        BasicStableNet(unsigned int offset);
        void* get_class_id();
        static unsigned int class_id;
        virtual double get_strain1_transmission_probability();
        virtual double get_strain2_transmission_probability();
        static void* class_identifier;
    };

} // namespace model

#endif // MODEL_BASICSTABLENET_H
