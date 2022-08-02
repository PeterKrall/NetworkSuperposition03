#include "population_state.h"
namespace model
{
    PopulationState::PopulationState(
                                      const unsigned int length_of_activity
                                    , const unsigned int new_activity
                                    , const unsigned int new_strain1_activity
                                    , const unsigned int new_strain2_activity
                                    , const unsigned int initial_state
                                    , const unsigned int strain1_activity
                                    , const unsigned int strain2_activity
                                    , const unsigned int post_strain1_activity
                                    , const unsigned int post_strain2_activity
                                    , const unsigned int nets_with_fluctuation_and_strain1_activity
                                    , const unsigned int nets_with_fluctuation_and_strain2_activity
    ) : length_of_activity(length_of_activity)
      , new_activity(new_activity)
      , new_strain1_activity(new_strain1_activity)
      , new_strain2_activity(new_strain2_activity)
      , initial_state(initial_state)
      , strain1_activity(strain1_activity)
      , strain2_activity(strain2_activity)
      , post_strain1_activity(post_strain1_activity)
      , post_strain2_activity(post_strain2_activity)
      , nets_with_fluctuation_and_strain1_activity(nets_with_fluctuation_and_strain1_activity)
      , nets_with_fluctuation_and_strain2_activity(nets_with_fluctuation_and_strain2_activity)
    {}
}