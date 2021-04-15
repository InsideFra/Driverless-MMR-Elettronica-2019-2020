/*
 * MCP3208.cpp
 *
 *  Created on: 18 apr 2020
 *      Author: franc
 */

#include "MCP3208.h"



MCP3208::MCP3208(uint16_t vref, GPIO_TypeDef* csPort, uint16_t csPin, SPI_HandleTypeDef *hspi) {

}

MCP3208::~MCP3208() {

}


uint16_t MCP3208::transfer() const
{
  SpiData adc;
  uint8_t pTxData;
  uint8_t pRxData;

  // activate ADC with chip select
  HAL_GPIO_WritePin(pcsPort, pcsPin, GPIO_PIN_RESET);

  // receive first(msb) 5 bits
  // ATTENZIONE: BLOCKING MODE
  pTxData = 0x00;
  HAL_SPI_TransmitReceive(mSpi, &pTxData, &pRxData, 8, 500); // TODO gestione timeout
  adc.hiByte = pRxData & 0x1F;

  // receive last(lsb) 8 bits
  // ATTENZIONE: BLOCKING MODE
  pTxData = 0x00;
  HAL_SPI_TransmitReceive(mSpi, &pTxData, &pRxData, 8, 500); // TODO gestione timeout
  adc.loByte = pRxData;

  // deactivate ADC with slave select
  HAL_GPIO_WritePin(pcsPort, pcsPin, GPIO_PIN_SET);

  // correct bit offset
  // |x|x|x|11|10|9|8|7| |6|5|4|3|2|1|0|1
  return (adc.value >> 1);
}

uint16_t MCP3208::transfer(uint16_t _cmd) const
{
  SpiData adc;
  uint8_t pTxData;
  uint8_t pRxData;

  SpiData cmd;
  cmd.value = _cmd;

  // activate ADC with chip select
  HAL_GPIO_WritePin(pcsPort, pcsPin, GPIO_PIN_RESET);

  // send first command byte
  pTxData = cmd.hiByte;
  HAL_SPI_Transmit(mSpi, &pTxData, 8, 50); // TODO gestione timeout

  // send second command byte and receive first(msb) 4 bits
  // ATTENZIONE: BLOCKING MODE
  pTxData = cmd.loByte;
  HAL_SPI_TransmitReceive(mSpi, &pTxData, &pRxData, 8, 50); // TODO gestione timeout
  adc.hiByte = pTxData & 0x0F;

  // receive last(lsb) 8 bits
  // ATTENZIONE: BLOCKING MODE
  pTxData = 0x00;
  HAL_SPI_TransmitReceive(mSpi, &pTxData, &pRxData, 8, 50); // TODO gestione timeout
  adc.loByte = pRxData;

  // deactivate ADC with slave select
  HAL_GPIO_WritePin(pcsPort, pcsPin, GPIO_PIN_SET);

  return adc.value;
}

uint16_t MCP3208::createCmd(Channel ch)
{
  // base command structure
  // 0b000001cccc000000
  // c: channel config
  return
    // add channel to basic command structure
    static_cast<uint16_t>( (0x0400 | (ch << 6)) );
}

uint16_t MCP3208::execute(uint16_t cmd) const
{
  return transfer(cmd);
}

uint16_t MCP3208::read(Channel ch)
{
  return execute( createCmd(ch) );
}
