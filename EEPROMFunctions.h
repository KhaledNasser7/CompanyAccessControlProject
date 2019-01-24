/*
 * EEPROMFunctions.h
 *
 * Created: 05/06/2018 07:59:17 م
 *  Author: Khaled Mohamed Nasser
 */ 


#ifndef EEPROMFUNCTIONS_H_
#define EEPROMFUNCTIONS_H_

#include "I2C.h"

#define EEPROM_ADDRESS 0b10100000

uint8_t eeprom_write(uint16_t address,uint8_t data);
uint8_t eeprom_read(uint16_t address,uint8_t* data);



#endif /* EEPROMFUNCTIONS_H_ */