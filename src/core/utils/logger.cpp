#include <new>
#include "logger.h"

namespace Engine {

Logger* Logger::instance = NULL;
char Logger::tmp_log_buf[1000] = {0};

Logger::Logger( void )
{
     logger_file = fopen("engine_log.txt", "a");
}

Logger* Logger::get_instance( void )
{
     if ( instance == NULL ) {
          instance = new (std::nothrow) Logger;
     }

     return instance;
}

void Logger::log( char* string, int length )
{
     fprintf(logger_file, "%s\n", string);
     fflush(logger_file);
}

} // end namespace Engine

