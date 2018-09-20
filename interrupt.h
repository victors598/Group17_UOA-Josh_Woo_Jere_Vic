/*
 * interrupt.h
 *
 * Created: 20/09/2018 12:01:28 PM
 *  Author: vsta598
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

//GET THESE CHECKED BY TRAVIS!!!!!!!!!!! //GET THESE CHECKED BY TRAVIS!!!!!!!!!!!
//GET THESE CHECKED BY TRAVIS!!!!!!!!!!! extern volatile uint8_t sampling; //GET THESE CHECKED BY TRAVIS!!!!!!!!!!!
//GET THESE CHECKED BY TRAVIS!!!!!!!!!!! extern volatile uint8_t skip; //GET THESE CHECKED BY TRAVIS!!!!!!!!!!!
//GET THESE CHECKED BY TRAVIS!!!!!!!!!!! //GET THESE CHECKED BY TRAVIS!!!!!!!!!!!

#ifndef INTERRUPT_H_
#define INTERRUPT_H_

void enable_ext_interrupt();
void disable_ext_interrupt();
ISR(INT0_vect);


#endif /* INTERRUPT_H_ */