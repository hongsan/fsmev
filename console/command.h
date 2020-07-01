#ifndef CONSOLE_COMMAND_H
#define CONSOLE_COMMAND_H

namespace console
{
enum Command
{
    MessageReceived = 1,
    GetItem = 100,
    PushItem,
    GetChart,
    PushChart,
    GetPlot,
    PushPlot,
    UpdateVariable,
};

}

#endif // COMMAND_H
