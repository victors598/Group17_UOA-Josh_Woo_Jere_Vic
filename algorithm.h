/*
 * algorithm.h
 *
 * Created: 20/09/2018 8:07:37 PM
 *  Author: vsta598
 */ 

#include "adc.h"

#ifndef ALGORITHM_H_
#define ALGORITHM_H_

void removeIdenticalPts(uint16_t array[]);
void sortArray();
uint16_t calculatePowerAvg();
uint16_t calculateCurrentRMS();
uint16_t calculateVoltagePeak();



#endif /* ALGORITHM_H_ */