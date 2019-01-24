/*
 * EEPROMFunctions.c
 *
 * Created: 05/06/2018 07:59:55 م
 *  Author: Khaled Mohamed Nasser
 */ 

#include "EEPROMFunctions.h"


uint8_t eeprom_write(uint16_t address,uint8_t data){
	i2c_start();
	if((TWSR & 0xFC) != 0x08)
	return 0;
	i2c_write(EEPROM_ADDRESS|(uint8_t) (address & 0x0700>>7));
	if((TWSR & 0xFC) != 0x18)
	return 0;
	i2c_write((uint8_t) address);
	if((TWSR & 0xFC) != 0x28)
	return 0;
	i2c_write(data);
	if((TWSR & 0xFC) != 0x28)
	return 0;
	i2c_stop();
	return 1;
}


uint8_t eeprom_read(uint16_t address,uint8_t * data){
	i2c_start();
	if((TWSR & 0xFC) != 0x08)
	return 0;
	i2c_write(EEPROM_ADDRESS|(uint8_t) (address & 0x0700>>7));
	if((TWSR & 0xFC) != 0x18)
	return 0;
	i2c_write((uint8_t) address);
	if((TWSR & 0xFC) != 0x28)
	return 0;
	i2c_start();
	if((TWSR & 0xFC) != 0x10)
	return 0;
	i2c_write(EEPROM_ADDRESS|(uint8_t) (address & 0x0700>>7)|1);
	if((TWSR & 0xFC) != 0x40)
	return 0;
	*data = i2c_read(0);
	if((TWSR & 0xFC) != 0x58)
	return 0;
	i2c_stop();
	return 1;
}