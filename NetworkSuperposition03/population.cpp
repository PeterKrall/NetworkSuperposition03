#include "population.h"
#include <malloc.h>
#include "strain1state.h"
#include "strain2state.h"
#include <iostream>

namespace model
{
    Population* Population::instance = nullptr;

    Population::Population()
    {
        unsigned int shuffled_population_size = Configuration::configuration->aggregated_stable_net_number * Configuration::configuration->aggregated_stable_net_size;
        
        members = (Individual**)(malloc(sizeof(Individual*) * Configuration::configuration->population_size));
        shuffled_members = (Individual**)(malloc(sizeof(Individual*) * Configuration::configuration->population_size));
        for (unsigned int i = 0; i < Configuration::configuration->population_size; ++i)
        {
            Individual* member = new Individual(i);
            *(members + i) = member;
            *(shuffled_members + i) = nullptr; 
        }
        // build a shuffled copy of the population
#define POPULATION_SEGMENT_SIZE 20000
        if (Configuration::configuration->aggregated_stable_net_shuffle == 100)
        {
            std::cout << "suffled population size = " << shuffled_population_size << "\n";
            std::vector<Individual*> v;
            for (unsigned int i = 0; i < shuffled_population_size; ++i)
            {
                v.push_back(*(members + i));
            }
            unsigned int i = 0;
            while ( i < shuffled_population_size )
            {
                unsigned int segment_count = v.size() / POPULATION_SEGMENT_SIZE + 1;
                unsigned int idx = ((rand() % segment_count) * POPULATION_SEGMENT_SIZE) + rand() % POPULATION_SEGMENT_SIZE;
                if (idx < v.size())
                {
                    if (i % 10000 == 0) { std::cout << "i= " << i << "\n"; }
                    *(shuffled_members + i) = v.at(idx);
                    v.erase(v.begin() + idx);
                    i++;
                }
            }
            // just to make sure that I made no program error 
            if (v.size())
            {
                throw "this never happened";
            }
            for (unsigned int i = 0; i < shuffled_population_size; ++i)
            {
                if (*(shuffled_members + i) == nullptr)
                {
                    throw "this never happened";
                }
                for (unsigned int ii = i+1; ii < shuffled_population_size; ++ii)
                {
                    if (*(shuffled_members + i) == *(shuffled_members + ii))
                    {
                        throw "this never happened";
                    }
                }
            }
        }
        else
        {
            for (unsigned int i = 0; i < Configuration::configuration->population_size; ++i)
            {
                *(shuffled_members + i) = *(members + i);
            }
#define NUMBER_OF_SWAPS (Configuration::configuration->population_size / 100) * Configuration::configuration->aggregated_stable_net_shuffle
            unsigned int segment_count = Configuration::configuration->population_size / POPULATION_SEGMENT_SIZE + 1;
            for (unsigned int i = 0; i < NUMBER_OF_SWAPS; )
            {
                unsigned int idx0 = ((rand() % segment_count) * POPULATION_SEGMENT_SIZE) + rand() % POPULATION_SEGMENT_SIZE;
                unsigned int idx1 = ((rand() % segment_count) * POPULATION_SEGMENT_SIZE) + rand() % POPULATION_SEGMENT_SIZE;
                if (idx0 < Configuration::configuration->population_size && idx1 < Configuration::configuration->population_size)
                {
                    Individual* someone = *(shuffled_members + idx0);
                    *(shuffled_members + idx0) = *(shuffled_members + idx1);
                    *(shuffled_members + idx1) = someone; 
                    i++;
                }
            } 
#undef NUMBER_OF_SWAPS
        }
#undef POPULATION_SEGMENT_SIZE
        instance = this;
    }
    Population::~Population()
    {
        for (unsigned int i = 0; i < Configuration::configuration->population_size; ++i)
        {
            Individual* member = *(members + i);
            delete member;
        }
        delete members;
        delete shuffled_members;
    }
    Individual* Population::get_random_member() const
    {
        // select an random individual in a population possibly bigger than RAND_MAX 
        // but at most POPULATION_SEGMENT_SIZE * RAND_MAX =>
        // (if population size is not a multiple of POPULATION_SEGMENT_SIZE, there will be a bias - but this does not matter)
#define POPULATION_SEGMENT_SIZE 20009
        unsigned int segment_count = Configuration::configuration->population_size / POPULATION_SEGMENT_SIZE + 1;
        unsigned int segment_offset = (rand() % segment_count) * POPULATION_SEGMENT_SIZE;
        unsigned int idx = segment_offset + rand() % POPULATION_SEGMENT_SIZE;
        if (idx < Configuration::configuration->population_size)
        {
            return  *(get_members() + idx);
        }
        else
        {
            return get_random_member();
        }
#undef POPULATION_SEGMENT_SIZE
    }
    Individual ** Population::get_members() const
    {
        return members;
    }
    Individual** Population::get_shuffled_members() const
    {
        return shuffled_members;
    }

    bool Population::count_activity (
                                     unsigned int* new_activity
                                    ,unsigned int* new_strain1_activity
                                    ,unsigned int* new_strain2_activity
                                    ,unsigned int* strain1_activity
                                    ,unsigned int* strain2_activity
                                    ,unsigned int* initial_state
                                    ,unsigned int* post_strain1_activity
                                    ,unsigned int* post_strain2_activity
                                    ) const

    {
        bool found_activity = false;
        *new_activity = 0;
        *new_strain1_activity = 0;
        *new_strain2_activity = 0;
        *initial_state = 0;
        *strain1_activity = 0;
        *strain2_activity = 0;
        *post_strain1_activity = 0;
        *post_strain2_activity = 0;
        for (unsigned int i = 0; i < Configuration::configuration->population_size; ++i)
        {
            Individual* member = *(members+i);
            if (member->is_new_active()) { (*new_activity)++; }
            if (member->is_active_strain1()) { (*strain1_activity)++; found_activity = true; if (member->is_new_active()) { (*new_strain1_activity)++; }}
            if (member->is_active_strain2()) { (*strain2_activity)++; found_activity = true; if (member->is_new_active()) { (*new_strain2_activity)++; }}
            if (member->is_in_initial_state()) { (*initial_state)++; }
            if (member->is_post_strain_1_activation()) { (*post_strain1_activity)++;  }
            if (member->is_post_strain_2_activation()) { (*post_strain2_activity)++;  }
        }
        return found_activity;
    }
    void Population::propagate_activity() const
    {
        for (unsigned int i = 0; i < Configuration::configuration->population_size; ++i)
        {
            Individual* member = *(members+i);
            member->interact_with_environment();
        }
        for (unsigned int i = 0; i < Configuration::configuration->population_size; ++i)
        {
            Individual* member = *(members + i);
            member->spread();
        }
    }
} // namespace model
