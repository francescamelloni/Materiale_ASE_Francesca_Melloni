/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "LPC17xx.h"
#include "timer.h"
#include "../led/led.h"

/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
extern unsigned char led_value;					/* defined in funct_led								*/
int array[7000];
int x=0;

void TIMER0_IRQHandler (void)
{
  if(LPC_TIM0->IR & 1){	//MR0
			LPC_TIM0->IR = 1;	
	}else if(LPC_TIM0->IR & 2){	//MR1
			LPC_TIM0->IR = 2;
	}else if(LPC_TIM0->IR & 4){	//MR2
			LPC_TIM0->IR = 4;
	}else if(LPC_TIM0->IR & 8){	//MR3
			LPC_TIM0->IR = 8;
	}
		
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
  if(LPC_TIM1->IR & 1){	//MR0
			LPC_TIM1->IR = 1;	
	}else if(LPC_TIM1->IR & 2){	//MR1
		  array[x] = LPC_TIM0->TC;
			x=x+1 % 7000;
			LED_Out(x);
		
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
