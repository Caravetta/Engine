#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#ifdef LINUX
#include "../core_common.h"
#include "linux/window/window_linux.h"
#include "linux/utils/utils_linux.h"
#include "linux/thread/thread_linux.h"
#include "linux/opengl/opengl.h"
#include "linux/opengl/shader.h"
#include "linux/opengl/vao.h"
#include "linux/opengl/vbo.h"

#elif WINDOWS_PLATFORM
#include "../core_common.h"
#include "win_32/window/window_win32.h"
#include "win_32/utils/utils_win32.h"
#include "win_32/thread/thread_win32.h"
#include "win_32/opengl/opengl.h"
#include "win_32/opengl/shader.h"
#include "win_32/opengl/vao.h"
#include "win_32/opengl/vbo.h"
#endif

#endif //__PLATFORM_H__
