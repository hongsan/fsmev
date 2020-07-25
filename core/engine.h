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
    void lock(){locking_ = true;}
    void unlock(){locking_ = false;}
private:
    Engine();
    Event events_[EVENT_QUEUE_SIZE];
    volatile Event* first_;
    volatile Event* last_;
    volatile Event* inPtr_;
    volatile Event* outPtr_;
    volatile bool locking_ = false;
    Task* tasks_ = nullptr;
};

}

#endif // ENGINE_H
