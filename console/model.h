#ifndef CONSOLE_MODEL_H
#define CONSOLE_MODEL_H
#include <stdint.h>
#include "core/engine.h"
#include "uart/controller.h"

namespace console
{
    enum ItemType{SECTION = 1, VARIABLE, ACTION};
    enum Color{};

    struct Item
    {
        uint8_t type;
        char* name;
        uint16_t command;
        int32_t min;
        int32_t max;
        uart::Handler handler;
        Item* next;
    };

    struct Plot
    {
        char* name;
        uint32_t offset;
        bool zeroVisible;
        int32_t value;
    };
}

#endif // MODEL_H
