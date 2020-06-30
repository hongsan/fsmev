#ifndef UART_COMMAND_H
#define UART_COMMAND_H
#include <stdint.h>

namespace uart
{
    typedef void (*Handler)(uint8_t length, uint8_t* data);
    struct Command
    {
        uint16_t type;
        Handler handler;
        Command* next;
    };
}

/*Command in Component*/
#define U_COMMAND(name)\
public:\
    static void name##Command(uint8_t length, uint8_t* data){instance().name##CommandHandler##_(length,data);}\
private:\
    void name##CommandHandler##_(uint8_t length, uint8_t* data);

#define U_COMMAND_HANDLER(cls,name) void cls::name##CommandHandler##_(uint8_t length, uint8_t* data)
#define U_COMMAND_REG(type, cls,name) uart::Controller::instance().registerCommand(type, &cls::name##Command);

#endif // COMMAND_H
