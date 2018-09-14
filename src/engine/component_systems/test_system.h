#if !defined(TEST_SYSTEM_H)

#include "../core/core.h"

class Test_System : public core::System {
public:
    Test_System();
    void init();
    void update();
    void shutdown();
};

#define TEST_SYSTEM_H
#endif
