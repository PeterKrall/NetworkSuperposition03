#include "strain1state.h"
#include "configuration.h"
#include "strain2state.h"

namespace model
{

    Strain1State::Strain1State(unsigned int time_to_date_back_activation) : State(time_to_date_back_activation) {}
    _state_builder Strain1State::get_active_state_builder()
    {
        if (age() < Configuration::configuration->strain_1_contagiousness_begin || age() > Configuration::configuration->strain_1_contagiousness_end)
        {
            return nullptr;
        }
        else
        {
            return get_state_builder();
        }
    }
    _state_builder Strain1State::get_state_builder() { return class_specific_state_builder; }
    _state_builder Strain1State::class_specific_state_builder = &Strain1State::state_builder;
    State* Strain1State::state_builder(bool skip_non_contagious_period)  
    {   
        return new Strain1State(skip_non_contagious_period ? Configuration::configuration->strain_1_contagiousness_begin : 0u);
    }
    double Strain1State::get_susceptibility(_state_builder spreader_state_builder)
    {
        if (
             (age() > Configuration::configuration->immunity_reduction_time_of_strain1_for_strain_2_exposition)
           &&(spreader_state_builder == Strain2State::get_state_builder())
           )
        {
            return  ((double)(Configuration::configuration->immunity_reduction_weight_of_strain1_for_strain_2_exposition)) / 100.9;
        }
        else
        {
            return 0.0;
        }
    }
    bool Strain1State::is_new_active() const { return age()==0; }
    bool Strain1State::is_active_strain1() const { return !(age() > Configuration::configuration->strain_1_contagiousness_end); }
    bool Strain1State::is_active_strain2() const { return false; }
    bool Strain1State::is_in_initial_state() const { return false; }
    bool Strain1State::is_post_strain_1_activation() const { return !is_active_strain1(); }
    bool Strain1State::is_post_strain_2_activation() const { return false; }

} // namespace model
