#ifndef POPULATION_STATE_H
#define POPULATION_STATE_H
// a state of the population
namespace model
{
	class PopulationState
	{
	public:
        PopulationState (
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
                        );
        const unsigned int length_of_activity;
        const unsigned int new_activity;
        const unsigned int new_strain1_activity;
        const unsigned int new_strain2_activity;
        const unsigned int initial_state;
        const unsigned int strain1_activity;
        const unsigned int strain2_activity;
        const unsigned int post_strain1_activity;
        const unsigned int post_strain2_activity;
        const unsigned int nets_with_fluctuation_and_strain1_activity;
        const unsigned int nets_with_fluctuation_and_strain2_activity;
	};
}
#endif // !

