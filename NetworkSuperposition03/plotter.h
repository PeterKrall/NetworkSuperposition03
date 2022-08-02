#ifndef PLOTTER_H
#define PLOTTER_H
#include "MatlabEngine.hpp"
#include "MatlabDataArray.hpp"
#include <vector>
namespace model
{
	using namespace matlab::engine;
	class Plotter
	{
	public:
		Plotter();
		void plot();
		void test();
	private:
		std::vector<double> sampled_time(int samples, double ts, double start = 0); // for test
	};
}
#endif
