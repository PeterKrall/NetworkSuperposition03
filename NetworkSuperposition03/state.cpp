#include "state.h"
#include "configuration.h"

namespace model
{
    State::State(unsigned int time_to_date_back_activation) 
        : time_of_activation(Configuration::configuration->generation - (Configuration::configuration->generation>time_to_date_back_activation?time_to_date_back_activation:0)){}
    unsigned int State::age() const { return Configuration::configuration->generation - time_of_activation; }
} // namespace model
