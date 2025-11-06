/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include <string.h>
#include "LPC17xx.h"
#include "timer.h"
#include "../GLCD/GLCD.h" 
#include "../TouchPanel/TouchPanel.h"
#include "../CAN/CAN.h"

/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

void TIMER0_IRQHandler (void)
{
	static int clear = 0;
	
	static int puntiSpediti1 = 0;
	static int precX1 = -1;
	static int precY1 = -1;

	static int puntiSpediti2 = 0;	
	static int precX2 = -1;
	static int precY2 = -1;
	
  if(getDisplayPoint(&display, Read_Ads7846(), &matrix )){
		if(display.y < 280 && display.y > 140){ // BIANCO
			// send from CAN2 to CAN1
			if(display.x != precX1 || display.y != precY1){
				precX2 = display.x;
				precY2 = display.y;
				CAN_TxMsg.data[0] = ((display.x ) & 0xFF00) >> 8;
				CAN_TxMsg.data[1] = (display.x ) & 0xFF;
				CAN_TxMsg.data[2] = (display.y & 0xFF00 ) >> 8;
				CAN_TxMsg.data[3] = display.y & 0xFF;
				CAN_TxMsg.len = 4;
				CAN_TxMsg.id = 1;
				CAN_TxMsg.format = STANDARD_FORMAT;
				CAN_TxMsg.type = DATA_FRAME;
				CAN_wrMsg (2, &CAN_TxMsg);               /* transmit message */
				puntiSpediti1+=1;				
				TP_DrawPoint_Magnifier(&display);
				}

			clear = 0;
		}
		else{
			if(display.y < 140){ // NERO
				// send from CAN1 to CAN2
				if(display.x != precX2 || display.y != precY2){
					precX2 = display.x;
					precY2 = display.y;
					CAN_TxMsg.data[0] = ((display.x ) & 0xFF00) >> 8;
					CAN_TxMsg.data[1] = (display.x ) & 0xFF;
					CAN_TxMsg.data[2] = (display.y & 0xFF00 ) >> 8;
					CAN_TxMsg.data[3] = display.y & 0xFF;
					CAN_TxMsg.len = 4;
					CAN_TxMsg.id = 2;
					CAN_TxMsg.format = STANDARD_FORMAT;
					CAN_TxMsg.type = DATA_FRAME;
					CAN_wrMsg (1, &CAN_TxMsg);               /* transmit message */
					puntiSpediti2+=1;				
					TP_DrawPoint_Magnifier(&display);
					clear = 0;
				}
			}
			else{			
				if(display.y <= 0x13E){			
					clear++;
					if(clear == 200){	/* 1 seconds = 200 times * 500 us*/
						//send CAN "clear" message - to be implemented
						LCD_Clear_HH(Black, Blue);
						GUI_Text(5, 280, (uint8_t *) " touch here : 1 sec to clear ", Black, Red);	
						GUI_Text(0, 10, (uint8_t *)  " CAN1 --> CAN 2 ", Red, Black);			
						GUI_Text(0, 160, (uint8_t *) " CAN2 --> CAN 1 ", Red, White);									
					}
				}
			}
		}
	}
	else{
		//do nothing if touch returns values out of bounds
	}
  LPC_TIM0->IR = 1;			/* clear interrupt flag */
  return;
}


/******************************************************************************
** Function name:		Timer1_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER1_IRQHandler (void)
{
  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
