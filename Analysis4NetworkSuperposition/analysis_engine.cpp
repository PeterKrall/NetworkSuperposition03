#include "analysis_engine.h"
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

    }
    AnalysisEngine::~AnalysisEngine()
    {

    }
    analysis AnalysisEngine::start_analysis = &analyse;
    matlab::data::ArrayFactory* AnalysisEngine::get_matlab_data_factory() { return matlab_data_factory; };
    std::unique_ptr<MATLABEngine>* AnalysisEngine::get_matlab_engine() { return &matlab_engine; }
    unsigned int AnalysisEngine::run_analysis()
    {
        return 0;
    }
}