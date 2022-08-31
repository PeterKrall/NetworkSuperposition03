#include "plotter.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <numeric>
#include "MatlabDataArray.hpp"
#include "population_state.h"
using std::cout;
using std::vector;
using std::string;
using std::ofstream;
using std::ios_base;
namespace analysis
{
    // this class is intended to become a plotter but by now (August 2022 it just produces an input file of data to be imported into matlab
    Plotter::Plotter(std::unique_ptr<matlab::engine::MATLABEngine>* engine, const char* output_directory) : engine(engine)
    {
        this->output_directory = std::string(output_directory);
    }

    bool Plotter::generate_matlab_data(std::vector<model::PopulationState*>* population_states, const char* label, const char* model_run_key)
    {
        char path[1024];
        sprintf_s(path, "%s%s_%s.csv", output_directory.c_str(), label, model_run_key);
        ofstream matlab_input_file(path, ios_base::trunc);
        unsigned int generation = 0;
        for (generation = 10; generation < 1510; generation ++)
        {
            if (generation < population_states->size())
            {
                matlab_input_file
                    << population_states->at(generation)->new_activity << ","
                    << population_states->at(generation)->new_strain1_activity << ","
                    << population_states->at(generation)->new_strain2_activity << ","
                    << (1.0 - ((double)(population_states->at(generation)->initial_state) / ((double)(population_states->at(0)->initial_state)))) * 1000.9 << "\n";
            }
            else
            {
                matlab_input_file << "0,0,0,0\n";
            }
        }
        
        matlab_input_file.close();
        return true;

    }
}