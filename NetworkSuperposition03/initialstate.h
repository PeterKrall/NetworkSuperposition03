#ifndef MODEL_INITIALSTATE_H
#define MODEL_INITIALSTATE_H
#include "state.h"

namespace model
{

    class InitialState : virtual public State
    {
    public:
        InitialState();
        virtual double get_susceptibility(_state_builder spreader_state_builder);
        virtual _state_builder get_active_state_builder();
        virtual _state_builder get_state_builder();
        static State* state_builder(bool skip_non_contagious_period);
        virtual bool is_new_active() const final;
        virtual bool is_active_strain1() const final;
        virtual bool is_active_strain2() const final;
        virtual bool is_in_initial_state() const final;
        virtual bool is_post_strain_1_activation() const final;
        virtual bool is_post_strain_2_activation() const final;
    private:
        static _state_builder class_specific_state_builder;
    };

} // namespace model

#endif // MODEL_INITIALSTATE_H
