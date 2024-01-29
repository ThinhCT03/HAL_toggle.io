
#include "main.h" 
#include "stm32f10x.h"    


/**
  * @brief  	Main program.
  * @param  	None
  * @retval 	None
 
  
/*----------------------------------------------------------------------------
					MAIN Function
 *----------------------------------------------------------------------------*/

void delay_ms(uint32_t ms);


int main(void) {
    // B?t clock cho GPIOC
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;

    // C?u hình chân 13 c?a GPIOC là output
    GPIOC->CRH &= ~GPIO_CRH_CNF13;  // Clear CNF bits
    GPIOC->CRH |= GPIO_CRH_MODE13;  // Output mode, max speed 2 MHz

    // Kh?i t?o Systick timer v?i chu k? là 1ms
    if (SysTick_Config(SystemCoreClock / 1000)) {
        while (1);  // X?y ra l?i n?u không th? kh?i t?o Systick
    }

    while (1) {
        // Th?c hi?n vi?c d?o bit trên chân 13 c?a GPIOC
        GPIOC->ODR ^= GPIO_ODR_ODR13;

        // Ch? 1 giây (1000ms)
        delay_ms(1000);
    }
}
void delay_ms(uint32_t ms) {
    // Ch? theo th?i gian ms s? d?ng Systick
    uint32_t ticks =(SystemCoreClock / 1000);
    SysTick->LOAD = ticks - 1;
    SysTick->VAL = 0;
		SysTick->CTRL = 0x5;
    while (ms)
  {
    if ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) != 0)
    {
      ms--;
    }
}
	SysTick->CTRL = 0;
	}
