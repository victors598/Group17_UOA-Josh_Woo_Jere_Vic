/*
 * adc.h
 *
 * Created: 20/09/2018 12:00:21 PM
 *  Author: vsta598
 */ 

#include <avr/io.h>

#ifndef ADC_H_
#define ADC_H_

#define CONVERSION_IN_PROGRESS (ADCSRA&(1<<ADSC)) //Checks if an ADC conversion is in progress.
#define MAX_ADC_BITS 1024
#define CYCLES_SAMPLED 7
#define SAMPLES_PER_CYCLE 19
#define MAX_NUM_OF_SAMPLES ((CYCLES_SAMPLED)*(SAMPLES_PER_CYCLE))
#define DC_OFFSET 1750
#define CURRENT_GAIN 3000 //subject to change~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define SHUNT_RESISTOR 687 //subject to change~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define RESISTOR_A 82000000 //Might overflow~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define RESISTOR_B 5600000 //Might overflow?????~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


void ADC_init();
uint16_t getReading ();
uint8_t sampleWaveform();
uint16_t convertADC(uint16_t adcVal);
uint16_t removeOffsetAndGain(uint16_t voltage, char sensed);
uint16_t getTrueValues(uint16_t sensed, char parameter);


#endif /* ADC_H_ */