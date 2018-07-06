#if !defined(WINDOW_H)

#include <string>
#include "../core_common.h"
#include "../platform/platform.h"

namespace core {

    class CORE_API Window {
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

} //end namesapce core

#define WINDOW_H
#endif
