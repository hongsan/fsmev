#ifndef UART_EVENT_H
#define UART_EVENT_H
#include "controller.h"

inline M_EVENT_HANDLER(uart::Controller,receiveHeader)
{
    if (UART_READ == HEADER_INDICATOR)
    {
        rxNextEvent_ = &uart::Controller::receiveLengthEvent;
    }
}

inline M_EVENT_HANDLER(uart::Controller,receiveLength)
{
    rxLength_ =  UART_READ;
    if (rxLength_ > MAX_PACKET_LENGTH) rxNextEvent_ = &uart::Controller::receiveHeaderEvent;
    else rxNextEvent_ = &uart::Controller::receiveType1Event;
}

inline M_EVENT_HANDLER(uart::Controller,receiveType1)
{
    rxType_  =  UART_READ;
    rxNextEvent_ = &uart::Controller::receiveType2Event;
}

inline M_EVENT_HANDLER(uart::Controller,receiveType2)
{
    rxType_ <<= 8;
    rxType_  +=  UART_READ;
    if (rxLength_>0)
    {
        rxNextEvent_ = &uart::Controller::receiveDataEvent;
        rxIndex_ = 0;
    }
    else rxNextEvent_ = &uart::Controller::receiveFooterEvent;
}

inline M_EVENT_HANDLER(uart::Controller,receiveData)
{
    rxBuffer_[rxIndex_] = UART_READ;
    rxIndex_++;
    if (rxIndex_ == rxLength_) rxNextEvent_ = &uart::Controller::receiveFooterEvent;
}

inline M_EVENT_HANDLER(uart::Controller,receiveFooter)
{
    rxNextEvent_ = &uart::Controller::receiveHeaderEvent;
    if (UART_READ == FOOTER_INDICATOR)
    {
        Command* it = commands_;
        while (it!=nullptr)
        {
            if (it->type==rxType_)
            {
                rxNextEvent_ = nullptr;
                currentHandler_ = it->handler;
                M_EVENT_POST(uart::Controller, processCommand);
                break;
            }
            it=it->next;
        }
    }
}

inline M_EVENT_HANDLER(uart::Controller,processCommand)
{
    if (currentHandler_)
    {
        (*currentHandler_)(rxLength_, rxBuffer_);
        currentHandler_ = nullptr;
    }
    rxNextEvent_ = &uart::Controller::receiveHeaderEvent;
}

inline M_EVENT_HANDLER(uart::Controller,send)
{
    if (txQueue_.empty())
    {
        sending_ = false;
        return;
    }
    if (UART_TX_READY) UART_WRITE(txQueue_.pop());
}

#endif // EVENT_H
