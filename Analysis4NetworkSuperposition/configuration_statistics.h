#ifndef CONFIGURATION_STATISTICS_H
#define CONFIGURATION_STATISTICS_H
#include "configuration.h"
namespace analysis
{
	class ConfigurationStatistics : public virtual model::Configuration
	{
	public:
		ConfigurationStatistics(const model::Configuration& core_template);
		unsigned int number_of_runs = 0;
		unsigned int max_max_new = 0;
		unsigned int min_max_new = 0;
		double mean_max_new = 0.0;
		double standard_deviation_max_new = 0.0;
		unsigned int max_max1_new = 0;
		unsigned int min_max1_new = 0;
		double mean_max1_new = 0.0;
		double standard_deviation_max1_new = 0.0;
		unsigned int max_max2_new = 0;
		unsigned int min_max2_new = 0;
		double mean_max2_new = 0.0;
		double standard_deviation_max2_new = 0.0;
		unsigned int max_max_post1 = 0;
		unsigned int min_max_post1 = 0;
		double mean_max_post1 = 0.0;
		double standard_deviation_max_post1 = 0.0;
		unsigned int max_post1_at_end = 0;
		unsigned int min_post1_at_end = 0;
		double mean_post1_at_end = 0.0;
		double standard_deviation_post1_at_end = 0.0;
		unsigned int max_post2_at_end = 0;
		unsigned int min_post2_at_end = 0;
		double mean_post2_at_end = 0.0;
		double standard_deviation_post2_at_end = 0.0;
		unsigned int max_length = 0;
		unsigned int min_length = 0;
		double mean_length = 0.0;
		double standard_deviation_length = 0.0;
		unsigned int max_time_to_dominance = 0;
		unsigned int min_time_to_dominance = 0;
		double mean_time_to_dominance = 0.0;
		double standard_deviation_time_to_dominance = 0.0;
		unsigned int max_time_to_complete_replacement = 0;
		unsigned int min_time_to_complete_replacement = 0;
		double mean_time_to_complete_replacement = 0.0;
		double standard_deviation_time_to_complete_replacement = 0.0;
		double max_immunity_at_peak = 0.0;
		double min_immunity_at_peak  = 0.0;
		double mean_immunity_at_peak  = 0.0;
		double standard_deviation_immunity_at_peak  = 0.0;
		double max_immunity_at_end  = 0.0;
		double min_immunity_at_end  = 0.0;
		double mean_immunity_at_end  = 0.0;
		double standard_deviation_immunity_at_end  = 0.0;
		double max_immunity_at_last90pcnt_max = 0.0;
		double min_immunity_at_last90pcnt_max = 0.0;
		double mean_immunity_at_last90pcnt_max = 0.0;
		double standard_deviation_immunity_at_last90pcnt_max = 0.0;
		double max_immunity_at_last75pcnt_max = 0.0;
		double min_immunity_at_last75pcnt_max = 0.0;
		double mean_immunity_at_last75pcnt_max = 0.0;
		double standard_deviation_immunity_at_last75pcnt_max = 0.0;
		double max_immunity_at_complete_replacement = 0.0;
		double min_immunity_at_complete_replacement = 0.0;
		double mean_immunity_at_complete_replacement = 0.0;
		double standard_deviation_immunity_at_complete_replacement = 0.0;
	};
}
#endif
