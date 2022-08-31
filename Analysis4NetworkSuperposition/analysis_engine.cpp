#include "analysis_engine.h"
#include "persistence.h"
#include "configuration_statistics.h"

namespace analysis
{
    static bool matlab_initialized = false;
    std::unique_ptr<MATLABEngine> matlab_engine = nullptr;
    matlab::data::ArrayFactory* matlab_data_factory = nullptr;

    bool initialize_matlab_access()
    {
        if (matlab_initialized) { return true; }
        // Start MATLAB engine synchronously
        matlab_engine = startMATLAB();
        matlab_data_factory = new matlab::data::ArrayFactory();

        // test: pass vector containing 2 scalar args in vector    
        std::vector<matlab::data::Array> args({ matlab_data_factory->createScalar<int16_t>(30), matlab_data_factory->createScalar<int16_t>(56) });

        // Call MATLAB function and check result
        matlab::data::TypedArray<int16_t> result = matlab_engine->feval(u"gcd", args);
        int16_t v = result[0];
        /*
        f = figure('visible', 'off');
        plot(a)
            % do all other plotting to the figure here before making visible, saving, and closing
            set(f, 'visible', 'on');
        saveas(f, 'newout', 'fig');
        close(f)
        */
        return (matlab_initialized = (v == 2));
    }
    unsigned int analyse(const char* output_directory)
    {
        if (!initialize_matlab_access())
        {
            throw "matlab not accessible!";
        }
        srand(time(NULL));
        AnalysisEngine* analysis_engine = new AnalysisEngine();
        unsigned int result = analysis_engine->run_analysis(output_directory);
        delete(analysis_engine);
        return result;
    }
    AnalysisEngine::AnalysisEngine()
    {
        configurations = nullptr;
    }
    AnalysisEngine::~AnalysisEngine()
    {
        get_matlab_engine()->release();
        (persistence::PersistenceProvider::close_persistence_provider_instance())((persistence::PersistenceProvider::get_persistence_provider_instance())());
    }
    analysis AnalysisEngine::start_analysis = &analyse;
    matlab::data::ArrayFactory* AnalysisEngine::get_matlab_data_factory() { return matlab_data_factory; };
    std::unique_ptr<MATLABEngine>* AnalysisEngine::get_matlab_engine() { return &matlab_engine; }
    unsigned int AnalysisEngine::run_analysis(const char* output_directory)
    {
        plotter = new Plotter(get_matlab_engine(), output_directory);
        configurations = (persistence::PersistenceProvider::get_persistence_provider_instance())()->read_configurations();
        (persistence::PersistenceProvider::get_persistence_provider_instance())()->erase_configuration_statistics();
        for (std::vector<model::Configuration*>::iterator it = configurations->begin(); it != configurations->end(); ++it) 
        {
            analyse_model_runs(*it);
            delete* it;
        }
        delete configurations; configurations = nullptr;
        return 0;
    }
    unsigned int AnalysisEngine::analyse_model_runs(model::Configuration* configuration)
    {        
        std::vector<ModelRunStatistics*>* valid_model_runs = new std::vector <ModelRunStatistics*>();
        std::vector<std::string*>* model_run_keys = (persistence::PersistenceProvider::get_persistence_provider_instance())()->read_model_runs(configuration);
        unsigned int random_losses_of_strain2 = 0;
        for (std::vector<std::string*>::iterator it = model_run_keys->begin(); it != model_run_keys->end(); ++it)
        {
            ModelRunStatistics* model_run_statistics = analyse_model_run(&(configuration->label), *it);
            if (model_run_statistics != nullptr)
            {
                if (model_run_statistics->post_2 > 0 && model_run_statistics->post_1 > model_run_statistics->post_2)
                {
                    random_losses_of_strain2++;
                    // there is no point including these runs into statistics except for mentioning their existence
                }
                else
                {
                    (persistence::PersistenceProvider::get_persistence_provider_instance())()->persist(model_run_statistics, (*it)->c_str());
                    valid_model_runs->push_back(model_run_statistics);
                }
            }
            delete* it;
        }
        delete model_run_keys;
        //
        if (valid_model_runs->size() > 0)
        {
            ConfigurationStatistics configuration_statististic(*configuration);
            configuration_statististic.number_of_runs = valid_model_runs->size();
            std::vector<int> max_new;
            std::vector<int> max1_new;
            std::vector<int> max2_new;
            std::vector<int> max_post1;
            std::vector<int> post1_at_end;
            std::vector<int> post2_at_end;
            std::vector<int> length;
            std::vector<double> immunity_at_peak;
            std::vector<double> immunity_at_end;
            std::vector<int> time_to_dominance;
            std::vector<int> time_to_complete_replacement;
            std::vector<double> immunity_at_last90pcnt_max;
            std::vector<double> immunity_at_last75pcnt_max;
            std::vector<double> immunity_at_complete_replacement;

            for (std::vector<ModelRunStatistics*>::iterator it = valid_model_runs->begin(); it != valid_model_runs->end(); ++it)
            {
                max_new.push_back((*it)->max);
                max1_new.push_back((*it)->max_1);
                max2_new.push_back((*it)->max_2);;
                max_post1.push_back((*it)->max_post_1);
                post1_at_end.push_back((*it)->post_1);
                post2_at_end.push_back((*it)->post_2);
                length.push_back((*it)->length);
                immunity_at_peak.push_back((*it)->immunity_at_peak);
                immunity_at_end.push_back((*it)->immunity_at_end);
                time_to_dominance.push_back((*it)->time_to_dominance);
                time_to_complete_replacement.push_back((*it)->time_to_complete_replacement);compute_statistics_component(immunity_at_end, &(configuration_statististic.max_immunity_at_end), &(configuration_statististic.min_immunity_at_end), &(configuration_statististic.mean_immunity_at_end), &(configuration_statististic.standard_deviation_immunity_at_end));
                immunity_at_last90pcnt_max.push_back((*it)->immunity_at_last_90pcnt_max);
                immunity_at_last75pcnt_max.push_back((*it)->immunity_at_last_75pcnt_max);
                immunity_at_complete_replacement.push_back((*it)->immunity_at_complete_replacement);

                delete (*it);
            }
            compute_statistics_component(max_new, &(configuration_statististic.max_max_new), &(configuration_statististic.min_max_new), &(configuration_statististic.mean_max_new), &(configuration_statististic.standard_deviation_max_new));
            compute_statistics_component(max1_new, &(configuration_statististic.max_max1_new), &(configuration_statististic.min_max1_new), &(configuration_statististic.mean_max1_new), &(configuration_statististic.standard_deviation_max1_new));
            compute_statistics_component(max2_new, &(configuration_statististic.max_max2_new), &(configuration_statististic.min_max2_new), &(configuration_statististic.mean_max2_new), &(configuration_statististic.standard_deviation_max2_new));
            compute_statistics_component(max_post1, &(configuration_statististic.max_max_post1), &(configuration_statististic.min_max_post1), &(configuration_statististic.mean_max_post1), &(configuration_statististic.standard_deviation_max_post1));
            compute_statistics_component(post1_at_end, &(configuration_statististic.max_post1_at_end), &(configuration_statististic.min_post1_at_end), &(configuration_statististic.mean_post1_at_end), &(configuration_statististic.standard_deviation_post1_at_end));
            compute_statistics_component(post2_at_end, &(configuration_statististic.max_post2_at_end), &(configuration_statististic.min_post2_at_end), &(configuration_statististic.mean_post2_at_end), &(configuration_statististic.standard_deviation_post2_at_end));
            compute_statistics_component(length, &(configuration_statististic.max_length), &(configuration_statististic.min_length), &(configuration_statististic.mean_length), &(configuration_statististic.standard_deviation_length));
            compute_statistics_component(time_to_dominance, &(configuration_statististic.max_time_to_dominance), &(configuration_statististic.min_time_to_dominance), &(configuration_statististic.mean_time_to_dominance), &(configuration_statististic.standard_deviation_time_to_dominance));
            compute_statistics_component(time_to_complete_replacement, &(configuration_statististic.max_time_to_complete_replacement), &(configuration_statististic.min_time_to_complete_replacement), &(configuration_statististic.mean_time_to_complete_replacement), &(configuration_statististic.standard_deviation_time_to_complete_replacement));
            compute_statistics_component(immunity_at_peak, &(configuration_statististic.max_immunity_at_peak), &(configuration_statististic.min_immunity_at_peak), &(configuration_statististic.mean_immunity_at_peak), &(configuration_statististic.standard_deviation_immunity_at_peak));
            compute_statistics_component(immunity_at_end, &(configuration_statististic.max_immunity_at_end), &(configuration_statististic.min_immunity_at_end), &(configuration_statististic.mean_immunity_at_end), &(configuration_statististic.standard_deviation_immunity_at_end));
            compute_statistics_component(immunity_at_complete_replacement, &(configuration_statististic.max_immunity_at_complete_replacement), &(configuration_statististic.min_immunity_at_complete_replacement), &(configuration_statististic.mean_immunity_at_complete_replacement), &(configuration_statististic.standard_deviation_immunity_at_complete_replacement));
            compute_statistics_component(immunity_at_last90pcnt_max, &(configuration_statististic.max_immunity_at_last90pcnt_max), &(configuration_statististic.min_immunity_at_last90pcnt_max), &(configuration_statististic.mean_immunity_at_last90pcnt_max), &(configuration_statististic.standard_deviation_immunity_at_last90pcnt_max));
            compute_statistics_component(immunity_at_last75pcnt_max, &(configuration_statististic.max_immunity_at_last75pcnt_max), &(configuration_statististic.min_immunity_at_last75pcnt_max), &(configuration_statististic.mean_immunity_at_last75pcnt_max), &(configuration_statististic.standard_deviation_immunity_at_last75pcnt_max));
            (persistence::PersistenceProvider::get_persistence_provider_instance())()->insert_configuration_statistics(configuration_statististic);
        }
        delete valid_model_runs;

        return random_losses_of_strain2;
    }
    bool AnalysisEngine::compute_statistics_component(std::vector<int>& observations, unsigned int* max, unsigned int* min, double* mean, double* standard_deviation)
    {
        bool worked = false;
        try {
            matlab::data::TypedArray<int> const args = matlab_data_factory->createArray({ 1,observations.size() }, observations.begin(), observations.end());
            
            matlab::data::TypedArray<int> const max_ = matlab_engine->feval(u"max", args); *max = max_[0];
            matlab::data::TypedArray<int> const min_ = matlab_engine->feval(u"min", args); *min = min_[0];
            matlab::data::TypedArray<double> const mean_ = matlab_engine->feval(u"mean", args); *mean = mean_[0];
            if (observations.size() == 1)
            {
                *standard_deviation = 0;
            }
            else
            {
                std::vector<double> observations_d; for (std::vector<int>::iterator it = observations.begin(); it != observations.end(); ++it)
                {
                    observations_d.push_back((double)(*it));
                }
                matlab::data::TypedArray<double> const args_d = matlab_data_factory->createArray({ 1,observations_d.size() }, observations_d.begin(), observations_d.end());
                matlab::data::TypedArray<double> const std_ = matlab_engine->feval(u"std", args_d);
                *standard_deviation = std_[0];                
            }
            worked = true;
        }
        catch (std::exception ex)
        {
            const char* what = ex.what();
        }
        catch (...)
        {
            worked = false;
        }
        return worked;
    }
    bool AnalysisEngine::compute_statistics_component(std::vector<double>& observations, double* max, double* min, double* mean, double* standard_deviation)
    {
        bool worked = false;
        try {
            matlab::data::TypedArray<double> const args = matlab_data_factory->createArray({ 1,observations.size() }, observations.begin(), observations.end());

            
            matlab::data::TypedArray<double> const max_ = matlab_engine->feval(u"max", args); *max = max_[0];
            matlab::data::TypedArray<double> const min_ = matlab_engine->feval(u"min", args); *min = min_[0];
            matlab::data::TypedArray<double> const mean_ = matlab_engine->feval(u"mean", args); *mean = mean_[0];
            if (observations.size() == 1)
            {
                *standard_deviation = 0;
            }
            else
            {
                matlab::data::TypedArray<double> const std_ = matlab_engine->feval(u"std", args);
                *standard_deviation = std_[0];
            }
            worked = true;
        }
        catch (std::exception ex)
        {
            const char* what = ex.what();
        }
        catch (...)
        {
            worked = false;
        }
        return worked;
    }

