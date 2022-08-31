#ifndef ANALYSIS_ENGINE_H
#define ANALYSIS_ENGINE_H
#include "configuration.h"
#include "run_statistics.h"
#include "MatlabEngine.hpp"
#include "MatlabDataArray.hpp"
#include "plotter.h"
namespace analysis
{
    using namespace matlab::engine;

    typedef unsigned int (*analysis)(const char* output_directory);

    class AnalysisEngine
    {
    public:
        AnalysisEngine();
        ~AnalysisEngine();
        unsigned int run_analysis(const char* output_directory);
        static matlab::data::ArrayFactory* get_matlab_data_factory();
        static std::unique_ptr<MATLABEngine>* get_matlab_engine();
        static analysis start_analysis;
    private:
        std::vector<model::Configuration*>* configurations = nullptr;
        unsigned int analyse_model_runs(model::Configuration* configuration);
        ModelRunStatistics* analyse_model_run(const std::string* label, std::string* model_run);
        bool compute_statistics_component(std::vector<int>& observation, unsigned int*, unsigned int*, double*, double*);
        bool compute_statistics_component(std::vector<double>& observation, double*, double*, double*, double*);
        Plotter* plotter = nullptr;
    };
}
#endif