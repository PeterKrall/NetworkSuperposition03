#include "individual.h"
#include "initialstate.h"
#include "strain1state.h"
#include "strain2state.h"
#include "net.h"
#include <algorithm>
#include <stdlib.h>
#include <iostream>
namespace model
{
    Individual::Individual(unsigned int index) : index(index)
    {
        state = new InitialState();
    }
    void Individual::register_net(Net* net)
    {
        if (is_included(net))
        {
            throw "duplicate membership!";
        }
        else
        {
            including_nets->push_back(net);
        }
    }
    void Individual::deregister_net(Net* net)
    {
        if (!is_included(net))
        {
            throw "not a member!";
        }
        else
        {
            including_nets->erase(std::find(including_nets->begin(), including_nets->end(), net));
        }
    }
    bool Individual::is_included(class Net* net) const
    {
        return ( std::find(including_nets->begin(), including_nets->end(), net) != including_nets->end() );
    }
    bool Individual::interact_with_environment()
    {
        if (
                (state->get_susceptibility(Strain1State::get_state_builder()) > 0.0)
            ||  (state->get_susceptibility(Strain2State::get_state_builder()) > 0.0)
           )
        {
            double raw_strain1transmission_probability_complement = 1.0;
            double raw_strain2transmission_probability_complement = 1.0;
            double strain1_exposition = 0.0;
            double strain2_exposition = 0.0;

            for(std::vector<Net*>::iterator it = std::begin(*including_nets); it != std::end(*including_nets); ++it)
            {
                raw_strain1transmission_probability_complement = raw_strain1transmission_probability_complement * (*it)->get_strain1_transmission_probability_complement();
                raw_strain2transmission_probability_complement = raw_strain2transmission_probability_complement * (*it)->get_strain2_transmission_probability_complement();
                strain1_exposition += (*it)->get_strain1_exposition4initial_state();
                strain2_exposition += (*it)->get_strain2_exposition4initial_state();
            }
            double raw_transmission_probability_complement = raw_strain1transmission_probability_complement * raw_strain2transmission_probability_complement;
            if ( raw_transmission_probability_complement < 1.0)
            {
                double corrected_strain1transmission_probability = (1.0-raw_strain1transmission_probability_complement) * state->get_susceptibility(Strain1State::get_state_builder());
                double corrected_strain2transmission_probability = (1.0-raw_strain2transmission_probability_complement) * state->get_susceptibility(Strain2State::get_state_builder());
                double corrected_transmission_probability_complement = (1.0-corrected_strain1transmission_probability) * (1.0-corrected_strain2transmission_probability);
                if (corrected_strain1transmission_probability == 0.0 && corrected_strain2transmission_probability == 0.0)
                {
                    return false;
                }

                unsigned int r = rand();
                unsigned int t = (corrected_transmission_probability_complement * RAND_MAX);
                if (r > t)
                {
                    // this is a bit tinkering ... but needed to avoid effects of rounding problems with very small numbers
                    if (corrected_strain2transmission_probability != 0.0 && corrected_strain1transmission_probability == 0)
                    {
                        activate(Strain2State::get_state_builder(), false);
                        return true;
                    }
                    if (corrected_strain2transmission_probability == 0.0 && corrected_strain1transmission_probability != 0)
                    {
                        activate(Strain1State::get_state_builder(), false);
                        return true;
                    }
                    double conditional_strain1_transmission_probability_rule1
                            = (strain1_exposition)/(strain1_exposition + strain2_exposition);
                    double conditional_strain1_transmission_probability_rule2
                        = corrected_strain1transmission_probability / (corrected_strain1transmission_probability + corrected_strain2transmission_probability);
                    r = rand();
                    t = (Configuration::configuration->use_rule2_for_conditional_strain_transmission_probabilities)
                        ? conditional_strain1_transmission_probability_rule2 * RAND_MAX
                        : conditional_strain1_transmission_probability_rule1 * RAND_MAX
                        ;
                    if (r < t)
                    {
                        if (Configuration::configuration->generation > 160 && including_nets->size() > 2)
                        {
#ifdef FOLLOW_ON_CONSOLE
                            std::cout << "new strain 1 case in net with fluctuation - generation: " 
                                << Configuration::configuration->generation 
                                << " rule1/rule2 probablity " << conditional_strain1_transmission_probability_rule1 
                                << " / " << conditional_strain1_transmission_probability_rule2 << "\n";
#endif
                        }
                        activate(Strain1State::get_state_builder(), false);
                    }
                    else
                    {
                        activate(Strain2State::get_state_builder(), false);
                    }
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    _state_builder Individual::get_spreader_state_builder() const
    {
        return state->get_active_state_builder();
    }
    void Individual::activate(_state_builder state_builder, bool skip_non_contagious_period)
    {
        state = state_builder(skip_non_contagious_period);
    }
    bool Individual::is_new_active() const { return state->is_new_active(); }
    bool Individual::is_active_strain1() const { return state->is_active_strain1(); }
    bool Individual::is_active_strain2() const { return state->is_active_strain2(); }
    bool Individual::is_in_initial_state() const { return state->is_in_initial_state(); }
    bool Individual::is_post_strain_1_activation() const { return state->is_post_strain_1_activation(); }
    bool Individual::is_post_strain_2_activation() const { return state->is_post_strain_2_activation(); }
    bool Individual::spread() const
    {

        bool activated_at_least_one_target = false;
        if ((is_active_strain1() || is_active_strain2()) && state->age())
        {
            unsigned int last_active_generation = is_active_strain1()
                ? Configuration::configuration->strain_1_contagiousness_end
                : Configuration::configuration->strain_2_contagiousness_end
                ;
            if (state->age() == last_active_generation)
            {
                double
                    t = is_active_strain1()
                    ? (double)(Configuration::configuration->strain1_random_transmission_probability)
                    : (double)(Configuration::configuration->strain2_random_transmission_probability)
                    ;
                double f = 1.0;
                
                while (pow((t / 10000.0), f) > 0.001)
                {
                    Individual* target = Population::instance->get_random_member();
                    double q = pow((t / 10000.0),f) * RAND_MAX * target->state->get_susceptibility(this->get_spreader_state_builder());
                    if (q > rand())
                    {
                        target->activate(this->get_spreader_state_builder(),false);
                        activated_at_least_one_target = true;
                    }
                    f += 1.0;
                }
            }
        }
        return activated_at_least_one_target;

    }
} // namespace model
