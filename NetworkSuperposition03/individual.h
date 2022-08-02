#ifndef MODEL_INDIVIDUAL_H
#define MODEL_INDIVIDUAL_H
#include "state.h"
#include <vector>


namespace model
{
    class Individual
    {
    public:
        Individual(unsigned int index);
        const unsigned int index;
        virtual void register_net(class Net* net) final;
        virtual void deregister_net(class Net* net) final;
        virtual bool is_included(class Net* net) const final;
        virtual bool interact_with_environment();
        virtual _state_builder get_spreader_state_builder() const;
        virtual void activate(_state_builder state_builder, bool skip_non_contagious_period);
        virtual bool is_new_active() const final;
        virtual bool is_active_strain1() const final;
        virtual bool is_active_strain2() const final;
        virtual bool is_in_initial_state() const final;
        virtual bool is_post_strain_1_activation() const final;
        virtual bool is_post_strain_2_activation() const final;
        virtual bool spread() const final;
    private:
        State* state;
        std::vector<class Net*>* including_nets = new std::vector<class Net*>();
    };
} // namespace model

#endif // MODEL_INDIVIDUAL_H
