#ifndef CONSOLE_CONTROLLER_H_
#define CONSOLE_CONTROLLER_H_

#include "core/queue.h"
#include "core/engine.h"
#include "uart/controller.h"
#include "uart/command.h"
#include "model.h"

COMPONENT(console, Controller)
    U_COMMAND(getItem);
    U_COMMAND(getPlot);
    U_COMMAND(getChart);
public:
    void init();
    void plot(uint8_t channel, int16_t value);
    void plotFlush();
    void updateVariable(uint16_t type, int32_t value);

    void addSection(char* name);
    void addVariable(uint16_t command, char* name, int32_t min, int32_t max, uart::Handler handler);
    void addAction(uint16_t type, char* name, uart::Handler handler);

    void setupChart(uint16_t xCount, uint32_t yMin, uint32_t yMax);
    void addPlot(uint8_t channel, char* name, uint32_t offset, bool zeroXVisible);
private:
    void addItem_(Item* item);
    Plot plots_[8];
    uint8_t plotMask_ = 0;
    Item* items_ = nullptr;
COMPONENT_END

#endif /* UART_CONTROLLER_H_ */
