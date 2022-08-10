#ifndef ANALYSIS_ENGINE_H
#define ANALYSIS_ENGINE_H
#include "persistence.h"
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
        static analysis start_analysis;
        unsigned int run_analysis();
        static matlab::data::ArrayFactory* get_matlab_data_factory();
        static std::unique_ptr<MATLABEngine>* get_matlab_engine();
    };
}
#endif