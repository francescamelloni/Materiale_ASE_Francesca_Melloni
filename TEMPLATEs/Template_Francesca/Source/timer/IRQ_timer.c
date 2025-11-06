/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

#include "LPC17xx.h"
#include "timer.h"
#include "../led/led.h"





void TIMER0_IRQHandler (void)
{
  if(LPC_TIM0->IR & 1){	//MR0
		  //my code
			LPC_TIM0->IR = 1;	
	}else if(LPC_TIM0->IR & 2){	//MR1
			LPC_TIM0->IR = 2;
	}else if(LPC_TIM0->IR & 4){	//MR2
			LPC_TIM0->IR = 4;
	}else if(LPC_TIM0->IR & 8){	//MR3
			LPC_TIM2->IR = 8;
	}
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
  if(LPC_TIM1->IR & 1){	//MR0
			LPC_TIM1->IR = 1;	
	}else if(LPC_TIM1->IR & 2){	//MR1
			LPC_TIM1->IR = 2;
	}else if(LPC_TIM1->IR & 4){	//MR2
			LPC_TIM1->IR = 4;
	}else if(LPC_TIM1->IR & 8){	//MR3
			LPC_TIM1->IR = 8;
	}
		
  return;
}
void TIMER2_IRQHandler (void)
{
  if(LPC_TIM2->IR & 1){	//MR0
			LPC_TIM2->IR = 1;	
	}else if(LPC_TIM2->IR & 2){	//MR1
			LPC_TIM2->IR = 2;
	}else if(LPC_TIM2->IR & 4){	//MR2
			LPC_TIM2->IR = 4;
	}else if(LPC_TIM2->IR & 8){	//MR3
			LPC_TIM2->IR = 8;
	}
		
  return;
}


void TIMER3_IRQHandler (void)
{
  if(LPC_TIM3->IR & 1){	//MR0
			LPC_TIM3->IR = 1;	
	}else if(LPC_TIM3->IR & 2){	//MR1
			LPC_TIM3->IR = 2;
	}else if(LPC_TIM3->IR & 4){	//MR2
			LPC_TIM3->IR = 4;
	}else if(LPC_TIM3->IR & 8){	//MR3
			LPC_TIM3->IR = 8;
	}
		
  return;
}


/******************************************************************************
**                            End Of File
******************************************************************************/
