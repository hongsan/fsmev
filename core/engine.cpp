#include "engine.h"
#include "config.h"

core::Engine::Engine()
{
    first_ = events_;
    last_ = first_ + EVENT_QUEUE_SIZE;
    inPtr_ = first_;
    outPtr_ = first_;
}

void core::Engine::run()
{
    while (1)
    {
        if (locking_ || (outPtr_ == inPtr_))
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

void core::Engine::tick()
{
    Task* it = tasks_;
    while (it!=nullptr)
    {
        it->tick();
        it = it->next;
    }
}

void core::Engine::post(core::Event e)
{
    DISABLE_INTERRUPT;
    volatile Event* next = inPtr_ + 1;
    if (next == last_) next = first_;

    if (next!=outPtr_) //queue not full
    {
        *(inPtr_) = e;
        inPtr_ = next;
    }
    ENABLE_INTERRUPT;
}

core::Task* core::Engine::registerTask(Event e)
{
    Task* t = new Task();
    t->event = e;
    t->interval = 0;
    t->counter = 0;
    t->loop = -1;
    t->state = core::Task::NONE;
    t->next = tasks_;
    tasks_ = t;
    return t;
}

core::Task* core::Engine::getTask(Event e)
{
    Task* it = tasks_;
    while (it!=nullptr)
    {
        if (it->event == e) return it;
        it = it->next;
    }
    return nullptr;
}
