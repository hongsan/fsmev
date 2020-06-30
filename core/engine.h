#ifndef CORE_ENGINE_H
#define CORE_ENGINE_H
#include "config.h"
#include <stdint.h>
#include "component.h"
#include "task.h"

namespace core
{

class Engine
{
public:
    static Engine& instance()
    {
        static Engine engine;
        return engine;
    }
    ~Engine(){}

    void run();
    void post(Event e);

    Task* registerTask(Event e);
    Task* getTask(Event e);
    void tick(); /*must be called in timer interrupt or SysTick interrupt, 1ms usually*/
private:
    Engine();
    Event events_[EVENT_QUEUE_SIZE];
    Event* first_;
    Event* last_;
    Event* inPtr_;
    Event* outPtr_;

    Task* tasks_ = nullptr;
};

}

inline void core::Engine::run()
{
    while (true)
    {
        if (outPtr_ == inPtr_)
        {
            WAIT_FOR_INTERUPT; //sleep
        }
        else
        {
            Event e = *outPtr_;
            outPtr_++;
            if (outPtr_ == last_) outPtr_ = first_;
            if (e != nullptr) (*e)();
        }
    }
}

inline void core::Engine::tick()
{
    Task* it = tasks_;
    while (it!=nullptr)
    {
        it->tick();
        it = it->next;
    }
}

#endif // ENGINE_H
