#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#ifdef LINUX
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>
#include "window_linux.h"
#include "thread_linux.h"
#include "utils_linux.h"
#include "input_linux.h"
#include "key_scancode_linux.h"

#elif WINDOWS
#include "window_win32.h"
#include "thread_win32.h"
#include "opengl.h"
#include "utils_win32.h"
#include "input_win32.h"
#include "key_scancode_win32.h"

#endif

#endif //__PLATFORM_H__

