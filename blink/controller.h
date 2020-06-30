#ifndef BLINK_CONTROLLER_H
#define BLINK_CONTROLLER_H
#include "core/engine.h"
#include "uart/controller.h"
#include "core/queue.h"

COMPONENT(blink, Controller)
    M_EVENT(toggle)

    U_COMMAND(start)
    U_COMMAND(stop)
public:
    void init();
private:
    void initGPIO_();
    void initSystem_();
    void initTimer4_();

    core::Task* toggle_;
COMPONENT_END

#endif // CONTROLLER_H
