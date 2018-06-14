#if !defined(PLATFORM_H)

#ifdef LINUX
#error LINUX is not currently implemented
#else
#include "../core_common.h"
#include "win_32/window/window_win32.h"
#include "win_32/utils/utils_win32.h"
#include "win_32/thread/thread_win32.h"
#include "win_32/opengl/opengl.h"
#include "win_32/opengl/shader.h"
#include "win_32/opengl/vao.h"
#include "win_32/opengl/vbo.h"
#endif

#define PLATFORM_H
#endif
