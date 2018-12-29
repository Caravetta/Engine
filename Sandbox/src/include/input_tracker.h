#ifndef __INPUT_TRACKER_H__
#define __INPUT_TRACKER_H__

namespace Input_Tracker {

typedef enum {
    W_KEY_STATE = 0,
    A_KEY_STATE,
    S_KEY_STATE,
    D_KEY_STATE,
    KEY_STATE_COUNT,
} tracked_keys_t;

void init();
bool is_key_pressed( tracked_keys_t key );

} // end namespace Input_Tracker

#endif //__INPUT_TRACKER_H__
