/*
 * RTCFunctions.h
 *
 * Created: 05/06/2018 04:47:21 م
 *  Author: Khaled Mohamed Nasser
 */ 


#ifndef RTCFUNCTIONS_H_
#define RTCFUNCTIONS_H_

#include "I2C.h"

typedef struct{
	uint8_t hours;
	uint8_t minutes;
	uint8_t seconds;
	}time_t;

typedef struct{
	uint16_t year;
	uint8_t month;
	uint8_t day;
	}date_t;

#define DS1307_address_write_mode 0b11010000
#define DS1307_address_read_mode  0b11010001

void ds1307_set_time(uint8_t hours,uint8_t minutes,uint8_t seconds);
void ds1307_set_date(uint8_t year,uint8_t month,uint8_t day);
time_t ds1307_get_time();
date_t ds1307_get_date();


#endif /* RTCFUNCTIONS_H_ */