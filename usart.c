/*
 * usart.c
 *
 * Created: 20/09/2018 12:01:14 PM
 *  Author: vsta598
 */ 

#include "usart.h"

//This is a function that will initialize the USART peripheral to our desired settings.
//USART settings => 8 bit data packet, no parity bit, 1 stop bit, transmitter, baud rate  = 9600.
void usart_init(uint16_t ubrr){
	UCSR0B |= (1 << TXEN0); //Enable the micro controller to transmit data.
	UBRR0 |= ubrr; //Set baud rate.
	
}

//This is a function that will be used to load data to the UDR0 register so that it can
//be transmitted via the blue tooth module.*/
void usart_transmit(uint8_t data)
{
	while(!(READY_TO_LOAD)); //Wait while UDR0 is full..
	
	UDR0 = data; //When UDR0 is empty the while loop will end and we can put new data in.
	
}

//This is a function that will be used to convert the RMS current, peak voltage and average power
//into our desired data packet format. So that it can be read by our VHDL logic.*/
void convertForTransmit(uint16_t reading, char parameter, uint8_t *output_array){
	uint8_t first_2_digits;
	
	output_array[0] = reading/100; //stores the leftmost decimal point
	output_array[0] += BCD_1; //adds to the data packet which BCD segment will display this value.
	
	output_array[1] = (reading%100)/10; //stores the middle decimal point
	output_array[1] += BCD_2;
	
	output_array[2] = (reading%100)%10; //stores the rightmost decimal point
	output_array[2] += BCD_3;
	
	//Conditionals that figures out what parameter the data packet will hold.
	if(parameter  == 'v'){
		first_2_digits = VOLTAGE;
		
		} else if(parameter == 'i'){
		first_2_digits = CURRENT;
		
		} else if(parameter == 'p') {
		first_2_digits = POWER;
		
	}
	
	//For loop that adds the parameter to the data packet.
	for(uint8_t i = 0; i < 4; i++){
		output_array[i] += first_2_digits;
		
	}
	
	
}

//Function that transmits the individual digits for the RMS current, peak voltage, and average power.
void sendToCPLD(uint8_t *ptrArray[]){
	uint8_t *arrayPTR;
		
	for(uint8_t i = 0; i < 3; i++){
		arrayPTR = ptrArray[i]; //Pointer that will point to a specific array.
		
		for(uint8_t j = 0; j < 4; j++){
			usart_transmit(*arrayPTR);
			arrayPTR++;
			
		}
		
	}

}