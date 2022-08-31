#ifndef RUN_STATISTICS_H
#define RUN_STATISTICS_H
#include <string>
namespace analysis
{
	class ModelRunStatistics
	{
	public:
		ModelRunStatistics(std::string& model_run_key);
		const std::string model_run_key;
		unsigned int max = 0;
		unsigned int max_1 = 0;
		unsigned int max_2 = 0;
		unsigned int max_post_1 = 0;
		unsigned int post_1 = 0;
		unsigned int post_2 = 0;
		unsigned int initial = 0;
		unsigned int length = 0;
		unsigned int time_to_dominance = 0;
		unsigned int time_to_complete_replacement = 0;
		unsigned int first_close_max = 0;
		unsigned int last_close_max = 0;
		double immunity_at_complete_replacement = 1.0;
		double immunity_at_last_90pcnt_max = 0.0;
		double immunity_at_last_75pcnt_max = 0.0;
		double immunity_at_peak = 0;
		double immunity_at_end = 0;
	};
}
#endif
