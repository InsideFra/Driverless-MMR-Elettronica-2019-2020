/*
 * NTCM12.cpp
 *
 *  Created on: 16 apr 2020
 *      Author: franc
 */

#include "NTCM12.h"

#define S 17
#define Va 5
#define R1 1000
structDataSens Calibrazione[S] = {
		// Resistenza	//Temperatura
		{45313, 		-40},
		{26114,			-30},
		{15462			-20},
		{9397,			-10},
		{5896,			0},
		{3792, 			10},
		{2500,			20},
		{1707,			30},
		{1175, 			40},
		{834,			50},
		{596,			60},
		{436,			70},
		{323,			80},
		{243,			90},
		{187,			100},
		{144,			110},
		{113,			120}
};

NTCM12::NTCM12() {
	// TODO Auto-generated constructor stub

}

int8_t NTCM12::TempDaResistenza(float Resistenza) {
	float differenzaMinore = 10000;
	float diff = 0;
	for(uint8_t i = 0; i < S; i++) {
		diff = Calibrazione[i].Resistenza - Resistenza;
		if(diff < 0) { // funzione assoluto molto becera
			diff = diff*(-1);
		}
		if(diff < differenzaMinore) {
			differenzaMinore = diff;
			if(i == S-1) {
				return Calibrazione[i].Temperatura;
			}
			continue;
		}
		else { // valore precedente è quello più vicino
			return Calibrazione[i-1].Temperatura;
		}
	}
	return 0;
}

int8_t NTCM12::TempDaVoltaggio(uint16_t Vb) {
	float resistenza = 0;
	resistenza = Vb*R1/(Va-Vb); // questo è da progetto elettronico, può essere rivisto
	if(resistenza != 0) {
		int8_t Temp = NTCM12::TempDaResistenza(resistenza);
		return Temp;
	}
	return 0;
}


