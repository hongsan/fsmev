#ifndef CORE_CONFIG_H
#define CORE_CONFIG_H

/*ifdef stm32f1*/
#include "stm32f1xx.h"
#define DISABLE_INTERRUPT   __disable_irq()
#define ENABLE_INTERRUPT    __enable_irq()
#define WAIT_FOR_INTERUPT   __WFI()

#define EVENT_QUEUE_SIZE 256
#endif // CONFIG_H
