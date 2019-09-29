#ifndef __INPUT_LINUX_H__
#define __INPUT_LINUX_H__

namespace Engine {

enum Platform_Key {
     PLATFORM_W_KEY = 25,
     PLATFORM_A_KEY = 38,
     PLATFORM_S_KEY = 39,
     PLATFORM_D_KEY = 40,
     PLATFORM_KEY_COUNT, //NOTE: This need to be at the end of the enum
};

extern bool key_state[PLATFORM_KEY_COUNT];

} // end namespace Engine

#endif //__INPUT_LINUX_H__
