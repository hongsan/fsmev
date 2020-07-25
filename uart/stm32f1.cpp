#include "stm32f1.h"
#include "stm32f1xx.h"
#include "core/engine.h"
#include "controller.h"

extern "C" void USART1_IRQHandler(void)
{
    if(USART1->SR & USART_SR_RXNE)
    {
        USART1->SR &= ~USART_SR_RXNE;
        uart::Controller::instance().nextReceiveEvent();
    }
//    else if(USART1->SR & USART_SR_TC)
//    {
//        USART1->SR &= ~USART_SR_TC;
//        M_EVENT_POST(uart::Controller, send);
//    }
}

void uart::Controller::initUART_()
{
    // GPIOB Periph clock enable
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;


    //USART1 GPIO Configuration
    //PB6      ------> USART1_TX
    //PB7      ------> USART1_RX

    // Set alternate
    AFIO->MAPR |= AFIO_MAPR_USART1_REMAP;       // remap usart to PB6, PB7
    AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_JTAGDISABLE;//010: JTAG-DP Disabled and SW-DP Enabled

    GPIOB->CRL &= ~(GPIO_CRL_CNF6_Msk);         // clear
    GPIOB->CRL |= (GPIO_CRL_CNF6_1);            // 10: Alternate function output Push-pull
    GPIOB->CRL |= (GPIO_CRL_MODE6_Msk);         // 11:output max speed(Tx)

    GPIOB->CRL &= ~GPIO_CRL_MODE7_Msk;          // 00: Input mode (Rx)
    GPIOB->CRL |= GPIO_CRL_CNF7_0;              // 01: Floating input

    // USART1 clock enable
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

    // 115200 Bd @ 48 MHz
    // USARTDIV = 48 MHz / 115200 = 416 = 0x01A0
    // BRR[15:4] = USARTDIV[15:4]
    // When OVER8 = 0, BRR [3:0] = USARTDIV [3:0]
    // USART1->BRR = (uint16_t)(0x01A0);

    //USART1->BRR = (uint16_t)(0x0270);//72 115200
    //USART1->BRR = (uint16_t)(0x1D4C);//72 9600
    //USART1->BRR = (uint16_t)(0x0230);//64 115200
    //USART1->BRR = (uint16_t)(0x1380);//48 9600
    //USART1->BRR = (uint16_t)(0x340);//8 9600
    //USART1->BRR = (uint16_t)(0x680);//16 9600
    //USART1->BRR = (uint16_t)(0x787);//36 115200
    //USART1->BRR = (uint16_t)(0xEA0);//36 9600
    //USART1->BRR = (uint16_t)(0x1380);//48 9600
    USART1->BRR = (uint16_t)(0x01A0);//48 115200

    // USART enable
    // Receiver enable
    // Transmitter enable
    USART1->CR1 = (uint32_t)(USART_CR1_UE | USART_CR1_RE | USART_CR1_TE);
    USART1->CR1 |= USART_CR1_RXNEIE;
    //USART1->CR1 |= USART_CR1_TCIE; //Transmission Complete Interrupt

    // Default value
    USART1->CR2 = (uint32_t)(0x00000000);
    USART1->CR3 = (uint32_t)(0x00000000);

    NVIC_EnableIRQ(USART1_IRQn);
}
