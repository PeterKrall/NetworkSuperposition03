#ifndef MODEL_POPULATION_H
#define MODEL_POPULATION_H
#include "individual.h"
#include "configuration.h"

namespace model
{
    class Population
    {
    public:
        Population();
        ~Population();
        Individual** get_members() const;
        Individual** get_shuffled_members() const;
        virtual bool count_activity (
                                     unsigned int* new_activity
                                    ,unsigned int* new_strain1_activity
                                    ,unsigned int* new_strain2_activity
                                    ,unsigned int* strain1_activity
                                    ,unsigned int* strain2_activity
                                    ,unsigned int* initial_state
                                    ,unsigned int* post_strain1_activity
                                    ,unsigned int* post_strain2_activity
                                    ) const final;
        virtual void propagate_activity() const final;
        virtual Individual* get_random_member() const final;
        static Population* instance;
    private:
        Individual** members;
        Individual** shuffled_members;
    };
} // namespace model

#endif // MODEL_POPULATION_H
