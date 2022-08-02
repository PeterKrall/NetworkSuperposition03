#include "aggregatednetwithfluctuation.h"
#include <stdlib.h>
#include "strain1state.h"
#include "strain2state.h"
namespace model
{

    AggregatedNetWithFluctuation::AggregatedNetWithFluctuation(BasicNetWithFluctuation** basic_nets)
        : Net()
    {
        this->basic_nets = basic_nets;
        members = (Individual**)(malloc(sizeof(Individual*)*(Configuration::configuration->aggregated_net_with_fluctuation_size)));
    }
    void* AggregatedNetWithFluctuation::get_class_id() { return &class_id; }
    void* AggregatedNetWithFluctuation::class_identifier = &class_id;
    unsigned int AggregatedNetWithFluctuation::class_id;
    double AggregatedNetWithFluctuation::get_strain1_transmission_probability()
    {
        return ((double)(Configuration::configuration->strain_1_transmission_probability_in_aggregated_net_with_fluctuation))/10000.0;
    }
    double AggregatedNetWithFluctuation::get_strain2_transmission_probability()
    {
        return ((double)(Configuration::configuration->strain_2_transmission_probability_in_aggregated_net_with_fluctuation))/10000.0;
    }
    void AggregatedNetWithFluctuation::update_transmission_probabilities()
    {
        update_content();
        Net::update_transmission_probabilities();
    }
    void AggregatedNetWithFluctuation::update_content()
    {
        while (actual_size != 0)
        {
            actual_size--;
            Individual* individual = *(members+actual_size);
            individual->deregister_net(this);
            *(members+actual_size) = nullptr;
        }
        while (actual_size != (size = Configuration::configuration->aggregated_net_with_fluctuation_size))
        {
            int r = rand()%(Configuration::configuration->basic_net_with_fluctuation_number);
            BasicNetWithFluctuation* basic_net = *(basic_nets+r);
            r = rand()%(basic_net->get_size());
            Individual* individual = *(basic_net->get_members()+r);
            if (!individual->is_included(this))
            {
                *(members+actual_size) = individual;
                individual->register_net(this);
                actual_size++;
            }
        }
        if (Configuration::configuration->generation==10)
        {
            std::vector<std::string> initial_cases;
            std::string initial_cases_string(Configuration::configuration->initial_strain1cases);
            size_t pos;
            while ((pos = initial_cases_string.find(",")) != std::string::npos)
            {
                initial_cases.push_back(initial_cases_string.substr(0, pos));
                initial_cases_string.erase(0, pos + 1);
            }
            initial_cases.push_back(initial_cases_string);
            for (std::vector<std::string>::iterator it = initial_cases.begin(); it != initial_cases.end(); ++it)
            {                
                (*(members+atoi((*it).c_str())))->activate(Strain1State::get_state_builder(),true);
            }
        }
        if (Configuration::configuration->generation == Configuration::configuration->first_strain2_appearance)
        {
            std::vector<std::string> initial_cases;
            std::string initial_cases_string(Configuration::configuration->initial_strain2cases);
            size_t pos;
            while ((pos = initial_cases_string.find(",")) != std::string::npos)
            {
                initial_cases.push_back(initial_cases_string.substr(0, pos));
                initial_cases_string.erase(0, pos + 1);
            }
            initial_cases.push_back(initial_cases_string);
            for (std::vector<std::string>::iterator it = initial_cases.begin(); it != initial_cases.end(); ++it)
            {
                (*(members+atoi((*it).c_str())))->activate(Strain2State::get_state_builder(),true);
            }
        }
    }
} // namespace model
