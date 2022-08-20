#include "plotter.h"
#include "analysis_engine.h"
#include "configuration.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <numeric>
namespace analysis
{
	Plotter::Plotter()
	{
        std::time_t t = std::time(0);
        std::tm now_; std::tm* now = &now_;
        localtime_s(&now_, &t);
        char buffer[4096];
        sprintf_s(
            buffer
            , "%smodel_run__%d_%d_%d_%d_%d_%d.png"
            , model::Configuration::configuration->output_directory.c_str()
            , now->tm_year + 1900, now->tm_mon + 1, now->tm_mday, now->tm_hour, now->tm_min, now->tm_sec
        );
        // out.open(buffer);

	}
    void Plotter::plot() {}
    using std::cout;
    using std::vector;
    using std::string;
    using std::ofstream;
    using std::ios_base;

    class Sinewave // a plot-test-class
    {
    public:
        vector<double> yvals;
        vector<double> xvals;

        // yvals = sin(a*t + b) and ownership of t is transferred to this object (as xvals) if it's an R-value
        // a = angular frequency; the value resulting from 2*pi*f
        // b = initial phase, in radians
        Sinewave(double a, double b, vector<double>&& t) : xvals(std::move(t))
        {
            yvals = vector<double>(xvals.size());
            // Compute the angle values
            std::transform(xvals.begin(), xvals.end(), yvals.begin(), [a, b](double xval) -> double {return a * xval + b; });

            // Compute the sin-values
            std::transform(yvals.begin(), yvals.end(), yvals.begin(), [](double angle) -> double {return sin(angle); });
        }

        // Transfer ownership of other SineSignal object's yvals, xvals
        Sinewave(const Sinewave&& other) noexcept
            : yvals(std::move(yvals)), xvals(std::move(xvals)) {}

        
        // Uses the Matlab Engine API for C++ to invoke Matlab's plot command and open a figure window (part of test)
        void plot_in_matlab()
        {
            std::unique_ptr<matlab::engine::MATLABEngine> MLPtr = matlab::engine::startMATLAB();
            matlab::data::ArrayFactory factory;

            // Create arguments for the call to Matlab's plot function
            std::vector<matlab::data::Array> args({
                factory.createArray({ xvals.size(), 1 }, xvals.begin(), xvals.end()),
                factory.createArray({ yvals.size(), 1 }, yvals.begin(), yvals.end()),
                factory.createCharArray(std::string("ro"))
                });

            // Invoke the plot command
            (*AnalysisEngine::get_matlab_engine())->feval(u"plot", args);
        }
    };

    /* Returns multiples of Ts, the sampling period in seconds, beginning at tStart. (as part of test) */
    std::vector<double> Plotter::sampled_time(int samples, double ts, double start)
    {
        vector<double> tvals(samples);
        std::iota(tvals.begin(), tvals.end(), start);
        std::transform(tvals.begin(), tvals.end(), tvals.begin(), [ts](double sampleVal) -> double {return sampleVal * ts; });
        return tvals;
    }

    void Plotter::test()
    {
        // first test - is matlab here at all?
        std::vector<matlab::data::Array> args({ AnalysisEngine::get_matlab_data_factory()->createScalar<int16_t>(30), AnalysisEngine::get_matlab_data_factory()->createScalar<int16_t>(25) });
        matlab::data::TypedArray<int16_t> result = (*AnalysisEngine::get_matlab_engine())->feval(u"gcd", args);
        int16_t v = result[0];
        assert(v == (int16_t)5);
        // second test - plot a wave
        double fs = 300; // Sampling frequency, in Hz
        int nCycles = 2, nSamples = (int)((double)nCycles * fs); // Number of sine-wave cycles
        vector<double> tvals = sampled_time(nSamples, 1 / fs);

        const double pi = 3.141592653589793;
        double w = 2 * pi * 1, poff = pi; // 1 Hz sinewave, 180 deg. out of phase 
        auto sw = Sinewave(w, poff, std::move(tvals));
        sw.plot_in_matlab();
    }
}