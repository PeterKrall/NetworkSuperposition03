#include "model.h"
#include <cstdio>
#include <malloc.h>
#include <cassert>
#include <ctime>

namespace model
{
    
    unsigned int Model::run()
    {
        unsigned int length_of_activity = 0;
        unsigned int new_activity = 0;
        unsigned int initial_state = 0;
        unsigned int strain1_activity = 0;
        unsigned int strain2_activity = 0;
        unsigned int post_strain1_activity = 0;
        unsigned int post_strain2_activity = 0;
        unsigned int new_strain1_activity = 0;
        unsigned int new_strain2_activity = 0;

        
        while (
                 Population::instance->count_activity (
                                                       &new_activity
                                                      ,&new_strain1_activity
                                                      ,&new_strain2_activity
                                                      ,&strain1_activity
                                                      ,&strain2_activity
                                                      ,&initial_state
                                                      ,&post_strain1_activity
                                                      ,&post_strain2_activity
                                                      )
               ||Configuration::configuration->generation<11
               )
        {
            unsigned int nets_with_fluctuation_and_strain1_activity = 0;
            unsigned int nets_with_fluctuation_and_strain2_activity = 0;
            {
                unsigned int number_of_nets_with_fluctuation = Configuration::configuration->basic_net_with_fluctuation_number;
                for (unsigned int i = 0; i < number_of_nets_with_fluctuation; ++i)
                {
                    BasicNetWithFluctuation* net = *(basic_nets_with_fluctuation+i);
                    if (net->has_strain1_actvity()) { nets_with_fluctuation_and_strain1_activity++; }
                    if (net->has_strain2_actvity()) { nets_with_fluctuation_and_strain2_activity++; }
                }
            }
            PopulationState population_state(
                                              length_of_activity
                                            , new_activity
                                            , new_strain1_activity
                                            , new_strain2_activity
                                            , initial_state
                                            , strain1_activity
                                            , strain2_activity
                                            , post_strain1_activity
                                            , post_strain2_activity
                                            , nets_with_fluctuation_and_strain1_activity
                                            , nets_with_fluctuation_and_strain2_activity
                                            );
            writer->persist_population_state(&population_state);
            
            length_of_activity++;
            {
                unsigned int number_of_stable_nets = Configuration::configuration->population_size / Configuration::configuration->basic_stable_net_size;
                for (unsigned int i = 0; i < number_of_stable_nets; ++i)
                {
                    BasicStableNet* net = *(basic_stable_nets+i);
                    net->update_transmission_probabilities();
                }
            }
            {
                unsigned int number_of_stable_nets = Configuration::configuration->population_size / Configuration::configuration->aggregated_stable_net_size;
                for (unsigned int i = 0; i < number_of_stable_nets; ++i)
                {
                    AggregatedStableNet* net = *(aggregated_stable_nets+i);
                    net->update_transmission_probabilities();
                }
            }
            {
                unsigned int number_of_nets_with_fluctuation = Configuration::configuration->basic_net_with_fluctuation_number;
                for (unsigned int i = 0; i < number_of_nets_with_fluctuation; ++i)
                {
                    BasicNetWithFluctuation* net = *(basic_nets_with_fluctuation+i);
                    net->update_transmission_probabilities();
                }
            }
            {
                unsigned int number_of_nets_with_fluctuation = Configuration::configuration->aggregated_net_with_fluctuation_number;
                for (unsigned int i = 0; i < number_of_nets_with_fluctuation; ++i)
                {
                    AggregatedNetWithFluctuation* net = *(aggregated_nets_with_fluctuation+i);
                    net->update_transmission_probabilities();
                }
            }
            Configuration::configuration->generation++;
            Population::instance->propagate_activity();
        }
        return length_of_activity;
    }
    unsigned int model_run()
    {
        srand(time(NULL));
        Model* model= new Model();
        unsigned int length_of_activity = model->run();
        delete(model);
        return length_of_activity;
    }

