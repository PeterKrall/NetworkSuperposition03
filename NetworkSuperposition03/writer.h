#ifndef WRITER_H
#define WRITER_H

#include "population_state.h"

namespace model
{
	typedef class Writer* (open_writer_function(char* model_run_key));
	typedef void (close_writer_function(class Writer* writer));
	// the interface for persistence providing classes
	class Writer
	{
	public:
		virtual void persist_population_state(PopulationState* population_state) = 0;
		static open_writer_function* get_open_writer();
		static close_writer_function* get_close_writer();
	protected:
		static open_writer_function* open_writer;		
		static close_writer_function* close_writer;
		Writer(char* model_run_key);
		~Writer();
		char model_run_key[1024];
	};
}
#endif
