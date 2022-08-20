#ifndef ANALYSIS_ENGINE_H
#define ANALYSIS_ENGINE_H
#include "configuration.h"
#include "MatlabEngine.hpp"
#include "MatlabDataArray.hpp"

namespace analysis
{
    using namespace matlab::engine;

    typedef unsigned int (*analysis)();

    class AnalysisEngine
    {
    public:
        AnalysisEngine();
        ~AnalysisEngine();
        unsigned int run_analysis();
        static matlab::data::ArrayFactory* get_matlab_data_factory();
        static std::unique_ptr<MATLABEngine>* get_matlab_engine();
        static analysis start_analysis;
    private:
        std::vector<model::Configuration*>* configurations = nullptr;
        unsigned int analyse_model_runs(model::Configuration* configuration);
        unsigned int analyse_model_run(std::string* model_run);
    };
}
#endif