#include "platform.h"

#ifdef WINDOWS
#include "win_32/window/window_win32.h"
#include "win_32/window/window_win32.cpp"
#include "win_32/utils/utils_win32.h"
#include "win_32/utils/utils_win32.cpp"
#include "win_32/thread/thread_win32.h"
#include "win_32/thread/thread_win32.cpp"
#include "win_32/opengl/opengl.cpp"
#include "win_32/opengl/shader.cpp"
#include "win_32/opengl/vao.cpp"
#include "win_32/opengl/vbo.cpp"
#elif
#error No files found for your platform
#endif
