/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

#include "LPC17xx.h"
#include "RIT.h"
#include "../led/led.h"

volatile int down_0 = 0;
volatile int down_1 = 0;
volatile int down_2 = 0;
int to_release_down0=0;
int to_release_down1=0;
int to_release_down2=0;



void RIT_IRQHandler (void)
{			
static int joy_sel=0;
static int joy_down=0;
static int joy_up=0;
static int joy_left=0;
static int joy_right=0;
	
	

/*************************BUTTONS***************************/
/*------------------------INT0------------------------*/
if(down_0 !=0){
	down_0++;
	if((LPC_GPIO2->FIOPIN & (1<<10)) == 0){
		switch(down_0){
			case 2:
				//my code
				to_release_down0=1;
				break;
			default:
				break;
		}
	}
	else {	/* button released */
		if(to_release_down0){
			//code here
			to_release_down0=0;
		}
		down_0=0;			
		NVIC_EnableIRQ(EINT0_IRQn);							 /* disable Button interrupts			*/
		LPC_PINCON->PINSEL4    |= (1 << 20);     /* External interrupt 0 pin selection */
	} 
}// end INT0



/*------------------------KEY1------------------------*/
if(down_1 !=0){
	down_1++;
	if((LPC_GPIO2->FIOPIN & (1<<11)) == 0){
		switch(down_1){
			case 2:
				// my code
				to_release_down1=1;
				break;
			default:
				break;
		}
	}

	else {	/* button released */
		if(to_release_down1){
			//code here
			to_release_down1=0;
		}
		
		
		down_1=0;			
		NVIC_EnableIRQ(EINT1_IRQn);							 /* disable Button interrupts			*/
		LPC_PINCON->PINSEL4    |= (1 << 22);     /* External interrupt 0 pin selection */
	}
} 
	



/*------------------------KEY2------------------------*/
if(down_2 !=0){
	down_2++;
	if((LPC_GPIO2->FIOPIN & (1<<12)) == 0){
		switch(down_2){
			case 2:
				//my code
				to_release_down2=1;
				break;
			default:
				break;
		}
	}
	else {	/* button released */
		if(to_release_down2){
			//code here
			to_release_down2=0;
		}
		down_2=0;		
		NVIC_EnableIRQ(EINT2_IRQn);							 /* disable Button interrupts			*/
		LPC_PINCON->PINSEL4    |= (1 << 24);     /* External interrupt 0 pin selection */
	}
} // end KEY2
	





/*************************JOYSTICK***************************/
	/*------------------------SEL------------------------*/
	if((LPC_GPIO1->FIOPIN & (1<<25)) == 0){
		joy_sel++;
		switch(joy_sel){
			case 1:
				//my code
				break;
			default:
				break;
		}
	}else{
		joy_sel=0;
	}
	
	/*------------------------DOWN------------------------*/
	if((LPC_GPIO1->FIOPIN & (1<<26)) == 0){
		joy_down++;
		switch(joy_down){
			case 1:
				
				break;
			default:
				break;
		}
	}else{
		joy_down=0;
	}

	/*------------------------LEFT------------------------*/
	if((LPC_GPIO1->FIOPIN & (1<<27)) == 0){
		joy_left++;
		switch(joy_left){
			case 1:
				//my code
				break;
			default:
				break;
		}
	}else{
		joy_left=0;
	}

	/*------------------------RIGHT------------------------*/
	if((LPC_GPIO1->FIOPIN & (1<<28)) == 0){
		joy_right++;
		switch(joy_right){
			case 1:
				//my code
				break;
			default:
				break;
		}
	}else{
		joy_right=0;
	}
	
	/*------------------------UP------------------------*/
	if((LPC_GPIO1->FIOPIN & (1<<29)) == 0){
		joy_up++;
		switch(joy_up){
			case 1:
				//my code
				break;
			default:
				break;
		}
	}else{
		joy_up=0;
	}
	
	
  /* ADC management */
	ADC_start_conversion();		
	
	
	LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	reset_RIT();
  return;
}
	



/******************************************************************************
**                            End Of File
******************************************************************************/
