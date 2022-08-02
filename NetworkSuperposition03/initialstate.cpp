#include "initialstate.h"
#include "strain1state.h"
#include "strain2state.h"

namespace model
{

    InitialState::InitialState() : State(0u)  { }
    _state_builder InitialState::get_active_state_builder() { return nullptr; }
    _state_builder InitialState::get_state_builder() { return class_specific_state_builder; }
    _state_builder InitialState::class_specific_state_builder = &InitialState::state_builder;
    State* InitialState::state_builder(bool skip_non_contagious_period)  {   return new InitialState();  }
    double InitialState::get_susceptibility(_state_builder spreader_state_builder)
    {
        if ((spreader_state_builder==Strain1State::get_state_builder())||(spreader_state_builder==Strain2State::get_state_builder()))
        {
            return 1.0;
        }
        else
        {
            return 0.0;
        }
    }
    bool InitialState::is_new_active() const { return false; }
    bool InitialState::is_active_strain1() const { return false; }
    bool InitialState::is_active_strain2() const { return false; }
    bool InitialState::is_in_initial_state() const { return true; }
    bool InitialState::is_post_strain_1_activation() const { return false; }
    bool InitialState::is_post_strain_2_activation() const { return false; }
} // namespace model
