#ifndef __INPUT_WIN32_H__
#define __INPUT_WIN32_H__

namespace Engine {

enum Platform_Key {
     PLATFORM_W_KEY = 0,
     PLATFORM_A_KEY = 0,
     PLATFORM_S_KEY = 0,
     PLATFORM_D_KEY = 0,
     PLATFORM_KEY_COUNT, //NOTE: This need to be at the end of the enum
};

extern bool key_state[PLATFORM_KEY_COUNT];

} // end namespace Engine

#endif //__INPUT_WIN32_H__
