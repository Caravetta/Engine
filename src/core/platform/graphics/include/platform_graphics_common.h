#ifndef __PLATFORM_GRAPHICS_COMMON_H__
#define __PLATFORM_GRAPHICS_COMMON_H__

#ifdef WINDOWS
     #define GRAPHICS_API __declspec(dllexport)

#elif LINUX
     #define GRAPHICS_API __attribute__ ((visibility ("default")))

#else
     #error
#endif

namespace Engine {

enum Clear_Mask {
     COLOR_BUFFER_CLEAR = 1 << 0,
     DEPTH_BUFFER_CLEAR = 1 << 1,
};

enum Data_Type {
     FLOAT_DATA = 0,
};

enum Draw_Mode {
     TRIANGLE_MODE = 0,
};

enum Graphics_Option {
     DEPTH_TEST = 0,
};

enum Depth_Func {
     DEPTH_LESS_FUNC = 0,
};

} // end namespace Engine

#endif