    Model::Model()
    {
        char model_run_key[1024];
        std::time_t t = std::time(0);
        std::tm now_; std::tm* now = &now_;
        localtime_s(&now_, &t);
        sprintf_s(
            model_run_key
            , "model_run_%d_%d_%d_%d_%d_%d__%d"
            , now->tm_year + 1900, now->tm_mon + 1, now->tm_mday, now->tm_hour, now->tm_min, now->tm_sec, rand()%10000
        );

        Configuration::configuration->generation = 0;
        writer = (Writer::get_open_writer())(model_run_key);
        new Population();
        {
            unsigned int number_of_stable_nets = Configuration::configuration->population_size / Configuration::configuration->basic_stable_net_size;
            basic_stable_nets = (BasicStableNet**)(malloc(sizeof(BasicStableNet*)*number_of_stable_nets));
            BasicStableNet* p = nullptr;
            for (unsigned int i = 0; i < number_of_stable_nets; ++i)
            {
                p = new BasicStableNet(i*Configuration::configuration->basic_stable_net_size);             
                *(basic_stable_nets + i) = p;
            }            
        }
        {
            unsigned int number_of_stable_nets = Configuration::configuration->population_size / Configuration::configuration->aggregated_stable_net_size;
            aggregated_stable_nets = (AggregatedStableNet**)(malloc(sizeof(AggregatedStableNet*)*number_of_stable_nets));
            AggregatedStableNet* p;
            for (unsigned int i = 0; i < number_of_stable_nets; ++i)
            {
                p = new AggregatedStableNet(i*Configuration::configuration->aggregated_stable_net_size);                
                *(aggregated_stable_nets + i) = p;
            }
        }
        {
            unsigned int number_of_nets_with_fluctuation = Configuration::configuration->basic_net_with_fluctuation_number;
            basic_nets_with_fluctuation = (BasicNetWithFluctuation**)(malloc(sizeof(BasicNetWithFluctuation*)*number_of_nets_with_fluctuation));
            BasicNetWithFluctuation* p;
            for (unsigned int i = 0; i < number_of_nets_with_fluctuation; ++i)
            {
                p = new BasicNetWithFluctuation(aggregated_stable_nets);
                *(basic_nets_with_fluctuation + i) = p;
            }
            
        }
        {
            unsigned int number_of_nets_with_fluctuation = Configuration::configuration->aggregated_net_with_fluctuation_number;
            aggregated_nets_with_fluctuation = (AggregatedNetWithFluctuation**)(malloc(sizeof(AggregatedNetWithFluctuation*)*number_of_nets_with_fluctuation));
            AggregatedNetWithFluctuation* p = nullptr;
            for (unsigned int i = 0; i < number_of_nets_with_fluctuation; ++i)
            {
                p = new AggregatedNetWithFluctuation(basic_nets_with_fluctuation);
                *(aggregated_nets_with_fluctuation + i) = p;
            }
        }
    }
    Model::~Model()
    {        
        {
            unsigned int number_of_stable_nets = Configuration::configuration->population_size / Configuration::configuration->basic_stable_net_size;
            for (unsigned int i = 0; i < number_of_stable_nets; ++i)
            {
                BasicStableNet* net = *(basic_stable_nets+i);
                delete(net);
            }
            free(basic_stable_nets);
        }
        {
            unsigned int number_of_stable_nets = Configuration::configuration->population_size / Configuration::configuration->aggregated_stable_net_size;
            for (unsigned int i = 0; i < number_of_stable_nets; ++i)
            {
                AggregatedStableNet* net = *(aggregated_stable_nets+i);
                delete(net);
            }
            free(aggregated_stable_nets);
        }
        {
            unsigned int number_of_nets_with_fluctuation = Configuration::configuration->basic_net_with_fluctuation_number;
            for (unsigned int i = 0; i < number_of_nets_with_fluctuation; ++i)
            {
                BasicNetWithFluctuation* net = *(basic_nets_with_fluctuation+i);
                delete(net);
            }
            free(basic_nets_with_fluctuation);
        }
        {
            unsigned int number_of_nets_with_fluctuation = Configuration::configuration->aggregated_net_with_fluctuation_number;
            for (unsigned int i = 0; i < number_of_nets_with_fluctuation; ++i)
            {
                AggregatedNetWithFluctuation* net = *(aggregated_nets_with_fluctuation+i);
                delete(net);
            }
            free(aggregated_nets_with_fluctuation);
        }
        //
        delete Population::instance;
        Writer::get_close_writer()(writer);
    }
    model_execution Model::run_model = &model_run;
} // namespace model
