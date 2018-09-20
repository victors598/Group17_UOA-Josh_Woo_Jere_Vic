/*
 * interrupt.c
 *
 * Created: 20/09/2018 12:01:41 PM
 *  Author: vsta598
 */ 

#include "interrupt.h"


/*This is a function that will set up the micro controller to call External Interrupt 0
when a rising edge is detected on Pin 32 (INT0).
*/
void enable_ext_interrupt(){
	EICRA |= ((1 << ISC01) | (1 << ISC00)); //Detect on Rising edge.
	EIMSK |= (1 << INT0); //Rising edge detected on pin 32.
	
}

//This function disables interrupt requests being sent if an interrupt event is detected on Pin 32 (INT0).
void disable_ext_interrupt(){
	EIMSK &= ~(1 << INT0);
	
}

//This is a function that is called when a rising edge is produced from the comparator in our circuitry.
//Starts the first conversion (set ADSC). Allowing free running mode to start.
ISR(INT0_vect){
	sampling = 1;
	skip = 0;
	
}
