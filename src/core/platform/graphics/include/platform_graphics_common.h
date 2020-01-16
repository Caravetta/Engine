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
     ACCUM_BUFFER_CLEAR = 1 << 2,
};

enum Data_Type {
     FLOAT_DATA = 0,
     UNSIGNED_BYTE,
     UNSIGNED_SHORT,
     UNSIGNED_INT,
     UNSIGNED_INT_24_8,
};

enum Usage_Type {
     STATIC_DRAW,
     STREAM_DRAW,
};

enum Draw_Mode {
     TRIANGLE_MODE = 0,
};

enum Graphics_Option {
     DEPTH_TEST_OPTION = 0,
     BLEND_OPTION,
     CULL_FACE_OPTION,
     SCISSOR_TEST_OPTION,
};

enum Depth_Func {
     DEPTH_LESS_FUNC = 0,
};

enum Texture_Format {
     RGB_FORMAT,
     RGBA_FORMAT,
     RGB_16F_FORMAT,
     DEPTH24_STENCIL8_FORMAT,
     GL_DEPTH_STENCIL,
};

enum Buffer_Type {
     ELEMENT_ARRAY_BUFFER,
     ARRAY_BUFFER,
};

enum Attachment_Type {
     COLOR_ATTACHMENT_0 = 0,
     COLOR_ATTACHMENT_1,
     COLOR_ATTACHMENT_2,
     GL_DEPTH_STENCIL_ATTACHMENT,
};

enum Texture_Unit {
     TEXTURE_UNIT_0 = 0,
     TEXTURE_UNIT_1,
     TEXTURE_UNIT_2,
     TEXTURE_UNIT_3,
};

#define INVALID_FBO_HANDLE 0
typedef uint64_t Fbo_Handle;

#define INVALID_TEXTURE_HANDLE 0
typedef unsigned int Texture_Handle;

} // end namespace Engine

#endif
