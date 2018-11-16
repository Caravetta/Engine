#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "core_common.h"

namespace Engine {

class ENGINE_API Application {
public:
    Application();
    virtual ~Application();

    void run();
};

Application* create_application();

} // end namespace Engine

#endif // __APPLICATION_H__
