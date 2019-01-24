/*
 * I2C.c
 *
 * Created: 03/06/2018 09:42:57 م
 *  Author: Khaled Mohamed Nasser
 */ 


#include "I2C.h"


void i2c_init(){
	// SCL frequency = (CPU clock frequency) / (16+ ( 2 * TWBR * 4^(TWPS) ) )
	// no prescalar so TWPS0 & TWPS1 in TWSR are cleared
	CLRBIT(TWSR,TWPS0);
	CLRBIT(TWSR,TWPS1);
	// set TWBR to 18 for 50 khz
	TWBR=18;
}


void i2c_start(){
	// send start bit
	TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWSTA);
	while(READBIT(TWCR,TWINT)==0);
	// clear start bit TWSTA
}


void i2c_write(uint8_t byte){
	TWDR=byte;
	TWCR = (1<<TWEN)|(1<<TWINT);
	while(READBIT(TWCR,TWINT)==0);
}


uint8_t i2c_read(uint8_t ack){
	TWCR = (ack<<TWEA)|(1<<TWEN)|(1<<TWINT);
	while(READBIT(TWCR,TWINT)==0);
	return TWDR;
}


void i2c_stop(){
	TWCR = (1<<TWEN)|(1<<TWSTO)|(1<<TWINT);
}


void i2c_set_address(uint8_t address){
	TWAR=address;
}