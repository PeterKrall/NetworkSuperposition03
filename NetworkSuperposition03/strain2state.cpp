#include "strain2state.h"
#include "configuration.h"
namespace model
{

    Strain2State::Strain2State(unsigned int time_to_date_back_activation) : State(time_to_date_back_activation) {}
    _state_builder Strain2State::get_active_state_builder()
    {
        if (age() < Configuration::configuration->strain_2_contagiousness_begin || age() > Configuration::configuration->strain_2_contagiousness_end)
        {
            return nullptr;
        }
        else
        {
            return get_state_builder();
        }
    }
    _state_builder Strain2State::get_state_builder() { return class_specific_state_builder; }
    _state_builder Strain2State::class_specific_state_builder = &Strain2State::state_builder;
    State* Strain2State::state_builder(bool skip_non_contagious_period)
    {
        return new Strain2State(skip_non_contagious_period ? Configuration::configuration->strain_2_contagiousness_begin : 0u);
    }
    double Strain2State::get_susceptibility(_state_builder spreader_state_builder) { return 0.0; }
    bool Strain2State::is_new_active() const { return age()==0; }
    bool Strain2State::is_active_strain1() const { return false; }
    bool Strain2State::is_active_strain2() const { return !(age() > Configuration::configuration->strain_2_contagiousness_end); }
    bool Strain2State::is_in_initial_state() const { return false; }
    bool Strain2State::is_post_strain_1_activation() const { return false; }
    bool Strain2State::is_post_strain_2_activation() const { return !is_active_strain2(); }
} // namespace model
