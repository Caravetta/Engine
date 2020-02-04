#include <vector>
#include "input_linux.h"

namespace Engine {

enum Linux_Key {
     LINUX_KEY_SPACE          = 32,
     LINUX_KEY_APOSTROPHE     = 39,
     LINUX_KEY_COMMA          = 44,
     LINUX_KEY_MINUS          = 45,
     LINUX_KEY_PERIOD         = 46,
     LINUX_KEY_SLASH          = 47,
     LINUX_KEY_0              = 48,
     LINUX_KEY_1              = 49,
     LINUX_KEY_2              = 50,
     LINUX_KEY_3              = 51,
     LINUX_KEY_4              = 52,
     LINUX_KEY_5              = 53,
     LINUX_KEY_6              = 54,
     LINUX_KEY_7              = 55,
     LINUX_KEY_8              = 56,
     LINUX_KEY_9              = 57,
     LINUX_KEY_SEMICOLON      = 59,
     LINUX_KEY_EQUAL          = 61,
     LINUX_KEY_GRAVE          = 96,
     LINUX_KEY_A              = 97,
     LINUX_KEY_B              = 98,
     LINUX_KEY_C              = 99,
     LINUX_KEY_D              = 100,
     LINUX_KEY_E              = 101,
     LINUX_KEY_F              = 102,
     LINUX_KEY_G              = 103,
     LINUX_KEY_H              = 104,
     LINUX_KEY_I              = 105,
     LINUX_KEY_J              = 106,
     LINUX_KEY_K              = 107,
     LINUX_KEY_L              = 108,
     LINUX_KEY_M              = 109,
     LINUX_KEY_N              = 110,
     LINUX_KEY_O              = 111,
     LINUX_KEY_P              = 112,
     LINUX_KEY_Q              = 113,
     LINUX_KEY_R              = 114,
     LINUX_KEY_S              = 115,
     LINUX_KEY_T              = 116,
     LINUX_KEY_U              = 117,
     LINUX_KEY_V              = 118,
     LINUX_KEY_W              = 119,
     LINUX_KEY_X              = 120,
     LINUX_KEY_Y              = 121,
     LINUX_KEY_Z              = 122,
     LINUX_KEY_ENTER          = 65293,
     LINUX_KEY_ESCAPE         = 65307,
     LINUX_KEY_SHIFT          = 65505,
     LINUX_KEY_COUNT, //Note: This must be at the end
};

static Key linux_key_map[LINUX_KEY_COUNT] = { KEY_UNKNOWN };
std::vector<platform_key_event_cb> platform_key_callbacks;
std::vector<platform_mouse_move_event_cb> platform_mouse_move_callbacks;

Rc_t init_platform_input_system( void )
{
     linux_key_map[LINUX_KEY_SPACE]          = KEY_SPACE;
     linux_key_map[LINUX_KEY_APOSTROPHE]     = KEY_APOSTROPHE;
     linux_key_map[LINUX_KEY_COMMA]          = KEY_COMMA;
     linux_key_map[LINUX_KEY_MINUS]          = KEY_MINUS;
     linux_key_map[LINUX_KEY_PERIOD]         = KEY_PERIOD;
     linux_key_map[LINUX_KEY_SLASH]          = KEY_SLASH;
     linux_key_map[LINUX_KEY_0]              = KEY_0;
     linux_key_map[LINUX_KEY_1]              = KEY_1;
     linux_key_map[LINUX_KEY_2]              = KEY_2;
     linux_key_map[LINUX_KEY_3]              = KEY_3;
     linux_key_map[LINUX_KEY_4]              = KEY_4;
     linux_key_map[LINUX_KEY_5]              = KEY_5;
     linux_key_map[LINUX_KEY_6]              = KEY_6;
     linux_key_map[LINUX_KEY_7]              = KEY_7;
     linux_key_map[LINUX_KEY_8]              = KEY_8;
     linux_key_map[LINUX_KEY_9]              = KEY_9;
     linux_key_map[LINUX_KEY_SEMICOLON]      = KEY_SEMICOLON;
     linux_key_map[LINUX_KEY_EQUAL]          = KEY_EQUAL;
     linux_key_map[LINUX_KEY_GRAVE]          = KEY_GRAVE_ACCENT;
     linux_key_map[LINUX_KEY_A]              = KEY_A;
     linux_key_map[LINUX_KEY_B]              = KEY_B;
     linux_key_map[LINUX_KEY_C]              = KEY_C;
     linux_key_map[LINUX_KEY_D]              = KEY_D;
     linux_key_map[LINUX_KEY_E]              = KEY_E;
     linux_key_map[LINUX_KEY_F]              = KEY_F;
     linux_key_map[LINUX_KEY_G]              = KEY_G;
     linux_key_map[LINUX_KEY_H]              = KEY_H;
     linux_key_map[LINUX_KEY_I]              = KEY_I;
     linux_key_map[LINUX_KEY_J]              = KEY_J;
     linux_key_map[LINUX_KEY_K]              = KEY_K;
     linux_key_map[LINUX_KEY_L]              = KEY_L;
     linux_key_map[LINUX_KEY_M]              = KEY_M;
     linux_key_map[LINUX_KEY_N]              = KEY_N;
     linux_key_map[LINUX_KEY_O]              = KEY_O;
     linux_key_map[LINUX_KEY_P]              = KEY_P;
     linux_key_map[LINUX_KEY_Q]              = KEY_Q;
     linux_key_map[LINUX_KEY_R]              = KEY_R;
     linux_key_map[LINUX_KEY_S]              = KEY_S;
     linux_key_map[LINUX_KEY_T]              = KEY_T;
     linux_key_map[LINUX_KEY_U]              = KEY_U;
     linux_key_map[LINUX_KEY_V]              = KEY_V;
     linux_key_map[LINUX_KEY_W]              = KEY_W;
     linux_key_map[LINUX_KEY_X]              = KEY_X;
     linux_key_map[LINUX_KEY_Y]              = KEY_Y;
     linux_key_map[LINUX_KEY_Z]              = KEY_Z;
     linux_key_map[LINUX_KEY_ENTER]          = KEY_ENTER;
     linux_key_map[LINUX_KEY_ESCAPE]         = KEY_ESCAPE;
     linux_key_map[LINUX_KEY_SHIFT]          = KEY_RIGHT_SHIFT;

     return SUCCESS;
}

void platform_key_event( uint32_t key, bool is_pressed )
{
     //LOG("Key: %d is_pressed: %d", key, is_pressed);

     if ( key > LINUX_KEY_COUNT ) {
          LOG_ERROR("Key %" PRIu32 " is larger than the key mapping", key);
          return;
     }

     for ( size_t ii = 0; ii < platform_key_callbacks.size(); ii++ ) {
          //LOG("MAP %d", linux_key_map[key]);
          platform_key_callbacks[ii](linux_key_map[key], is_pressed);
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