    ModelRunStatistics* AnalysisEngine::analyse_model_run(const std::string* label, std::string* model_run_key)
    {
        std::vector<model::PopulationState*>* population_states = (persistence::PersistenceProvider::get_persistence_provider_instance())()->read_population_states(model_run_key);
        if (population_states == nullptr) { return 0; /* not valid */ }
        model::PopulationState* final_poulation_state = nullptr;
        unsigned int valid_sequence_length = 0;
        ModelRunStatistics* model_run_statistics = nullptr;
        if (population_states->size() > 100 && ((final_poulation_state = *(population_states->end() - 1))->new_activity == 0))
        {
            model_run_statistics = new ModelRunStatistics(*model_run_key);
            valid_sequence_length = population_states->size();
            model_run_statistics->post_1 = final_poulation_state->post_strain1_activity;
            model_run_statistics->post_2 = final_poulation_state->post_strain2_activity;
            model_run_statistics->initial = final_poulation_state->initial_state;
            model_run_statistics->length = final_poulation_state->length_of_activity;
            unsigned int first_strain_2 = 0;
            unsigned int initial_state = 0;
            for (std::vector<model::PopulationState*>::iterator it = population_states->begin(); it != population_states->end(); ++it)
            {
                initial_state = (*it)->initial_state;
                if ((*it)->new_activity > model_run_statistics->max) 
                { 
                    model_run_statistics->max = (*it)->new_activity; 
                    model_run_statistics->immunity_at_peak = 1.0 - ((double)(*it)->initial_state / (double)(*(population_states->begin()))->initial_state);
                }
                if ((*it)->new_strain1_activity > model_run_statistics->max_1) { model_run_statistics->max_1 = (*it)->new_strain1_activity; }
                if ((*it)->new_strain2_activity > model_run_statistics->max_2) { model_run_statistics->max_2 = (*it)->new_strain2_activity; }
                if ((*it)->post_strain1_activity > model_run_statistics->max_post_1) { model_run_statistics->max_post_1 = (*it)->post_strain1_activity; }
                if ((*it)->new_strain2_activity > 0 && first_strain_2 == 0) { first_strain_2 = (*it)->length_of_activity; }
                if (first_strain_2 > 0 && model_run_statistics->time_to_dominance == 0 && ((*it)->new_strain2_activity * 10) > ((*it)->new_strain1_activity * 100)) 
                { 
                    model_run_statistics->time_to_dominance = (*it)->length_of_activity - first_strain_2; 
                }
                if (first_strain_2 > 0 && model_run_statistics->time_to_complete_replacement == 0 &&  ((*it)->strain1_activity == 0)) 
                { 
                    model_run_statistics->time_to_complete_replacement = (*it)->length_of_activity - first_strain_2; 
                    model_run_statistics->immunity_at_complete_replacement = 1.0 - ((double)((*it)->initial_state) / (double)(*(population_states->begin()))->initial_state);
                }
            }
            model_run_statistics->immunity_at_end = 1.0 - ((double)(initial_state) / (double)(*(population_states->begin()))->initial_state);
            for (std::vector<model::PopulationState*>::iterator it = population_states->begin(); it != population_states->end(); ++it)
            {
                if ((*it)->new_activity * 100 > model_run_statistics->max * 90)
                {
                    if (model_run_statistics->first_close_max == 0) { model_run_statistics->first_close_max = (*it)->length_of_activity; }
                    model_run_statistics->last_close_max = (*it)->length_of_activity;
                    model_run_statistics->immunity_at_last_90pcnt_max = 1.0 - ((double)((*it)->initial_state) / (double)(*(population_states->begin()))->initial_state);
                }
                if ((*it)->new_activity * 100 > model_run_statistics->max * 75)
                {
                    if (model_run_statistics->first_close_max == 0) { model_run_statistics->first_close_max = (*it)->length_of_activity; }
                    model_run_statistics->immunity_at_last_75pcnt_max = 1.0 - ((double)((*it)->initial_state) / (double)(*(population_states->begin()))->initial_state);
                }
            }
        }
        plotter->generate_matlab_data(population_states, label->c_str(), model_run_key->c_str());
        for (std::vector<model::PopulationState*>::iterator it = population_states->begin(); it != population_states->end(); ++it)
        {
            if (model_run_statistics != nullptr)
            {
                if (model_run_statistics->first_close_max == 0 && (*it)->new_activity * 100 > model_run_statistics->max * 90) { model_run_statistics->first_close_max = (*it)->length_of_activity; }
                if ((*it)->new_activity * 100 > model_run_statistics->max * 90) { model_run_statistics->last_close_max = (*it)->length_of_activity; }
            }
            delete* it;
        }

        delete population_states;

        return model_run_statistics;
    }

}