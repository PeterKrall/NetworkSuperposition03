#ifndef MODEL_MODEL_H
#define MODEL_MODEL_H

#include "configuration.h"
#include "population.h"
#include "basicstablenet.h"
#include "aggregatedstablenet.h"
#include "aggregatednetwithfluctuation.h"
#include "basicnetwithfluctuation.h"
#include "plotter.h"
#include "writer.h"
#include "MatlabEngine.hpp"
#include "MatlabDataArray.hpp"

namespace model
{
    using namespace matlab::engine;
    
    typedef unsigned int (*model_execution)();

    class Model
    {
    public:
        Model();
        ~Model();
        static model_execution run_model;
        unsigned int run();        
        static matlab::data::ArrayFactory* get_matlab_data_factory();
        static std::unique_ptr<MATLABEngine>* get_matlab_engine();
    private:
        AggregatedNetWithFluctuation** aggregated_nets_with_fluctuation;
        BasicNetWithFluctuation** basic_nets_with_fluctuation;
        AggregatedStableNet** aggregated_stable_nets;
        BasicStableNet** basic_stable_nets;                
        Plotter* plotter = nullptr;
        Writer* writer = nullptr;
    };

} // namespace model

#endif // MODEL_MODEL_H
