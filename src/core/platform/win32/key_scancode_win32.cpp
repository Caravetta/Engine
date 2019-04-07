#include <string>
#include "core_common.h"
#include "key_scancode_win32.h"

namespace Engine {

key_t scancode_to_key_map[ MAX_SCANCODE_COUNT ];
std::string scancode_to_string_map[ MAX_SCANCODE_COUNT ];

void init_scancode_to_key_map( void )
{
    scancode_to_key_map[ SCANCODE_ESCAPE ]              = KEY_ESCAPE;
    scancode_to_key_map[ SCANCODE_1 ]                   = KEY_1;
    scancode_to_key_map[ SCANCODE_2 ]                   = KEY_2;
    scancode_to_key_map[ SCANCODE_3 ]                   = KEY_3;
    scancode_to_key_map[ SCANCODE_4 ]                   = KEY_4;
    scancode_to_key_map[ SCANCODE_5 ]                   = KEY_5;
    scancode_to_key_map[ SCANCODE_6 ]                   = KEY_6;
    scancode_to_key_map[ SCANCODE_7 ]                   = KEY_7;
    scancode_to_key_map[ SCANCODE_8 ]                   = KEY_8;
    scancode_to_key_map[ SCANCODE_9 ]                   = KEY_9;
    scancode_to_key_map[ SCANCODE_0 ]                   = KEY_0;
    scancode_to_key_map[ SCANCODE_MINUS ]               = KEY_MINUS;
    scancode_to_key_map[ SCANCODE_EQUALS ]              = KEY_EQUALS;
    scancode_to_key_map[ SCANCODE_BACKSPACE ]           = KEY_BACKSPACE;
    scancode_to_key_map[ SCANCODE_TAB ]                 = KEY_TAB;
    scancode_to_key_map[ SCANCODE_Q ]                   = KEY_Q;
    scancode_to_key_map[ SCANCODE_W ]                   = KEY_W;
    scancode_to_key_map[ SCANCODE_E ]                   = KEY_E;
    scancode_to_key_map[ SCANCODE_R ]                   = KEY_R;
    scancode_to_key_map[ SCANCODE_T ]                   = KEY_T;
    scancode_to_key_map[ SCANCODE_Y ]                   = KEY_Y;
    scancode_to_key_map[ SCANCODE_U ]                   = KEY_U;
    scancode_to_key_map[ SCANCODE_I ]                   = KEY_I;
    scancode_to_key_map[ SCANCODE_O ]                   = KEY_O;
    scancode_to_key_map[ SCANCODE_P ]                   = KEY_P;
    scancode_to_key_map[ SCANCODE_BRACKETLEFT ]         = KEY_BRACKETLEFT;
    scancode_to_key_map[ SCANCODE_BRACKETRIGHT ]        = KEY_BRACKETRIGHT;
    scancode_to_key_map[ SCANCODE_ENTER ]               = KEY_ENTER;
    scancode_to_key_map[ SCANCODE_CONTROLLEFT ]         = KEY_CONTROLLEFT;
    scancode_to_key_map[ SCANCODE_A ]                  = KEY_A;
    scancode_to_key_map[ SCANCODE_S ]                  = KEY_S;
    scancode_to_key_map[ SCANCODE_D ]                  = KEY_D;
    scancode_to_key_map[ SCANCODE_F ]                  = KEY_F;
    scancode_to_key_map[ SCANCODE_G ]                  = KEY_G;
    scancode_to_key_map[ SCANCODE_H ]                  = KEY_H;
    scancode_to_key_map[ SCANCODE_J ]                  = KEY_J;
    scancode_to_key_map[ SCANCODE_K ]                  = KEY_K;
    scancode_to_key_map[ SCANCODE_L ]                  = KEY_L;
    scancode_to_key_map[ SCANCODE_SEMICOLON ]          = KEY_SEMICOLON;
    scancode_to_key_map[ SCANCODE_APOSTROPHE ]         = KEY_APOSTROPHE;
    scancode_to_key_map[ SCANCODE_GRAVE ]              = KEY_GRAVE;
    scancode_to_key_map[ SCANCODE_SHIFTLEFT ]          = KEY_SHIFTLEFT;
    scancode_to_key_map[ SCANCODE_BACKSLASH ]          = KEY_BACKSLASH;
    scancode_to_key_map[ SCANCODE_Z ]                  = KEY_Z;
    scancode_to_key_map[ SCANCODE_X ]                  = KEY_X;
    scancode_to_key_map[ SCANCODE_C ]                  = KEY_C;
    scancode_to_key_map[ SCANCODE_V ]                  = KEY_V;
    scancode_to_key_map[ SCANCODE_B ]                  = KEY_B;
    scancode_to_key_map[ SCANCODE_N ]                  = KEY_N;
    scancode_to_key_map[ SCANCODE_M ]                  = KEY_M;
    scancode_to_key_map[ SCANCODE_COMMA ]              = KEY_COMMA;
    scancode_to_key_map[ SCANCODE_PREIOD ]             = KEY_PREIOD;
    scancode_to_key_map[ SCANCODE_SLASH ]              = KEY_SLASH;
    scancode_to_key_map[ SCANCODE_SHIFTRIGHT ]         = KEY_SHIFTRIGHT;
    scancode_to_key_map[ SCANCODE_NUMPAD_MULTIPLY ]    = KEY_NUMPAD_MULTIPLY;
    scancode_to_key_map[ SCANCODE_ALTLEFT ]            = KEY_ALTLEFT;
    scancode_to_key_map[ SCANCODE_SPACE ]              = KEY_SPACE;
    scancode_to_key_map[ SCANCODE_CAPSLOCK ]           = KEY_CAPSLOCK;
    scancode_to_key_map[ SCANCODE_F1 ]                 = KEY_F1;
    scancode_to_key_map[ SCANCODE_F2 ]                 = KEY_F2;
    scancode_to_key_map[ SCANCODE_F3 ]                 = KEY_F3;
    scancode_to_key_map[ SCANCODE_F4 ]                 = KEY_F4;
    scancode_to_key_map[ SCANCODE_F5 ]                 = KEY_F5;
    scancode_to_key_map[ SCANCODE_F6 ]                 = KEY_F6;
    scancode_to_key_map[ SCANCODE_F7 ]                 = KEY_F7;
    scancode_to_key_map[ SCANCODE_F8 ]                 = KEY_F8;
    scancode_to_key_map[ SCANCODE_F9 ]                 = KEY_F9;
    scancode_to_key_map[ SCANCODE_F10 ]                = KEY_F10;
    scancode_to_key_map[ SCANCODE_NUMLOCK ]            = KEY_NUMLOCK;
    scancode_to_key_map[ SCANCODE_SCROLLLOCK ]         = KEY_SCROLLLOCK;
    scancode_to_key_map[ SCANCODE_NUMPAD_7 ]           = KEY_NUMPAD_7;
    scancode_to_key_map[ SCANCODE_NUMPAD_8 ]           = KEY_NUMPAD_8;
    scancode_to_key_map[ SCANCODE_NUMPAD_9 ]           = KEY_NUMPAD_9;
    scancode_to_key_map[ SCANCODE_NUMPAD_MINUS ]       = KEY_NUMPAD_MINUS;
    scancode_to_key_map[ SCANCODE_NUMPAD_4 ]           = KEY_NUMPAD_4;
    scancode_to_key_map[ SCANCODE_NUMPAD_5 ]           = KEY_NUMPAD_5;
    scancode_to_key_map[ SCANCODE_NUMPAD_6 ]           = KEY_NUMPAD_6;
    scancode_to_key_map[ SCANCODE_NUMPAD_PLUS ]        = KEY_NUMPAD_PLUS;
    scancode_to_key_map[ SCANCODE_NUMPAD_1 ]           = KEY_NUMPAD_1;
    scancode_to_key_map[ SCANCODE_NUMPAD_2 ]           = KEY_NUMPAD_2;
    scancode_to_key_map[ SCANCODE_NUMPAD_3 ]           = KEY_NUMPAD_3;
    scancode_to_key_map[ SCANCODE_NUMPAD_0 ]           = KEY_NUMPAD_0;
    scancode_to_key_map[ SCANCODE_NUMPAD_PERIOD ]      = KEY_NUMPAD_PERIOD;
    scancode_to_key_map[ SCANCODE_ALT_PRINTSCREEN ]    = KEY_ALT_PRINTSCREEN;
    scancode_to_key_map[ SCANCODE_BRACKETANGLE ]       = KEY_BRACKETANGLE;
    scancode_to_key_map[ SCANCODE_F11 ]                = KEY_F11;
    scancode_to_key_map[ SCANCODE_F12 ]                = KEY_F12;

    scancode_to_string_map[ SCANCODE_ESCAPE ]              = "KEY_ESCAPE";
    scancode_to_string_map[ SCANCODE_1 ]                   = "KEY_1";
    scancode_to_string_map[ SCANCODE_2 ]                   = "KEY_2";
    scancode_to_string_map[ SCANCODE_3 ]                   = "KEY_3";
    scancode_to_string_map[ SCANCODE_4 ]                   = "KEY_4";
    scancode_to_string_map[ SCANCODE_5 ]                   = "KEY_5";
    scancode_to_string_map[ SCANCODE_6 ]                   = "KEY_6";
    scancode_to_string_map[ SCANCODE_7 ]                   = "KEY_7";
    scancode_to_string_map[ SCANCODE_8 ]                   = "KEY_8";
    scancode_to_string_map[ SCANCODE_9 ]                   = "KEY_9";
    scancode_to_string_map[ SCANCODE_0 ]                   = "KEY_0";
    scancode_to_string_map[ SCANCODE_MINUS ]               = "KEY_MINUS";
    scancode_to_string_map[ SCANCODE_EQUALS ]              = "KEY_EQUALS";
    scancode_to_string_map[ SCANCODE_BACKSPACE ]           = "KEY_BACKSPACE";
    scancode_to_string_map[ SCANCODE_TAB ]                 = "KEY_TAB";
    scancode_to_string_map[ SCANCODE_Q ]                   = "KEY_Q";
    scancode_to_string_map[ SCANCODE_W ]                   = "KEY_W";
    scancode_to_string_map[ SCANCODE_E ]                   = "KEY_E";
    scancode_to_string_map[ SCANCODE_R ]                   = "KEY_R";
    scancode_to_string_map[ SCANCODE_T ]                   = "KEY_T";
    scancode_to_string_map[ SCANCODE_Y ]                   = "KEY_Y";
    scancode_to_string_map[ SCANCODE_U ]                   = "KEY_U";
    scancode_to_string_map[ SCANCODE_I ]                   = "KEY_I";
    scancode_to_string_map[ SCANCODE_O ]                   = "KEY_O";
    scancode_to_string_map[ SCANCODE_P ]                   = "KEY_P";
    scancode_to_string_map[ SCANCODE_BRACKETLEFT ]         = "KEY_BRACKETLEFT";
    scancode_to_string_map[ SCANCODE_BRACKETRIGHT ]        = "KEY_BRACKETRIGHT";
    scancode_to_string_map[ SCANCODE_ENTER ]               = "KEY_ENTER";
    scancode_to_string_map[ SCANCODE_CONTROLLEFT ]         = "KEY_CONTROLLEFT";
    scancode_to_string_map[ SCANCODE_A ]                  = "KEY_A";
    scancode_to_string_map[ SCANCODE_S ]                  = "KEY_S";
    scancode_to_string_map[ SCANCODE_D ]                  = "KEY_D";
    scancode_to_string_map[ SCANCODE_F ]                  = "KEY_F";
    scancode_to_string_map[ SCANCODE_G ]                  = "KEY_G";
    scancode_to_string_map[ SCANCODE_H ]                  = "KEY_H";
    scancode_to_string_map[ SCANCODE_J ]                  = "KEY_J";
    scancode_to_string_map[ SCANCODE_K ]                  = "KEY_K";
    scancode_to_string_map[ SCANCODE_L ]                  = "KEY_L";
    scancode_to_string_map[ SCANCODE_SEMICOLON ]          = "KEY_SEMICOLON";
    scancode_to_string_map[ SCANCODE_APOSTROPHE ]         = "KEY_APOSTROPHE";
    scancode_to_string_map[ SCANCODE_GRAVE ]              = "KEY_GRAVE";
    scancode_to_string_map[ SCANCODE_SHIFTLEFT ]          = "KEY_SHIFTLEFT";
    scancode_to_string_map[ SCANCODE_BACKSLASH ]          = "KEY_BACKSLASH";
    scancode_to_string_map[ SCANCODE_Z ]                  = "KEY_Z";
    scancode_to_string_map[ SCANCODE_X ]                  = "KEY_X";
    scancode_to_string_map[ SCANCODE_C ]                  = "KEY_C";
    scancode_to_string_map[ SCANCODE_V ]                  = "KEY_V";
    scancode_to_string_map[ SCANCODE_B ]                  = "KEY_B";
    scancode_to_string_map[ SCANCODE_N ]                  = "KEY_N";
    scancode_to_string_map[ SCANCODE_M ]                  = "KEY_M";
    scancode_to_string_map[ SCANCODE_COMMA ]              = "KEY_COMMA";
    scancode_to_string_map[ SCANCODE_PREIOD ]             = "KEY_PREIOD";
    scancode_to_string_map[ SCANCODE_SLASH ]              = "KEY_SLASH";
    scancode_to_string_map[ SCANCODE_SHIFTRIGHT ]         = "KEY_SHIFTRIGHT";
    scancode_to_string_map[ SCANCODE_NUMPAD_MULTIPLY ]    = "KEY_NUMPAD_MULTIPLY";
    scancode_to_string_map[ SCANCODE_ALTLEFT ]            = "KEY_ALTLEFT";
    scancode_to_string_map[ SCANCODE_SPACE ]              = "KEY_SPACE";
    scancode_to_string_map[ SCANCODE_CAPSLOCK ]           = "KEY_CAPSLOCK";
    scancode_to_string_map[ SCANCODE_F1 ]                 = "KEY_F1";
    scancode_to_string_map[ SCANCODE_F2 ]                 = "KEY_F2";
    scancode_to_string_map[ SCANCODE_F3 ]                 = "KEY_F3";
    scancode_to_string_map[ SCANCODE_F4 ]                 = "KEY_F4";
    scancode_to_string_map[ SCANCODE_F5 ]                 = "KEY_F5";
    scancode_to_string_map[ SCANCODE_F6 ]                 = "KEY_F6";
    scancode_to_string_map[ SCANCODE_F7 ]                 = "KEY_F7";
    scancode_to_string_map[ SCANCODE_F8 ]                 = "KEY_F8";
    scancode_to_string_map[ SCANCODE_F9 ]                 = "KEY_F9";
    scancode_to_string_map[ SCANCODE_F10 ]                = "KEY_F10";
    scancode_to_string_map[ SCANCODE_NUMLOCK ]            = "KEY_NUMLOCK";
    scancode_to_string_map[ SCANCODE_SCROLLLOCK ]         = "KEY_SCROLLLOCK";
    scancode_to_string_map[ SCANCODE_NUMPAD_7 ]           = "KEY_NUMPAD_7";
    scancode_to_string_map[ SCANCODE_NUMPAD_8 ]           = "KEY_NUMPAD_8";
    scancode_to_string_map[ SCANCODE_NUMPAD_9 ]           = "KEY_NUMPAD_9";
    scancode_to_string_map[ SCANCODE_NUMPAD_MINUS ]       = "KEY_NUMPAD_MINUS";
    scancode_to_string_map[ SCANCODE_NUMPAD_4 ]           = "KEY_NUMPAD_4";
    scancode_to_string_map[ SCANCODE_NUMPAD_5 ]           = "KEY_NUMPAD_5";
    scancode_to_string_map[ SCANCODE_NUMPAD_6 ]           = "KEY_NUMPAD_6";
    scancode_to_string_map[ SCANCODE_NUMPAD_PLUS ]        = "KEY_NUMPAD_PLUS";
    scancode_to_string_map[ SCANCODE_NUMPAD_1 ]           = "KEY_NUMPAD_1";
    scancode_to_string_map[ SCANCODE_NUMPAD_2 ]           = "KEY_NUMPAD_2";
    scancode_to_string_map[ SCANCODE_NUMPAD_3 ]           = "KEY_NUMPAD_3";
    scancode_to_string_map[ SCANCODE_NUMPAD_0 ]           = "KEY_NUMPAD_0";
    scancode_to_string_map[ SCANCODE_NUMPAD_PERIOD ]      = "KEY_NUMPAD_PERIOD";
    scancode_to_string_map[ SCANCODE_ALT_PRINTSCREEN ]    = "KEY_ALT_PRINTSCREEN";
    scancode_to_string_map[ SCANCODE_BRACKETANGLE ]       = "KEY_BRACKETANGLE";
    scancode_to_string_map[ SCANCODE_F11 ]                = "KEY_F11";
    scancode_to_string_map[ SCANCODE_F12 ]                = "KEY_F12";
}

key_t get_key_id( key_scancode_t scancode )
{
    //LOG( scancode );
    if ( scancode < MAX_SCANCODE_COUNT ) {
        //LOG(scancode_to_string_map[scancode]);
        return scancode_to_key_map[scancode];
    }

    return KEY_NUMPAD_3;
}

} // end namespace Engine
