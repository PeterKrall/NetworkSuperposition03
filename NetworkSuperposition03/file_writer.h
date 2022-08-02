#ifndef FILE_WRITER
#define FILE_WRITER
#include "writer.h"
#include <iostream>
#include <fstream>

namespace persistence
{
	// file-writing implementation of Writer interface
	class FileWriter : public virtual model::Writer 
	{
	protected:
		FileWriter(char* model_run_key);
		~FileWriter();
	public:
		virtual void persist_population_state(model::PopulationState* population_state);
	private:
		std::ofstream out;
		static model::Writer* create(char* model_run_key);
		static void destroy(model::Writer*);
		static bool is_activated;
		static bool activate_conditionally();
	private:
		static FileWriter* instance;
	};
}
#endif // !FILE_WRITER

