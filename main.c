#include "stm32f4xx.h"                  // Device header
static void wait(){
	volatile int i;
	for(i=0;i<1000000;i++);
}

int main(){
	volatile int led;
	led = 12;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN | RCC_AHB1ENR_GPIOAEN;
	GPIOD->MODER |= GPIO_MODER_MODER12_0 | GPIO_MODER_MODER13_0 | GPIO_MODER_MODER14_0 | GPIO_MODER_MODER15_0;
	GPIOA->MODER &= ~GPIO_MODER_MODER0;
	while(1){
		if(GPIOA->IDR & GPIO_IDR_ID0){
			GPIOD->ODR |= 1U << led;
			wait();
			GPIOD->ODR &= ~(1U<< led);
			led++;
			if(led > 15){
				led = 12;
			}
		}
	}
}
