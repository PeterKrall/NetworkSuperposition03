#include "writer.h"
#include "configuration.h"
#include <stdio.h>

namespace model
{
    Writer::Writer(char* model_run_key)
	{
        sprintf_s(this->model_run_key, "%s", model_run_key);
	}
    
    Writer::~Writer()  {   }
    open_writer_function* Writer::get_open_writer()
    { 
        if (open_writer == nullptr || close_writer == nullptr) { throw "no valid writer definition"; }
        return open_writer;  
    }
    close_writer_function* Writer::get_close_writer() { return close_writer; }
    open_writer_function* Writer::open_writer = nullptr;
    close_writer_function* Writer::close_writer = nullptr;
}