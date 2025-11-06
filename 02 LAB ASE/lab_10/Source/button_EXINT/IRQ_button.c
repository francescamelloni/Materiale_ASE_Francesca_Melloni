#include "button.h"
#include "LPC17xx.h"

//	#include "../led/led.h" 					/* do not needed anymore, make your project clean */
#include "../RIT/RIT.h"		  			/* you now need RIT library 			 */

extern int down_0;
extern int down_1;
extern int down_2;

extern int array[];
int i,j,temp,sum=0;
double avg;

void EINT0_IRQHandler (void)	  	/* INT0														 */
{		
	down_0 = 1;
	NVIC_DisableIRQ(EINT0_IRQn);		/* disable Button interrupts			 */
	LPC_PINCON->PINSEL4    &= ~(1 << 20);     /* GPIO pin selection */
	LPC_SC->EXTINT &= (1 << 0);     /* clear pending interrupt         */
}


void EINT1_IRQHandler (void)	  	/* KEY1														 */
{
	down_1 = 1;
	NVIC_DisableIRQ(EINT1_IRQn);		/* disable Button interrupts			 */
	LPC_PINCON->PINSEL4    &= ~(1 << 22);     /* GPIO pin selection */
	
	disable_timer(1);
	for (j=0; j<7000;j++){
		for (i=0; i<7000;i++){
			if (array[i]>array[i+1]){
					temp=array[i];
					array[i]=array[i+1];
				  array[i+1]=temp;
			}
		}
	}
	
	for (j=0;j<7000;j++){
		sum += array[j];
		array[j] = 0xCAFECAFE;
	}
	
	avg = sum/7000;	
	
	
	LPC_SC->EXTINT &= (1 << 1);     /* clear pending interrupt         */
}

void EINT2_IRQHandler (void)	  	/* KEY2														 */
{
	down_2 = 1;
	NVIC_DisableIRQ(EINT2_IRQn);		/* disable Button interrupts			 */	
	LPC_PINCON->PINSEL4    &= ~(1 << 24);     /* GPIO pin selection */
  LPC_SC->EXTINT &= (1 << 2);     /* clear pending interrupt         */    
}


