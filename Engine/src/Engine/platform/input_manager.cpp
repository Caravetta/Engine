#include "input_manager.h"
#include "event_system.h"

namespace Engine {

#define MOUSE_POS_TO_OPENGL( mouse, offset, window ) ((mouse - offset - (window/2)) / (window/2))

Input_Manager* Input_Manager::instance = NULL;

Input_Manager::Input_Manager()
{
    //TODO(JOSH): need to come up with a good way to start all the key events

    key_lut[32] = "KEY_SPACE";
    key_lut[39] = "KEY_APOSTROPHE";
    key_lut[44] = "KEY_COMMA";
    key_lut[45] = "KEY_MINUS";
    key_lut[46] = "KEY_PERIOD";
    key_lut[47] = "KEY_SLASH";
    key_lut[48] = "KEY_0";
    key_lut[49] = "KEY_1";
    key_lut[50] = "KEY_2";
    key_lut[51] = "KEY_3";
    key_lut[52] = "KEY_4";
    key_lut[53] = "KEY_5";
    key_lut[54] = "KEY_6";
    key_lut[55] = "KEY_7";
    key_lut[56] = "KEY_8";
    key_lut[57] = "KEY_9";
    key_lut[59] = "KEY_SEMICOLON";
    key_lut[61] = "KEY_EQUAL";
    key_lut[65] = "KEY_A";
    key_lut[66] = "KEY_B";
    key_lut[67] = "KEY_C";
    key_lut[68] = "KEY_D";
    key_lut[69] = "KEY_E";
    key_lut[70] = "KEY_F";
    key_lut[71] = "KEY_G";
    key_lut[72] = "KEY_H";
    key_lut[73] = "KEY_I";
    key_lut[74] = "KEY_J";
    key_lut[75] = "KEY_K";
    key_lut[76] = "KEY_L";
    key_lut[77] = "KEY_M";
    key_lut[78] = "KEY_N";
    key_lut[79] = "KEY_O";
    key_lut[80] = "KEY_P";
    key_lut[81] = "KEY_Q";
    key_lut[82] = "KEY_R";
    key_lut[83] = "KEY_S";
    key_lut[84] = "KEY_T";
    key_lut[85] = "KEY_U";
    key_lut[86] = "KEY_V";
    key_lut[87] = "KEY_W";
    key_lut[88] = "KEY_X";
    key_lut[89] = "KEY_Y";
    key_lut[90] = "KEY_Z";
    key_lut[91] = "KEY_LEFT_BRACKET";
    key_lut[92] = "KEY_BACKSLASH";
    key_lut[93] = "KEY_RIGHT_BRACKET";
    key_lut[96] = "KEY_GRAVE_ACCENT";
    key_lut[161] = "KEY_WORLD_1";
    key_lut[162] = "KEY_WORLD_2";
    key_lut[256] = "KEY_ESCAPE";
    key_lut[257] = "KEY_ENTER";
    key_lut[258] = "KEY_TAB";
    key_lut[259] = "KEY_BACKSPACE";
    key_lut[260] = "KEY_INSERT";
    key_lut[261] = "KEY_DELETE";
    key_lut[262] = "KEY_RIGHT";
    key_lut[263] = "KEY_LEFT";
    key_lut[264] = "KEY_DOWN";
    key_lut[265] = "KEY_UP";
    key_lut[266] = "KEY_PAGE_UP";
    key_lut[267] = "KEY_PAGE_DOWN";
    key_lut[268] = "KEY_HOME";
    key_lut[269] = "KEY_END";
    key_lut[280] = "KEY_CAPS_LOCK";
    key_lut[281] = "KEY_SCROLL_LOCK";
    key_lut[282] = "KEY_NUM_LOCK";
    key_lut[283] = "KEY_PRINT_SCREEN";
    key_lut[284] = "KEY_PAUSE";
    key_lut[290] = "KEY_F1";
    key_lut[291] = "KEY_F2";
    key_lut[292] = "KEY_F3";
    key_lut[293] = "KEY_F4";
    key_lut[294] = "KEY_F5";
    key_lut[295] = "KEY_F6";
    key_lut[296] = "KEY_F7";
    key_lut[297] = "KEY_F8";
    key_lut[298] = "KEY_F9";
    key_lut[299] = "KEY_F10";
    key_lut[300] = "KEY_F11";
    key_lut[301] = "KEY_F12";
    key_lut[302] = "KEY_F13";
    key_lut[303] = "KEY_F14";
    key_lut[304] = "KEY_F15";
    key_lut[305] = "KEY_F16";
    key_lut[306] = "KEY_F17";
    key_lut[307] = "KEY_F18";
    key_lut[308] = "KEY_F19";
    key_lut[309] = "KEY_F20";
    key_lut[310] = "KEY_F21";
    key_lut[311] = "KEY_F22";
    key_lut[312] = "KEY_F23";
    key_lut[313] = "KEY_F24";
    key_lut[314] = "KEY_F25";
    key_lut[320] = "KEY_KP_0";
    key_lut[321] = "KEY_KP_1";
    key_lut[322] = "KEY_KP_2";
    key_lut[323] = "KEY_KP_3";
    key_lut[324] = "KEY_KP_4";
    key_lut[325] = "KEY_KP_5";
    key_lut[326] = "KEY_KP_6";
    key_lut[327] = "KEY_KP_7";
    key_lut[328] = "KEY_KP_8";
    key_lut[329] = "KEY_KP_9";
    key_lut[330] = "KEY_KP_DECIMAL";
    key_lut[331] = "KEY_KP_DIVIDE";
    key_lut[332] = "KEY_KP_MULTIPLY";
    key_lut[333] = "KEY_KP_SUBTRACT";
    key_lut[334] = "KEY_KP_ADD";
    key_lut[335] = "KEY_KP_ENTER";
    key_lut[336] = "KEY_KP_EQUAL";
    key_lut[340] = "KEY_LEFT_SHIFT";
    key_lut[341] = "KEY_LEFT_CONTROL";
    key_lut[342] = "KEY_LEFT_ALT";
    key_lut[343] = "KEY_LEFT_SUPER";
    key_lut[344] = "KEY_RIGHT_SHIFT";
    key_lut[345] = "KEY_RIGHT_CONTROL";
    key_lut[346] = "KEY_RIGHT_ALT";
    key_lut[347] = "KEY_RIGHT_SUPER";
    key_lut[348] = "KEY_MENU";

    for ( int i = 0; i < 350; i++ ) {
        if ( !key_lut[i].empty() ) {
            Event_Manager::create_event_id(key_lut[i] + "_PRESSED");
            Event_Manager::create_event_id(key_lut[i] + "_RELEASED");
        }
    }

    Event_Manager::create_event_id(MOUSE_POS_CHANGE);
}

Input_Manager* Input_Manager::get_instance()
{
    if ( instance == NULL ) {
        LOG("Initializing Input_Manager");
        instance = new Input_Manager;
    }
    return instance;
}

void Input_Manager::process_key_down( uint16_t pressed_key )
{
    Event_Manager::broadcast_event(key_lut[pressed_key] + "_PRESSED", NULL, 0);
    return;
}

void Input_Manager::process_key_up( uint16_t released_key )
{
    Event_Manager::broadcast_event(key_lut[released_key] + "_RELEASED", NULL, 0);
    return;
}

void Input_Manager::process_mouse_move( uint64_t x_pos, uint64_t y_pos )
{
    UNUSED_ARG(x_pos);
    UNUSED_ARG(y_pos);

    Event_Manager::broadcast_event(MOUSE_POS_CHANGE, NULL, 0);
}

} // end namespace core
