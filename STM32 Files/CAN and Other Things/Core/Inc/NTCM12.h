/*
 * NTCM12.h
 *
 *  Created on: 16 apr 2020
 *      Author: franc
 */

#ifndef SRC_NTCM12_H_
#define SRC_NTCM12_H_

#include "stm32f4xx_hal.h"

typedef struct {
	const float 	Resistenza;
	const int8_t 	Temperatura;
} structDataSens;

class NTCM12 {
public:
	NTCM12();

	int8_t TempDaResistenza(float Resistenza);
	int8_t TempDaVoltaggio(uint16_t Vb);
};

#endif /* SRC_NTCM12_H_ */
