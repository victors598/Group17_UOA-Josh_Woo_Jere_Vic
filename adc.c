/*
 * adc.c
 *
 * Created: 20/09/2018 12:00:40 PM
 *  Author: vsta598
 */ 

#include "adc.h"

//This is a function that will initialize the ADC peripheral to our desired settings.
//
//ADC settings => Vref = 5V, ADC reads from  channel ADC0, turns ON the ADC, sets prescaler to x64
//                , enables auto triggering, sets trigger source to free running mode
//				and starts the first conversion.
void ADC_init(){
	//Questions for Travis: Should I set up the DDR stuff as all outputs and then set the necessary input pins as input?
	//						Does that mean I don't have to set up TXEN0, it will be labeled as an output when I make DDR stuff outputs?
	//						Does setting stuff to outputs make it reduce power?
	// input = high impedance, won't short and break the microcontrollers
	//						Can't turn off ADC7D any other way to access this register?
	//						Set PE3(ADC7/PTCY/T3/MOSI1) to 1, i.e. keep it high to prevent it floating, therefore reducing power consumption?
	
	//Enable ADC, enable auto-trigger, prescaler select, first conversion.
	ADCSRA |= ((1 << ADEN) | (1 << ADSC) | (1 << ADATE) | (1 << ADPS2) | (1 << ADPS1));
	ADMUX |= (1 << REFS0); //5V reference.
	DIDR0 |= ((1 << ADC2D) | (1 << ADC3D) | (1 << ADC5D)); //Disable some ADC pin to reduce power consumption.
	
}

// This is a function that will get a reading from the ADC whilst it is operating in free running mode
//Reading ADCL blocks ADC from outputting to the data register. Reading ADCH re-enables access for the ADC.
uint16_t getReading (){
	uint16_t result;
	
	while(CONVERSION_IN_PROGRESS){
		//Do nothing.
	}
	
	result = ADCL; //ADCL must be read first. Otherwise next conversion will be ignored, as data register is blocked.
	result |= ADCH;
	
	return result;
	
}

//After an external interrupt has occurred this function will be called. It will read from the ADC data register
//after each conversion has occurred and will store the result in an array that is passed into the function.
//The function will keep sampling until the array is full. 
uint8_t sampleWaveform(uint16_t samplingArr[][]){
	uint8_t count = 0;
	
	while(count < MAX_NUM_OF_SAMPLES){
		samplingArr[FIRST_ROW][count] = getReading();
		count++;
		
	}
	
	return 1; //sets sample conditional block to be skipped  
	
}

//This function will take a 16 bit ADC value that was read from the ADC data register and will convert it into 
//a 16-bit integer that will represent the true voltage value.
// This function doesn't return a floating point value, as we have deemed processing a floating point value
//is too instruction heavy for the CPU.
uint16_t convertADC(uint16_t adcVal){
	adcVal = (((uint32_t)adcVal*5000)/MAX_ADC_BITS);
	
	return adcVal;
	
}


//Function removes the DC gain and offset value from our outputs. Voltage signal conditioning has unity gain, 
//whilst current has a DC gain of 3. Both have a DC offset of 1.75V.
uint16_t removeOffsetAndGain(uint16_t output, char parameter){
	if(parameter == 'i'){ //Current
		output -= DC_OFFSET; 
		output /= CURRENT_GAIN;
		 
		
	} else { //Voltage
		output -= DC_OFFSET;
		
	}
	
	return output;
}

//This function converts the voltage sensed by the analog circuitry into either the load voltage or current values.
uint16_t getTrueValues(uint16_t sensed, char parameter){
	if(parameter == 'i'){ //Current
		return (sensed/SHUNT_RESISTOR);
		
	} else { //Voltage
		return (((uint32_t)sensed*(RESISTOR_A + RESISTOR_B))/RESISTOR_B); //NEED TO UPCAST HERE?????
		
	}
	
}

//~~~~~~~~~~~~~~~~~~~QUESTIONS: What is more efficient: updating a value by having the function return a value, or update the value by
//							    passing in a pointer that will then get updated as the value is processed?
//https://www.quora.com/Is-it-better-to-return-value-from-a-function-or-pass-in-a-pointer-in-C
