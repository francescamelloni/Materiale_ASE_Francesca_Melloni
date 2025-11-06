#include "button.h"
#include "lpc17xx.h"

#include "../led/led.h"

unsigned char next_state(unsigned char current_state, unsigned char taps, int *output_bit);
unsigned char current_state = 0xAA; 
unsigned char initial_state = 0xAA;
int count = 0;
unsigned char taps = 0x27; 
int output_bit = 0;

void EINT0_IRQHandler (void)	  /* TERZO PULSANTE */
{
  LPC_SC->EXTINT &= (1 << 0);     /* clear pending interrupt         */
}

void EINT1_IRQHandler (void)	  /* PRIMO PULSANTE */
{
	current_state = next_state(current_state, taps, &output_bit);
	
	LED_Out(current_state); /* funzione che accende i led in base al numero binario passato */

	LPC_SC->EXTINT &= (1 << 1);     /* clear pending interrupt         */
}

void EINT2_IRQHandler (void)	   /* SECONDO PULSANTE */
{
	do{
		current_state = next_state(current_state, taps, &output_bit);
		count++;
	}while (current_state != initial_state);
	
	LED_Out(count);
	
  LPC_SC->EXTINT &= (1 << 2);     /* clear pending interrupt         */  
}