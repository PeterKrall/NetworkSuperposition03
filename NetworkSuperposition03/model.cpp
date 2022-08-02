#include "model.h"
#include "plotter.h"
#include <cstdio>
#include <malloc.h>
#include <cassert>
#include <ctime>

namespace model
{
    using namespace matlab::engine;

    static bool matlab_initialized = false;
    std::unique_ptr<MATLABEngine> matlab_engine = nullptr;
    matlab::data::ArrayFactory* matlab_data_factory = nullptr;

    bool initialize_matlab_access()
    {
        if (matlab_initialized) { return true;  }
        // Start MATLAB engine synchronously
        matlab_engine = startMATLAB();
        matlab_data_factory = new matlab::data::ArrayFactory();
        
        // test: pass vector containing 2 scalar args in vector    
        std::vector<matlab::data::Array> args({ matlab_data_factory->createScalar<int16_t>(30), matlab_data_factory->createScalar<int16_t>(56) });

        // Call MATLAB function and check result
        matlab::data::TypedArray<int16_t> result = matlab_engine->feval(u"gcd", args);
        int16_t v = result[0];        
        return (matlab_initialized = (v == 2));
    }
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
        if (!initialize_matlab_access())
        {
            throw "matlab not accessible!";
        }
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
        plotter = new Plotter(); 
        //plotter->test();
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
        delete plotter;
        Writer::get_close_writer()(writer);
    }
    model_execution Model::run_model = &model_run;
    matlab::data::ArrayFactory* Model::get_matlab_data_factory() { return matlab_data_factory;  };
    std::unique_ptr<MATLABEngine>* Model::get_matlab_engine() { return &matlab_engine; }
} // namespace model
