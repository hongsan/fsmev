#include "controller.h"

void blink::Controller::initSystem_()
{
    /*RCC->CR*/
    RCC->CR |= RCC_CR_HSEON;
    while(!(RCC->CR & RCC_CR_HSERDY)){;}// check flag HSIRDY = 1

    /* enable flash prefetch buffer */
    FLASH->ACR |= FLASH_ACR_LATENCY_1;
    FLASH->ACR |= FLASH_ACR_PRFTBE;

    RCC->CR |= RCC_CR_PLLON;
    while(!(RCC->CR & RCC_CR_PLLRDY)){;}// check flag PLLRDY = 1

    /*RCC->CFGR*/
    RCC->CR &= ~RCC_CR_PLLON;
    while(RCC->CR & RCC_CR_PLLRDY){;}// check flag PLLRDY = 0

    RCC->CFGR |= RCC_CFGR_PLLSRC;//1: Clock from PREDIV1 selected as PLL input clock
    RCC->CFGR |= RCC_CFGR_PLLMULL9;//nhan tan trong PLL
    RCC->CFGR |= RCC_CFGR_SW_PLL;// clock PLL lam dau vao cho Clock system mux
    while ((RCC->CR & RCC_CFGR_SWS_PLL)){;}
    //he so chia AHB prescaler = 0 la chia 1
    RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;//100: HCLK divided by 2

    /*ADC prescaler clock 12Mhz*/
    RCC->CFGR |= RCC_CFGR_ADCPRE_1;//10: PCLK2 divided by 6

    RCC->CR |= RCC_CR_PLLON;
    while(!(RCC->CR & RCC_CR_PLLRDY)){;}// check flag PLLRDY = 1
}

void blink::Controller::initTimer4_()
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
    TIM4->PSC = 1000;
    TIM4->ARR = 71;                 // 1Khz
    TIM4->DIER = TIM_DIER_UIE;      // Enable update interrupt (timer level)
    TIM4->CR1 = TIM_CR1_CEN;        // Enable timer
    NVIC_EnableIRQ(TIM4_IRQn);      // Enable interrupt from TIM2 (NVIC level)
}

extern "C" void TIM4_IRQHandler(void)
{
    if(TIM4->SR & TIM_SR_UIF)       // if UIF flag is set
    {
        TIM4->SR &= ~TIM_SR_UIF;    // clear UIF flag
        core::Engine::instance().tick();
    }
}

void blink::Controller::initGPIO_()
{
    /*TODO: init GPIO for LED here*/
}
