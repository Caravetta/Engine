#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#ifdef LINUX
#include "window_linux.h"

#elif WINDOWS
#include "window_win32.h"
#include "opengl.h"
#endif

#endif //__PLATFORM_H__
