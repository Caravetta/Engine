#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <stdio.h>

namespace Engine {

class Logger {
public:
     static char tmp_log_buf[1000];

     void log( char* string, int length );
     static Logger* get_instance( void );

private:
     Logger( void );
     static Logger* instance;

     FILE* logger_file;
};

} // end namespace Engine

#endif //__LOGGER_H__

