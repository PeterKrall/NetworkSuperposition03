#ifndef PLOTTER_H
#define PLOTTER_H
#include "run_statistics.h"
#include "MatlabEngine.hpp"
#include "population_state.h"
namespace analysis
{	
	class Plotter
	{
	public:
		Plotter(std::unique_ptr<matlab::engine::MATLABEngine>* engine, const char* output_directory);
		bool generate_matlab_data(std::vector<model::PopulationState*>* population_states, const char* label, const char* model_run_key);
	private:
		std::string output_directory;
		const std::unique_ptr<matlab::engine::MATLABEngine>* engine;
	};
}
#endif
