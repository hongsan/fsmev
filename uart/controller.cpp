#include "controller.h"
#include "core/engine.h"
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

void uart::Controller::init()
{
    initUART_();
    rxNextEvent_ = &uart::Controller::receiveHeaderEvent; //initial state
    txQueue_.init(txBuf_,TX_BUF_SIZE);
}

void uart::Controller::print(char* text)
{
    int l = strlen(text) + 1;
    this->sendPacket(1, l, (uint8_t*)text);
}

void uart::Controller::printf(char* format, ...)
{
    char buf[256];
    va_list args;
    va_start (args, format);
    int l = vsprintf(buf, format ,args) + 1;
    va_end(args);
    this->sendPacket(1, l, (uint8_t*)buf);
}

bool uart::Controller::sendPacket(uint16_t type, uint8_t length, const uint8_t* data)
{
    if (txQueue_.available() < length + 5) return false;
    txQueue_.push(HEADER_INDICATOR);
    txQueue_.push(length);
    txQueue_.push((type >> 8) & 0xFF);
    txQueue_.push(type & 0xFF);

    for (int i =0;i < length;i++)
    {
        txQueue_.push(data[i]);
    }
    txQueue_.push(FOOTER_INDICATOR);

    if (!sending_)
    {
        M_EVENT_POST(uart::Controller,send);
        sending_ = true;
    }
    return true;
}
void uart::Controller::registerCommand(uint16_t type, Handler handler)
{
    Command* cmd = new Command();
    cmd->type = type;
    cmd->handler = handler;
    cmd->next = commands_;
    commands_ = cmd;
}
