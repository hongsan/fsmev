#ifndef CORE_QUEUE_H
#define CORE_QUEUE_H
#include <stdint.h>

namespace core
{

class Queue
{
public:
    Queue(){}
    void init(uint8_t* buf, uint16_t size)
    {
        first_ = buf;
        size_ = size;
        available_ = size;
        last_ = first_ + size;
        inPtr_ = first_;
        outPtr_ = first_;
    }
    void push(uint8_t val)
    {
        if (available_ > 0)
        {
            *(inPtr_) = val;
            inPtr_++;
            if (inPtr_ == last_) inPtr_ = first_;
            available_--;
        }
    }
    uint8_t pop()
    {
        if (available_ < size_)
        {
            uint8_t ret = *(outPtr_);
            outPtr_++;
            if (outPtr_ == last_) outPtr_ = first_;
            available_++;
            return ret;
        }
        return 0;
    }
    uint16_t available(){return available_;}
    bool notEmpty(){return (available_ < size_);}
    bool empty(){return (available_ == size_);}
private:
    uint16_t size_;
    uint8_t* first_;
    uint8_t* last_;
    uint8_t* inPtr_;
    uint8_t* outPtr_;
    uint16_t available_;
};

}

#endif // QUEUE_H
