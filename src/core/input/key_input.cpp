#include <vector>
#include "key_input.h"
#include "platform.h"

#define IS_SHIFT_PRESSED() (is_key_pressed(KEY_LEFT_SHIFT) || is_key_pressed(KEY_RIGHT_SHIFT))

namespace Engine {

void key_event_callback( Key key, bool is_pressed );

bool key_states[KEY_MAX_COUNT] = { false };
std::vector<key_event_cb> key_event_callbacks;

Rc_t init_key_input_system( void )
{
     platform_add_key_callback(key_event_callback);
     init_platform_input_system();

     return SUCCESS;
}

void add_key_callback( key_event_cb callback )
{
     key_event_callbacks.push_back(callback);
}

bool is_key_pressed( Key key )
{
     return key_states[key];
}

char key_to_char( Key key )
{
     char c_key = -1;

     if ( key >= KEY_A && key <= KEY_Z ) {
          if ( is_key_pressed(KEY_LEFT_SHIFT) || is_key_pressed(KEY_RIGHT_SHIFT) ) {
               c_key = key;
          } else {
               c_key = key + 32;
          }
     } else if ( key >= KEY_0 && key <= KEY_9 ) {
          if ( is_key_pressed(KEY_LEFT_SHIFT) || is_key_pressed(KEY_RIGHT_SHIFT) ) {
               switch ( key ) {
               case KEY_0:
                    c_key = ')';
                    break;
               case KEY_1:
                    c_key = '!';
                    break;
               case KEY_2:
                    c_key = '@';
                    break;
               case KEY_3:
                    c_key = '#';
                    break;
               case KEY_4:
                    c_key = '$';
                    break;
               case KEY_5:
                    c_key = '%';
                    break;
               case KEY_6:
                    c_key = '^';
                    break;
               case KEY_7:
                    c_key = '&';
                    break;
               case KEY_8:
                    c_key = '*';
                    break;
               case KEY_9:
                    c_key = '(';
                    break;
               default:
                    LOG_ERROR("Got a value that was not a number");
                    break;
               }
          } else {
               c_key = key;
          }
     } else {
          switch ( key ) {
          case KEY_SPACE:
               c_key = key;
               break;
          case KEY_APOSTROPHE:
               c_key = IS_SHIFT_PRESSED() ? '"' : key;
               break;
          case KEY_COMMA:
               c_key = IS_SHIFT_PRESSED() ? '<' : key;
               break;
          case KEY_MINUS:
               c_key = IS_SHIFT_PRESSED() ? '_' : key;
               break;
          case KEY_PERIOD:
               c_key = IS_SHIFT_PRESSED() ? '>' : key;
               break;
          case KEY_SLASH:
               c_key = IS_SHIFT_PRESSED() ? '?' : key;
               break;
          case KEY_SEMICOLON:
               c_key = IS_SHIFT_PRESSED() ? ':' : key;
               break;
          case KEY_EQUAL:
               c_key = IS_SHIFT_PRESSED() ? '+' : key;
               break;
          case KEY_LEFT_BRACKET:
               c_key = IS_SHIFT_PRESSED() ? '{' : key;
               break;
          case KEY_BACKSLASH:
               c_key = IS_SHIFT_PRESSED() ? '|' : key;
               break;
          case KEY_RIGHT_BRACKET:
               c_key = IS_SHIFT_PRESSED() ? '}' : key;
               break;
          case KEY_GRAVE_ACCENT:
               c_key = IS_SHIFT_PRESSED() ? '~' : key;
               break;
          case KEY_TAB:
               c_key = 0x9;
               break;
          default:
               break;
          }

     }

     return c_key;
}

void key_event_callback( Key key, bool is_pressed )
{
     key_states[key] = is_pressed;

     for ( size_t ii = 0; ii < key_event_callbacks.size(); ii++ ) {
          key_event_callbacks[ii](key, is_pressed);
     }
}

} // end namespace Engine

