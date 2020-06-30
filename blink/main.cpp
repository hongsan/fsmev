#include "core/engine.h"
#include "uart/controller.h"
#include "blink/controller.h"

int main()
{
    COMPONENT_REG(blink, Controller);
    COMPONENT_REG(uart, Controller);
    core::Engine::instance().run();
    return 0;
}
