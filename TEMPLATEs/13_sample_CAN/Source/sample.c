/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            CAN Bus-support splatter-mirror visual effect example (works also in loopback)
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2010-11-7
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             Paolo Bernardi
** Modified date:           02/01/2024
** Version:                 v2.0
** Descriptions:            basic program for CAN communication (works in loopback + 2 boards crossing CAN Channels)
**
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "LPC17xx.h"
#include "GLCD/GLCD.h" 
#include "TouchPanel/TouchPanel.h"
#include "timer/timer.h"
#include "CAN/CAN.h"


#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif


int main(void)
{
  SystemInit();  												/* System Initialization (i.e., PLL)  */
	CAN_Init();
  LCD_Initialization();
	
  
	TP_Init();
	TouchPanel_Calibrate();
	
	LCD_Clear_HH(Black,Blue);
	GUI_Text(0, 10, (uint8_t *)  " CAN1 --> CAN 2 ", Red, Black);			
	GUI_Text(0, 160, (uint8_t *) " CAN2 --> CAN 1 ", Red, White);			
	GUI_Text(5, 280, (uint8_t *) " touch here : 1 sec to clear ", Black, Red);
	
	init_timer(0, 0x4E2 ); 						    /* 500us * 25MHz = 1.25*10^3 = 0x4E2 */ //TBV
	enable_timer(0);
	
	LPC_SC->PCON |= 0x1;									/* power-down	mode										*/
	LPC_SC->PCON &= ~(0x2);						
	
  while (1)	
  {
		__ASM("wfi");
  }
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
