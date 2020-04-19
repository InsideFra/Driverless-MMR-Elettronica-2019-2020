/*
 * MCP3208.h
 *
 *  Created on: 18 apr 2020
 *      Author: franc
 */

#ifndef SRC_MCP3208_H_
#define SRC_MCP3208_H_

#include "stm32f4xx_hal.h"

enum Channel {
    SINGLE_0 = 0b1000,  /**< single channel 0 */
    SINGLE_1 = 0b1001,  /**< single channel 1 */
    SINGLE_2 = 0b1010,  /**< single channel 2 */
    SINGLE_3 = 0b1011,  /**< single channel 3 */
    SINGLE_4 = 0b1100,  /**< single channel 4 */
    SINGLE_5 = 0b1101,  /**< single channel 5 */
    SINGLE_6 = 0b1110,  /**< single channel 6 */
    SINGLE_7 = 0b1111,  /**< single channel 7 */
    DIFF_0PN = 0b0000,  /**< differential channel 0 (input 0+,1-) */
    DIFF_0NP = 0b0001,  /**< differential channel 0 (input 0-,1+) */
    DIFF_1PN = 0b0010,  /**< differential channel 1 (input 2+,3-) */
    DIFF_1NP = 0b0011,  /**< differential channel 1 (input 2-,3+) */
    DIFF_2PN = 0b0100,  /**< differential channel 2 (input 4+,5-) */
    DIFF_2NP = 0b0101,  /**< differential channel 2 (input 5-,5+) */
    DIFF_3PN = 0b0110,  /**< differential channel 3 (input 6+,7-) */
    DIFF_3NP = 0b0111   /**< differential channel 3 (input 6-,7+) */
};

class MCP3208 {

public:

	/** ADC resolution in bits. */
	static const uint8_t kResBits = 12;
	/** ADC resolution. */
	static const uint16_t kRes = (1 << kResBits);


	/**
	* Initiates a MCP320x object. The chip select pin must be already
	* configured as output.
	* @param [in] vref ADC reference voltage in mV.
	* @param [in] csPin pin number to use for chip select.
	* @param [in] spi reference to the SPI interface to use.
	*/
	MCP3208(uint16_t vref, GPIO_TypeDef* csPort, uint16_t csPin, SPI_HandleTypeDef *hspi);
	~MCP3208();
	/**
	* Reads the supplied channel. The SPI interface must be initialized and
	* put in a usable state before calling this function.
	* @param [in] ch defines the channel to read from.
	* @return the converted raw value.
	*/
	uint16_t read(Channel ch);

	uint16_t createCmd(Channel ch);

	/**
	* Executes the supplied command.
	* @param [in] cmd the command to execute.
	* @return the ADC value from the SPI response.
	*/
	uint16_t execute(uint16_t cmd) const;

private:
	uint8_t spiWorking;

	uint16_t pcsPin;
	GPIO_TypeDef* pcsPort;
	SPI_HandleTypeDef* mSpi;

	/**
	* Defines 16 bit SPI data. The structure implements an easy
	* access to each byte.
	*/
	union SpiData { // VERIFICA : Potrebbe non funzionare
		uint16_t value;  /**< value */
		struct {
		  uint8_t loByte;  /**< low byte */
		  uint8_t hiByte;  /**< high byte */
		};
	};

	/**
	* Transfers without SPI command data.
	* @return the ADC value from the SPI response.
	*/
	uint16_t transfer() const;

	/**
	* Transfers the supplied SPI command data.
	* @param [in] cmd the SPI command data to transfer.
	* @return the ADC value from the SPI response.
	*/
	uint16_t transfer(uint16_t cmd) const;

};

#endif /* SRC_MCP3208_H_ */
