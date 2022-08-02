#ifndef MODEL_STATE_H
#define MODEL_STATE_H

// the state of an individual
namespace model
{
    typedef class State* (*_state_builder)(bool skip_non_contagious_period);
    class State
    {
    public:
        State(unsigned int time_to_date_back_activation);
        virtual _state_builder get_active_state_builder() = 0;
        virtual double get_susceptibility(_state_builder spreader_state_builder) = 0;
        virtual unsigned int age() const final;
        virtual bool is_new_active() const = 0;
        virtual bool is_active_strain1() const = 0;
        virtual bool is_active_strain2() const = 0;
        virtual bool is_in_initial_state() const = 0;
        virtual bool is_post_strain_1_activation() const = 0;
        virtual bool is_post_strain_2_activation() const = 0;
    protected:
        const unsigned int time_of_activation;
    };

} // namespace model

#endif // MODEL_STATE_H
