/*
 * I2C.h
 *
 * Created: 03/06/2018 09:42:45 م
 *  Author: Khaled Mohamed Nasser
 */ 


#ifndef I2C_H_
#define I2C_H_

#include <avr/io.h>
#include "I2CConfig.h"
#include <util/delay.h>
#include "Macros.h"


void i2c_init();
void i2c_start();
void i2c_write(uint8_t byte);
uint8_t i2c_read(uint8_t ack);
void i2c_stop();
void i2c_set_address(uint8_t address);



#endif /* I2C_H_ */