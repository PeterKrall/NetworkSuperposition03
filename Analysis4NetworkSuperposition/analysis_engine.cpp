#include "analysis_engine.h"
#include "persistence.h"

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
        return (matlab_initialized = (v == 2));
    }
    unsigned int analyse()
    {
        if (!initialize_matlab_access())
        {
            throw "matlab not accessible!";
        }
        srand(time(NULL));
        AnalysisEngine* analysis_enginge = new AnalysisEngine();
        unsigned int result = analysis_enginge->run_analysis();
        delete(analysis_enginge);
        return result;
    }
    AnalysisEngine::AnalysisEngine()
    {
        configurations = nullptr;
    }
    AnalysisEngine::~AnalysisEngine()
    {
        /*
        for (auto it = std::begin(v); it != std::end(v); ++it) 
        {
            std::cout << *it << "\n";
        }
        */
    }
    analysis AnalysisEngine::start_analysis = &analyse;
    matlab::data::ArrayFactory* AnalysisEngine::get_matlab_data_factory() { return matlab_data_factory; };
    std::unique_ptr<MATLABEngine>* AnalysisEngine::get_matlab_engine() { return &matlab_engine; }
    unsigned int AnalysisEngine::run_analysis()
    {
       std::vector<model::Configuration*>* configurations = (persistence::PersistenceProvider::get_persistence_provider_instance())()->read_configurations();
        for (std::vector<model::Configuration*>::iterator it = configurations->begin(); it != configurations->end(); ++it) 
        {
            analyse_model_runs(*it);
            delete* it;
        }
        delete configurations;
        return 0;
    }
    unsigned int AnalysisEngine::analyse_model_runs(model::Configuration* configuration)
    {
        std::vector<std::string*>* model_runs = (persistence::PersistenceProvider::get_persistence_provider_instance())()->read_model_runs(configuration);
        for (std::vector<std::string*>::iterator it = model_runs->begin(); it != model_runs->end(); ++it)
        {
            analyse_model_run(*it);
            delete* it;
        }
        delete model_runs;

        return 0;
    }
    unsigned int AnalysisEngine::analyse_model_run(std::string* model_run_key)
    {
        std::vector<model::PopulationState*>* population_states = (persistence::PersistenceProvider::get_persistence_provider_instance())()->read_population_states(model_run_key);
        for (std::vector<model::PopulationState*>::iterator it = population_states->begin(); it != population_states->end(); ++it)
        {            
            delete* it;
        }
        delete population_states;

        return 0;
    }

}