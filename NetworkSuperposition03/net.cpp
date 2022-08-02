#include "net.h"
#include "strain1state.h"
#include "strain2state.h"
#include <math.h>
namespace model
{
    Net::Net()
    {        
        members = nullptr; // initially, will be set by derived classes        
    }
    void Net::update_transmission_probabilities()
    {
        double strain1_spreader = 0.0;
        double strain2_spreader = 0.0;
        for (unsigned int i = 0; i < size; i++)
        {
            Individual* member = *(members+i);
            if (member->get_spreader_state_builder() == Strain1State::get_state_builder()) { strain1_spreader += 1.0; }
            if (member->get_spreader_state_builder() == Strain2State::get_state_builder()) { strain2_spreader += 1.0; }
        }
        if (strain1_spreader == 0.0)
        {
            strain1_transmission_probability_complement = 1.0;
        }
        else
        {
            strain1_transmission_probability_complement = pow((1.0-get_strain1_transmission_probability()),strain1_spreader);
        }
        if (strain2_spreader == 0.0)
        {
            strain2_transmission_probability_complement = 1.0;
        }
        else
        {
            strain2_transmission_probability_complement = pow((1.0-get_strain2_transmission_probability()),strain2_spreader);
        }
    }
    double Net::get_strain1_transmission_probability_complement() const
    {
        return strain1_transmission_probability_complement;
    }
    double Net::get_strain2_transmission_probability_complement() const
    {
        return strain2_transmission_probability_complement;
    }
    Individual** Net::get_members() const
    {
        return members;
    }
    unsigned int Net::get_size() const
    {
        return size;
    }
    bool Net::count_activity(unsigned int* new_activity,unsigned int* strain1_activity,unsigned int* strain2_activity, unsigned int* individuals_in_initial_state) const
    {
        bool found_activity = false;
        for (unsigned int i = 0; i < size; ++i)
        {
            Individual* member = *(members+i);
            if (member->is_active_strain1()) { (*strain1_activity)++; found_activity = true; }
            if (member->is_active_strain2()) { (*strain2_activity)++; found_activity = true; }
            if (member->is_new_active()) { (*new_activity)++; }
            if (member->is_in_initial_state()) { (*individuals_in_initial_state)++; }
        }
        return found_activity;
    }

} // namespace model
