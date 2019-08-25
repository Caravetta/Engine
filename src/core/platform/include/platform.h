#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#ifdef WINDOWS
#include "window_win32.h"
#include "opengl_win32.h"
#elif LINUX
#include "window_linux.h"
#include "opengl_linux.h"
#else
     #error
#endif

#ifdef OPENGL
#include "opengl.h"
#else
     #error
#endif

#endif //__PLATFORM_H__
