#include <Engine.h>

class Sandbox : public Engine::Application {
public:
Sandbox()
{

}

~Sandbox()
{

}

};

Engine::Application* Engine::create_application()
{
    return new Sandbox;
}
