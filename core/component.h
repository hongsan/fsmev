#ifndef CORE_COMPONENT_H
#define CORE_COMPONENT_H

namespace core
{

class Component
{
public:
    virtual void init(){}
};

}

#define COMPONENT(module, name)\
namespace module{\
class name: public core::Component{\
public:\
    static name& instance(){static name instance;return instance;}\
private:\
    name(){}

#define COMPONENT_END };}
#define COMPONENT_REG(module, name) module::name::instance().init();

/*EVENT IN COMPONENT*/
#define M_EVENT(name)\
public:\
    static void name##Event(){instance().name##Handler##_();}\
private:\
    void name##Handler##_();

#define M_EVENT_HANDLER(cls,name) void cls::name##Handler##_()
#define M_EVENT_POST(cls,name) core::Engine::instance().post(&cls::name##Event)

#endif // COMPONENT_H
