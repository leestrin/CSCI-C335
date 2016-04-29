/*********************************
 * f3d_user_btn.c
 *
 * driver for button
 * initialize and read from button
 *
 * Author: Simon Lee (sijlee), Ethan Lawton (elawton2)
 * Date Created: 02/05/2016
 * Last Modified by: Simon Lee (sijlee)
 * Date Last Modified: 02/10/2016
 * Assignment: Lab 4
 * Part of: C335
 */

/**********************************
 *f3d_user_btn.c 
 *contains the init and read functions for the User Button
 *********************************/
#include <stm32f30x.h>
#include <stm32f30x_gpio.h>
#include <stm32f30x_rcc.h>


/*Initialization of the UserButton*/
void f3d_user_btn_init(void){
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

/*reads the User Button*/
int user_btn_read(void){
  //read from pin 0
  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0);
  
}
