/*********************************
 * f3d_led.c
 *
 * led driver for STM32
 * initializes leds(GPIO pins), turns on and off leds  
 *
 * Author: Simon Lee (sijlee), Ethan Lawton (elawton2)
 * Date Created: 02/05/2016
 * Last Modified by: Simon Lee (sijlee)
 * Date Last Modified: 02/10/2016
 * Assignment: Lab 4
 * Part of: C335
 */

/************************
 *f3d_led.c - contains intializations/functions for the leds
 ************************/

#include <stm32f30x.h>
#include <stm32f30x_gpio.h>
#include <stm32f30x_rcc.h>
#include <f3d_led.h>


//intializes the port and pins for the leds on the board
void f3d_led_init(void) {
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All; 
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; 


}
/*Turns on the appropriate led as specified by the parameter.*/
void f3d_led_on(int led) {
  //from input, we select leds by pin
  switch(led)
    {
      //since there are 8 leds, we accept from 0 to 7
      //for each led number, turn on GPIO pin
    case 7:
      GPIOE->BSRR=GPIO_Pin_15;
      break;
    case 6:
      GPIOE->BSRR=GPIO_Pin_14;
      break;
    case 5:
      GPIOE->BSRR=GPIO_Pin_13;
      break;
    case 4:
      GPIOE->BSRR=GPIO_Pin_12;
      break;
    case 3:
      GPIOE->BSRR=GPIO_Pin_11;
      break;
    case 2:
      GPIOE->BSRR=GPIO_Pin_10;
      break;
    case 1:
      GPIOE->BSRR=GPIO_Pin_9;
      break;
    case 0:
      GPIOE->BSRR=GPIO_Pin_8;
      break;
      
    }
}

/*Turns off the approiate led as specified by the parameter*/ 
void f3d_led_off(int led) {
  
  switch(led)
    {
    case 7:
      GPIOE->BRR=GPIO_Pin_15;
      break;
    case 6:
      GPIOE->BRR=GPIO_Pin_14;
      break;
    case 5:
      GPIOE->BRR=GPIO_Pin_13;
      break;
    case 4:
      GPIOE->BRR=GPIO_Pin_12;
      break;
    case 3:
      GPIOE->BRR=GPIO_Pin_11;
      break;
    case 2:
      GPIOE->BRR=GPIO_Pin_10;
      break;
    case 1:
      GPIOE->BRR=GPIO_Pin_9;
      break;
    case 0:
      GPIOE->BRR=GPIO_Pin_8;
      break;
      
    }
} 

/*Turns on all LEDs*/
void f3d_led_all_on(void) {
  /*YOUR CODE HERE*/
  GPIOE->BSRR=GPIO_Pin_8;
  GPIOE->BSRR=GPIO_Pin_9;
  GPIOE->BSRR=GPIO_Pin_10;
  GPIOE->BSRR=GPIO_Pin_11;
  GPIOE->BSRR=GPIO_Pin_12;
  GPIOE->BSRR=GPIO_Pin_13;
  GPIOE->BSRR=GPIO_Pin_14;
  GPIOE->BSRR=GPIO_Pin_15; 
} 

/*Turns off all LEDs*/
void f3d_led_all_off(void) {
  /*YOUR CODE HERE*/
  GPIOE->BRR=GPIO_Pin_8;
  GPIOE->BRR=GPIO_Pin_9;
  GPIOE->BRR=GPIO_Pin_10;
  GPIOE->BRR=GPIO_Pin_11;
  GPIOE->BRR=GPIO_Pin_12;
  GPIOE->BRR=GPIO_Pin_13;
  GPIOE->BRR=GPIO_Pin_14;
  GPIOE->BRR=GPIO_Pin_15;
} 

/* led.c ends here */

