#ifndef UART_CONTROLLER_H_
#define UART_CONTROLLER_H_

#define HEADER_INDICATOR	0xFE
#define FOOTER_INDICATOR	0xFD
#define MAX_PACKET_LENGTH	250

#include "core/queue.h"
#include "core/engine.h"
#include "command.h"
#include "stm32f1.h"

#define TX_BUF_SIZE   2048

COMPONENT(uart, Controller)
    M_EVENT(receiveHeader);
    M_EVENT(receiveLength);
    M_EVENT(receiveType1);
    M_EVENT(receiveType2);
    M_EVENT(receiveData);
    M_EVENT(receiveFooter);
    M_EVENT(processCommand);
    M_EVENT(send);
public:
    void init();
    void nextReceiveEvent();

    void print(char* text);
    void printf(char* format, ...);
    bool sendPacket(uint16_t type, uint8_t length, const uint8_t* data);
    void registerCommand(uint16_t type, Handler handler);
private:
    /*tx*/
    core::Queue txQueue_;
    uint8_t txBuf_[TX_BUF_SIZE];

    /*rx*/
    uint8_t rxBuffer_[MAX_PACKET_LENGTH];
    uint8_t rxLength_;
    core::Event rxNextEvent_;
    uint8_t rxIndex_;
    uint16_t rxType_;

    bool sending_ = false;
    Handler currentHandler_=nullptr;
    Command* commands_ = nullptr;
    void initUART_();
COMPONENT_END

#include "event.h" //for inline member function work

inline void uart::Controller::nextReceiveEvent()
{
    if (rxNextEvent_!=nullptr) core::Engine::instance().post(rxNextEvent_);
}

#endif /* UART_CONTROLLER_H_ */
