#ifndef __ENTRY_POINT_H__
#define __ENTRY_POINT_H__

#include "application.h"
#include "../core.h"

extern Engine::Application* Engine::create_application();

int main( int argc, char** argv )
{
    auto application = Engine::create_application();
    application->run();
    delete application;
}

#endif //__ENTRY_POINT_H__
