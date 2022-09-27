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
        strain1_spreader = 0.0;
        strain2_spreader = 0.0;
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
            strain1_transmission_probability_complement = pow((1.0 - get_strain1_exposure()),strain1_spreader);
        }
        if (strain2_spreader == 0.0)
        {
            strain2_transmission_probability_complement = 1.0;
        }
        else
        {
            strain2_transmission_probability_complement = pow((1.0 - get_strain2_exposure()),strain2_spreader);
        }
    }
    double Net::get_strain1_exposure() 
    {
        double f = (Configuration::configuration->environmental_constraints_change_time < Configuration::configuration->generation) && (Configuration::configuration->environmental_constraints_change_time != 0)
                ? (double)(Configuration::configuration->environmental_constraints_change_weight) / 100.0
                : 1.0
                ;
        return get_strain1_transmission_probability()*f;
    }
    double Net::get_strain2_exposure() 
    {
        double f = (Configuration::configuration->environmental_constraints_change_time < Configuration::configuration->generation) && (Configuration::configuration->environmental_constraints_change_time != 0)
                ? (double)(Configuration::configuration->environmental_constraints_change_weight) / 100.0
                : 1.0
                ;
        return get_strain2_transmission_probability() * f;
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
    unsigned int Net::initialize_activity(std::string& initial_cases_string, _state_builder state_builder)
    {
        unsigned int cnt = 0;
        std::vector<std::string> initial_cases;
        (Configuration::configuration->initial_strain2cases);
        size_t pos;
        while ((pos = initial_cases_string.find(",")) != std::string::npos)
        {
            initial_cases.push_back(initial_cases_string.substr(0, pos));
            initial_cases_string.erase(0, pos + 1);
        }
        initial_cases.push_back(initial_cases_string);
        for (std::vector<std::string>::iterator it = initial_cases.begin(); it != initial_cases.end(); ++it)
        {
            try
            {
                unsigned int idx = std::stol((*it));
                Individual* member = *(members + atoi((*it).c_str()));
                member->activate(state_builder, true);
                cnt++;
            }
            catch (...)
            {
                // do nothing - the particle does not define a valid element
            }
        }
        return cnt;
    }
    double Net::get_strain1_exposition4initial_state() { return strain1_spreader * get_strain1_exposure(); }
    double Net::get_strain2_exposition4initial_state() { return strain2_spreader * get_strain2_exposure(); }

} // namespace model
