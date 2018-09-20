/*
 * usart.h
 *
 * Created: 20/09/2018 12:00:51 PM
 *  Author: vsta598
 */ 

#include <avr/io.h>

#ifndef USART_H_
#define USART_H_

#define FOSC 16000000 //Clock frequency of the micro controller
#define BAUD_RATE 9600
#define UBRR 103 //UBRR is calculated using the following equation ((FOSC/(16*(BAUD_RATE)))-1)
#define READY_TO_LOAD UCSR0A&(1<<UDRE0) //Tests if the data register empty bit is 1.
#define BCD_1 16 //Added to output packet so that VHDL logic can display the value in the correct place.
#define BCD_2 32
#define BCD_3 48
#define VOLTAGE 64 //Added to output packet so that VHDL logic can differentiate what parameter the
#define CURRENT 128 //data packet is sending.
#define POWER 192

void usart_init(uint16_t ubrr);
void usart_transmit(uint8_t data);
void convertForTransmit(uint16_t reading, char parameter, uint8_t *output_array);
void sendToCPLD(uint8_t *ptrArray[]);



#endif /* USART_H_ */