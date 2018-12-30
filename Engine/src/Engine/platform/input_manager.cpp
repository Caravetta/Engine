#include "input_manager.h"
#include "event_system.h"

namespace Engine {

/* computed key_input_t values */
key_input_t key_pressed_inputs[KEY_ID_MAX];
key_input_t key_released_inputs[KEY_ID_MAX];

/* key state map */
key_state_t key_state[KEY_ID_MAX];

#define DEFKEY(K) { key_names[K] = #K; }

std::string key_names[KEY_ID_MAX];

key_id_t operator ++( key_id_t &id, int )
{
  id = static_cast<key_id_t>( id + 1 );
  return id;
}

#define MOUSE_POS_TO_OPENGL( mouse, offset, window ) ((mouse - offset - (window/2)) / (window/2))

Input_Manager* Input_Manager::instance = NULL;

Input_Manager::Input_Manager()
{
    DEFKEY(KEY_A);
    DEFKEY(KEY_B);
    DEFKEY(KEY_C);
    DEFKEY(KEY_D);
    DEFKEY(KEY_E);
    DEFKEY(KEY_F);
    DEFKEY(KEY_G);
    DEFKEY(KEY_H);
    DEFKEY(KEY_I);
    DEFKEY(KEY_J);
    DEFKEY(KEY_K);
    DEFKEY(KEY_L);
    DEFKEY(KEY_M);
    DEFKEY(KEY_N);
    DEFKEY(KEY_O);
    DEFKEY(KEY_P);
    DEFKEY(KEY_Q);
    DEFKEY(KEY_R);
    DEFKEY(KEY_S);
    DEFKEY(KEY_T);
    DEFKEY(KEY_U);
    DEFKEY(KEY_V);
    DEFKEY(KEY_W);
    DEFKEY(KEY_X);
    DEFKEY(KEY_Y);
    DEFKEY(KEY_Z);
    DEFKEY(KEY_1);
    DEFKEY(KEY_2);
    DEFKEY(KEY_3);
    DEFKEY(KEY_4);
    DEFKEY(KEY_5);
    DEFKEY(KEY_6);
    DEFKEY(KEY_7);
    DEFKEY(KEY_8);
    DEFKEY(KEY_9);
    DEFKEY(KEY_0);
    DEFKEY(KEY_ENTER);
    DEFKEY(KEY_ESCAPE);
    DEFKEY(KEY_BACKSPACE);
    DEFKEY(KEY_TAB);
    DEFKEY(KEY_SPACE);
    DEFKEY(KEY_MINUS);
    DEFKEY(KEY_EQUAL);
    DEFKEY(KEY_LEFT_BRACKET);
    DEFKEY(KEY_RIGHT_BRACKET);
    DEFKEY(KEY_BACKSLASH);
    DEFKEY(KEY_SEMICOLON);
    DEFKEY(KEY_APOSTROPHE);
    DEFKEY(KEY_GRAVE_ACCENT);
    DEFKEY(KEY_COMMA);
    DEFKEY(KEY_DOT);
    DEFKEY(KEY_SLASH);
    DEFKEY(KEY_CAPS_LOCK);
    DEFKEY(KEY_F1);
    DEFKEY(KEY_F2);
    DEFKEY(KEY_F3);
    DEFKEY(KEY_F4);
    DEFKEY(KEY_F5);
    DEFKEY(KEY_F6);
    DEFKEY(KEY_F7);
    DEFKEY(KEY_F8);
    DEFKEY(KEY_F9);
    DEFKEY(KEY_F10);
    DEFKEY(KEY_F11);
    DEFKEY(KEY_F12);
    DEFKEY(KEY_SYSRQ);
    DEFKEY(KEY_SCROLL_LOCK);
    DEFKEY(KEY_PAUSE);
    DEFKEY(KEY_INSERT);
    DEFKEY(KEY_HOME);
    DEFKEY(KEY_PAGE_UP);
    DEFKEY(KEY_DELETE);
    DEFKEY(KEY_END);
    DEFKEY(KEY_PAGE_DOWN);
    DEFKEY(KEY_LEFT);
    DEFKEY(KEY_RIGHT);
    DEFKEY(KEY_DOWN);
    DEFKEY(KEY_UP);
    DEFKEY(KEY_LEFT_CONTROL);
    DEFKEY(KEY_LEFT_SHIFT);
    DEFKEY(KEY_LEFT_ALT);
    DEFKEY(KEY_LEFT_GUI);
    DEFKEY(KEY_RIGHT_CONTROL);
    DEFKEY(KEY_RIGHT_SHIFT);
    DEFKEY(KEY_RIGHT_ALT);
    DEFKEY(KEY_RIGHT_GUI);

    for ( key_id_t i = KEY_NONE; i < KEY_ID_MAX; i++ ) {
        key_pressed_inputs[i] = { i, 0, KeyPressed };
        key_released_inputs[i] = { i, 0, KeyReleased };

        Event_Manager::create_event_id(key_names[i] + "_PRESSED");
        Event_Manager::create_event_id(key_names[i] + "_RELEASED");
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

std::string Input_Manager::get_key_name( key_id_t scancode )
{
    return key_names[scancode];
}

void Input_Manager::process_key_down( key_id_t scancode, uint16_t keysym )
{
    //LOG("KEYDOWN scancode " << (int) scancode << " keysym " << keysym);
    key_pressed_inputs[scancode].keysym = keysym;
    key_state[scancode] = KeyPressed;
    Event_Manager::broadcast_event(key_names[scancode] + "_PRESSED",
        &key_pressed_inputs[scancode], sizeof key_pressed_inputs[scancode]);
    return;
}

void Input_Manager::process_key_up( key_id_t scancode, uint16_t keysym )
{
    key_released_inputs[scancode].keysym = keysym;
    key_state[scancode] = KeyReleased;
    Event_Manager::broadcast_event(key_names[scancode] + "_RELEASED",
        &key_released_inputs[scancode], sizeof key_released_inputs[scancode]);
    return;
}

void Input_Manager::process_mouse_move( uint64_t x_pos, uint64_t y_pos )
{
    UNUSED_ARG(x_pos);
    UNUSED_ARG(y_pos);

    Event_Manager::broadcast_event(MOUSE_POS_CHANGE, NULL, 0);
}

key_state_t key_pressed( key_id_t scancode )
{
    return key_state[scancode];
}

} // end namespace Engine
