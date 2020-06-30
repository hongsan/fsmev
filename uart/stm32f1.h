#ifndef UART_STM32F1_H
#define UART_STM32F1_H

#define UART_TX_READY   (USART1->SR & USART_SR_TXE)
#define UART_RX_READY   (USART1->SR & USART_SR_RXNE)
#define UART_READ       (uint8_t)USART1->DR
#define UART_WRITE(c)   USART1->DR = c

#endif // STM32F1_H
