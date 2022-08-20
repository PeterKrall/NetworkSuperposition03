#ifndef MODEL_MODEL_H
#define MODEL_MODEL_H

#include "configuration.h"
#include "population.h"
#include "basicstablenet.h"
#include "aggregatedstablenet.h"
#include "aggregatednetwithfluctuation.h"
#include "basicnetwithfluctuation.h"
#include "writer.h"

namespace model
{
    
    typedef unsigned int (*model_execution)();

    class Model
    {
    public:
        Model();
        ~Model();
        static model_execution run_model;
        unsigned int run();        
    private:
        AggregatedNetWithFluctuation** aggregated_nets_with_fluctuation;
        BasicNetWithFluctuation** basic_nets_with_fluctuation;
        AggregatedStableNet** aggregated_stable_nets;
        BasicStableNet** basic_stable_nets;                
        Writer* writer = nullptr;
    };

} // namespace model

#endif // MODEL_MODEL_H
