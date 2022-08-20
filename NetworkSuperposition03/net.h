#ifndef MODEL_NET_H
#define MODEL_NET_H
#include "configuration.h"
#include "population.h"

namespace model 
{

    class Net
    {
    public:
        Net();
        virtual double get_strain1_transmission_probability() = 0;
        virtual double get_strain2_transmission_probability() = 0;
        virtual void* get_class_id() = 0;
        virtual void update_transmission_probabilities();
        virtual double get_strain1_transmission_probability_complement() const final;
        virtual double get_strain2_transmission_probability_complement() const final;
        virtual Individual** get_members() const final;
        virtual unsigned int get_size() const final;
        virtual bool count_activity(unsigned int* new_activity,unsigned int* strain1_activity,unsigned int* strain2_activity, unsigned int* individuals_in_initial_state) const final;
    protected:        
        Individual** members;
        unsigned int size = 0;
        unsigned int initialize_activity(std::string& initial_cases_string, _state_builder state_builder);
    private:
        double strain1_transmission_probability_complement = 1.0;
        double strain2_transmission_probability_complement = 1.0;
    };

} // namespace model

#endif // MODEL_NET_H
