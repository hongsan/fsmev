#include "command.h"
#include "controller.h"
#include "uart/controller.h"

void blink::Controller::init()
{
    initSystem_();
    initGPIO_();
    initTimer4_();//system tick timer

    /*register uart commands*/
    U_COMMAND_REG(blink::Command::Start, blink::Controller, start);
    U_COMMAND_REG(blink::Command::Start, blink::Controller, stop);

    /*register tasks*/
    toggle_ = core::Engine::instance().registerTask(&blink::Controller::toggleEvent);
}

M_EVENT_HANDLER(blink::Controller,toggle)
{
    /*TODO: led toggle here*/
}

U_COMMAND_HANDLER(blink::Controller, start)
{
    toggle_->start(200); //200ms
    uart::Controller::instance().sendPacket(blink::Command::Started,0,nullptr);
    uart::Controller::instance().print("Blink Started");
}

U_COMMAND_HANDLER(blink::Controller, stop)
{
    toggle_->stop();
    uart::Controller::instance().sendPacket(blink::Command::Started,0,nullptr);
    uart::Controller::instance().print("Blink Stopped");
}
