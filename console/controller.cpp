#include "controller.h"
#include "core/engine.h"
#include "uart/controller.h"
#include "command.h"

void console::Controller::init()
{
    U_COMMAND_REG(console::GetItem, console::Controller, getItem);
    U_COMMAND_REG(console::GetPlot, console::Controller, getPlot);
    U_COMMAND_REG(console::GetPlot, console::Controller, getChart);
}

U_COMMAND_HANDLER(console::Controller, getItem)
{
    /*TODO*/
}

U_COMMAND_HANDLER(console::Controller, getPlot)
{
    /*TODO*/
}

U_COMMAND_HANDLER(console::Controller, getChart)
{
    /*TODO*/
}

void console::Controller::updateVariable(uint16_t command, int32_t value)
{
    /*TODO*/
}

void console::Controller::addSection(char* name)
{
    Item* item = new Item();
    item->type = SECTION;
    item->name = name;
    addItem_(item);
}

void console::Controller::addVariable(uint16_t command, char* name, int32_t min, int32_t max, uart::Handler handler)
{
    Item* item = new Item();
    item->type = VARIABLE;
    item->command = command;
    item->handler = handler;
    item->name = name;
    item->min = min;
    item->max = max;
    uart::Controller::instance().registerCommand(command, handler);
    addItem_(item);
}

void console::Controller::addAction(uint16_t command, char* name, uart::Handler handler)
{
    Item* item = new Item();
    item->type = ACTION;
    item->command = command;
    item->handler = handler;
    item->name = name;
    uart::Controller::instance().registerCommand(command, handler);
    addItem_(item);
}

void console::Controller::addItem_(Item* item)
{
    item->next = nullptr;
    if (items_ == nullptr) items_ = item;
    else
    {
        Item* it = items_;
        while (it->next != nullptr) {it = it->next;}
        it->next = item;
    }
}

