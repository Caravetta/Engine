#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#ifdef WINDOWS
     #include "window_win32.h"
#elif LINUX
     #include "window_linux.h"
     #include "input_linux.h"
#else
     #error
#endif

#endif //__PLATFORM_H__
