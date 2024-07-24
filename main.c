#include "stm32f4xx.h"                  // Device header
static void wait(){
	volatile int i;
	for(i=0;i<1000000;i++);
}

int main(){
	volatile int led;
	led = 12;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN | RCC_AHB1ENR_GPIOAEN; // Activate D and A ports clock signal
	GPIOD->MODER |= GPIO_MODER_MODER12_0 | GPIO_MODER_MODER13_0 | GPIO_MODER_MODER14_0 | GPIO_MODER_MODER15_0; // Set pin 12, 13, 14 and 15 of D port to digital output mode
	GPIOA->MODER &= ~GPIO_MODER_MODER0; // Set pin 0 of A port to digital input mode
	while(1){
		if(GPIOA->IDR & GPIO_IDR_ID0){ // If button clicked
			GPIOD->ODR |= 1U << led; // Light on the current LED
			wait(); // wait
			GPIOD->ODR &= ~(1U<< led); // Light off the current LED
			led++; // Next LED
			if(led > 15){ // If out of range
				led = 12; // Set first LED
			}
		}
	}
}
