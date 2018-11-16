#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <string>
#include "core_common.h"
#include "platform.h"

namespace Engine {

class Window {
public:

    int width;
    int height;
    std::string title;

    Window( int width, int height, std::string title );
    void update();
    void swap_buffers();
    int get_width();
    int get_height();
    bool is_closed();

private:
    struct platform_window_t* platform_window;
};

} //end namesapce Engine

#endif //__WINDOW_H__
