#include "task.h"
#include "engine.h"

void core::Task::tick()
{
    if (state != RUNNING) return;
    if (counter++ >= interval)
    {
        core::Engine::instance().post(event);
        counter = 0;
        if (loop > 0) loop--;
        if (loop == 0) state = NONE;
    }
}

void core::Task::start(uint32_t interval, int32_t loop)
{
    this->interval = interval;
    this->counter = 0;
    this->loop = loop;
    state = RUNNING;
}

void core::Task::stop()
{
    state = NONE;
}
