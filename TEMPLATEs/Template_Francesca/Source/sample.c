/*----------------------------------------------------------------------------
 * Name:    sample.c
 * Purpose: to control led through EINT buttons and manage the bouncing effect
 *        	- key1 switches on the led at the left of the current led on, 
 *					- it implements a circular led effect. 	
  * Note(s): this version supports the LANDTIGER Emulator
 * Author: 	Paolo BERNARDI - PoliTO - last modified 15/12/2020
 *----------------------------------------------------------------------------
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2017 Politecnico di Torino. All rights reserved.
 *----------------------------------------------------------------------------*/
                  
#include <stdio.h>
#include "LPC17xx.h"                    /* LPC17xx definitions                */
#include "led/led.h"
#include "button_EXINT/button.h"
#include "joystick/joystick.h"
#include "timer/timer.h"
#include "RIT/RIT.h"
#include "./adc/adc.h"
#include "GLCD/GLCD.h" 
#include "TouchPanel/TouchPanel.h"

#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif


/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/
int main (void) {
  	
	SystemInit();  												/* System Initialization (i.e., PLL)  */
  LED_init();                           /* LED Initialization                 */
  BUTTON_init();												/* BUTTON Initialization              */
	init_RIT(0x004C4B40);									/* RIT Initialization 50 msec       */
	enable_RIT();													/* enable RIT to count 50ms				 */
	joystick_init();
	ADC_init();		
	
/*-----------DISPLAY e LED (stessi pin)-------------*/
/*Per disattivare i led premere il jumper verde di sotto*/
	
/*  LCD_Initialization();
	TP_Init();
	TouchPanel_Calibrate();
	LCD_Clear(Black);
	GUI_Text(0, 280, (uint8_t *) " touch here : 1 sec to clear  ", Red, White);
	//LCD_DrawLine(0, 0, 200, 200, White);
*/
	
	LPC_SC->PCON |= 0x1;									/* power-down	mode										*/
	LPC_SC->PCON &= ~(0x2);						
		
	//enable_timer(0);
	
  while (1) {                           /* Loop forever                       */	
		__ASM("wfi");
  }

}
