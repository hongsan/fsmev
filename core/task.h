#ifndef CORE_TASK_H
#define CORE_TASK_H
#include <stdint.h>

namespace core
{

typedef void (*Event)();

struct Task
{
    enum State{NONE=0, RUNNING};
    void tick();
    void start(uint32_t interval, int32_t loop = -1);
    void stop();

    Task* next;
    uint32_t interval;
    uint32_t counter;
    Event event;
    uint8_t state;
    int32_t loop;
};

}


#endif // TASK_H
