#include <vector>
#include "input_win32.h"

namespace Engine {

enum Win32_Key {
     WIN32_KEY_BACK      = 0x08,
     WIN32_KEY_TAB       = 0x09,
     WIN32_KEY_ENTER     = 0x0D,
     WIN32_KEY_SHIFT     = 0x10,
     WIN32_KEY_CTRL      = 0x11,
     WIN32_KEY_ALT       = 0x12,
     WIN32_KEY_PAUSE     = 0x13,
     WIN32_KEY_CAP       = 0x14,
     WIN32_KEY_ESCAPE    = 0x1B,
     WIN32_KEY_SPACE     = 0x20,
     WIN32_KEY_PAGE_UP   = 0x21,
     WIN32_KEY_PAGE_DOWN = 0x22,
     WIN32_KEY_END       = 0x23,
     WIN32_KEY_HOME      = 0x24,
     WIN32_KEY_LEFT      = 0x25,
     WIN32_KEY_UP        = 0x26,
     WIN32_KEY_RIGHT     = 0x27,
     WIN32_KEY_DOWN      = 0x28,
     WIN32_KEY_SELECT    = 0x29,
     WIN32_KEY_PRINT     = 0x2A,
     WIN32_KEY_EXECUTE   = 0x2B,
     WIN32_KEY_PRINT_SC  = 0x2C,
     WIN32_KEY_INSERT    = 0x2D,
     WIN32_KEY_DELETE    = 0x2E,
     WIN32_KEY_HELP      = 0x2F,
     WIN32_KEY_0         = 0x30,
     WIN32_KEY_1         = 0x31,
     WIN32_KEY_2         = 0x32,
     WIN32_KEY_3         = 0x33,
     WIN32_KEY_4         = 0x34,
     WIN32_KEY_5         = 0x35,
     WIN32_KEY_6         = 0x36,
     WIN32_KEY_7         = 0x37,
     WIN32_KEY_8         = 0x38,
     WIN32_KEY_9         = 0x39,
     WIN32_KEY_A         = 0x41,
     WIN32_KEY_B         = 0x42,
     WIN32_KEY_C         = 0x43,
     WIN32_KEY_D         = 0x44,
     WIN32_KEY_E         = 0x45,
     WIN32_KEY_F         = 0x46,
     WIN32_KEY_G         = 0x47,
     WIN32_KEY_H         = 0x48,
     WIN32_KEY_I         = 0x49,
     WIN32_KEY_J         = 0x4A,
     WIN32_KEY_K         = 0x4B,
     WIN32_KEY_L         = 0x4C,
     WIN32_KEY_M         = 0x4D,
     WIN32_KEY_N         = 0x4E,
     WIN32_KEY_O         = 0x4F,
     WIN32_KEY_P         = 0x50,
     WIN32_KEY_Q         = 0x51,
     WIN32_KEY_R         = 0x52,
     WIN32_KEY_S         = 0x53,
     WIN32_KEY_T         = 0x54,
     WIN32_KEY_U         = 0x55,
     WIN32_KEY_V         = 0x56,
     WIN32_KEY_W         = 0x57,
     WIN32_KEY_X         = 0x58,
     WIN32_KEY_Y         = 0x59,
     WIN32_KEY_Z         = 0x5A,
     WIN32_KEY_MINUS     = 0xBD,
     WIN32_KEY_PERIOD    = 0xBE,
     WIN32_KEY_COUNT, //Note: This must be at the end
};

static Key win32_key_map[WIN32_KEY_COUNT] = { KEY_UNKNOWN };
std::vector<platform_key_event_cb> platform_key_callbacks;
std::vector<platform_mouse_move_event_cb> platform_mouse_move_callbacks;

Rc_t init_platform_input_system( void )
{
     win32_key_map[WIN32_KEY_BACK]           = KEY_BACKSPACE;
     win32_key_map[WIN32_KEY_TAB]            = KEY_TAB;
     win32_key_map[WIN32_KEY_ENTER]          = KEY_ENTER;
     win32_key_map[WIN32_KEY_SHIFT]          = KEY_LEFT_SHIFT;
     win32_key_map[WIN32_KEY_CTRL]           = KEY_LEFT_CONTROL;
     win32_key_map[WIN32_KEY_ALT]            = KEY_LEFT_ALT;
     win32_key_map[WIN32_KEY_PAUSE]          = KEY_PAUSE;
     win32_key_map[WIN32_KEY_CAP]            = KEY_CAPS_LOCK;
     win32_key_map[WIN32_KEY_ESCAPE]         = KEY_ESCAPE;
     win32_key_map[WIN32_KEY_SPACE]          = KEY_SPACE;
     win32_key_map[WIN32_KEY_PAGE_UP]        = KEY_PAGE_UP;
     win32_key_map[WIN32_KEY_PAGE_DOWN]      = KEY_PAGE_DOWN;
     win32_key_map[WIN32_KEY_END]            = KEY_END;
     win32_key_map[WIN32_KEY_HOME]           = KEY_HOME;
     win32_key_map[WIN32_KEY_LEFT]           = KEY_LEFT;
     win32_key_map[WIN32_KEY_UP]             = KEY_UP;
     win32_key_map[WIN32_KEY_RIGHT]          = KEY_RIGHT;
     win32_key_map[WIN32_KEY_DOWN]           = KEY_DOWN;
     win32_key_map[WIN32_KEY_PRINT_SC]       = KEY_PRINT_SCREEN;
     win32_key_map[WIN32_KEY_INSERT]         = KEY_INSERT;
     win32_key_map[WIN32_KEY_DELETE]         = KEY_DELETE;
     win32_key_map[WIN32_KEY_0]              = KEY_0;
     win32_key_map[WIN32_KEY_1]              = KEY_1;
     win32_key_map[WIN32_KEY_2]              = KEY_2;
     win32_key_map[WIN32_KEY_3]              = KEY_3;
     win32_key_map[WIN32_KEY_4]              = KEY_4;
     win32_key_map[WIN32_KEY_5]              = KEY_5;
     win32_key_map[WIN32_KEY_6]              = KEY_6;
     win32_key_map[WIN32_KEY_7]              = KEY_7;
     win32_key_map[WIN32_KEY_8]              = KEY_8;
     win32_key_map[WIN32_KEY_9]              = KEY_9;
     win32_key_map[WIN32_KEY_A]              = KEY_A;
     win32_key_map[WIN32_KEY_B]              = KEY_B;
     win32_key_map[WIN32_KEY_C]              = KEY_C;
     win32_key_map[WIN32_KEY_D]              = KEY_D;
     win32_key_map[WIN32_KEY_E]              = KEY_E;
     win32_key_map[WIN32_KEY_F]              = KEY_F;
     win32_key_map[WIN32_KEY_G]              = KEY_G;
     win32_key_map[WIN32_KEY_H]              = KEY_H;
     win32_key_map[WIN32_KEY_I]              = KEY_I;
     win32_key_map[WIN32_KEY_J]              = KEY_J;
     win32_key_map[WIN32_KEY_K]              = KEY_K;
     win32_key_map[WIN32_KEY_L]              = KEY_L;
     win32_key_map[WIN32_KEY_M]              = KEY_M;
     win32_key_map[WIN32_KEY_N]              = KEY_N;
     win32_key_map[WIN32_KEY_O]              = KEY_O;
     win32_key_map[WIN32_KEY_P]              = KEY_P;
     win32_key_map[WIN32_KEY_Q]              = KEY_Q;
     win32_key_map[WIN32_KEY_R]              = KEY_R;
     win32_key_map[WIN32_KEY_S]              = KEY_S;
     win32_key_map[WIN32_KEY_T]              = KEY_T;
     win32_key_map[WIN32_KEY_U]              = KEY_U;
     win32_key_map[WIN32_KEY_V]              = KEY_V;
     win32_key_map[WIN32_KEY_W]              = KEY_W;
     win32_key_map[WIN32_KEY_X]              = KEY_X;
     win32_key_map[WIN32_KEY_Y]              = KEY_Y;
     win32_key_map[WIN32_KEY_Z]              = KEY_Z;
     win32_key_map[WIN32_KEY_SHIFT]          = KEY_LEFT_SHIFT;
     win32_key_map[WIN32_KEY_MINUS]          = KEY_MINUS;
     win32_key_map[WIN32_KEY_PERIOD]         = KEY_PERIOD;
     return SUCCESS;
}

void platform_key_event( uint32_t key, bool is_pressed )
{
     if ( key > WIN32_KEY_COUNT ) {
          LOG_ERROR("Key %" PRIu32 " is larger than the key mapping", key);
          return;
     }

     for ( size_t ii = 0; ii < platform_key_callbacks.size(); ii++ ) {
          platform_key_callbacks[ii](win32_key_map[key], is_pressed);
     }
}

void platform_add_key_callback( platform_key_event_cb callback )
{
     platform_key_callbacks.push_back(callback);
}

void platform_mouse_move_event( float mx, float my )
{
     for ( size_t ii = 0; ii < platform_mouse_move_callbacks.size(); ii++ ) {
          platform_mouse_move_callbacks[ii](mx, my);
     }
}

void platform_mouse_key_event( uint32_t key, bool is_pressed )
{

}

void platform_add_mouse_move_callback( platform_mouse_move_event_cb callback )
{
     platform_mouse_move_callbacks.push_back(callback);
}

} // end namespace Engine

