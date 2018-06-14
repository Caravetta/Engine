#if !defined(PLATFORM_H)

#ifdef WINDOWS
#include "win_32/window/window_win32.h"
#include "win_32/utils/utils_win32.h"
#include "win_32/thread/thread_win32.h"
#include "win_32/opengl/opengl.h"
#include "win_32/opengl/shader.h"
#include "win_32/opengl/vao.h"
#include "win_32/opengl/vbo.h"
#else
#error No Headers for platform
#endif

#define PLATFORM_H
#endif
