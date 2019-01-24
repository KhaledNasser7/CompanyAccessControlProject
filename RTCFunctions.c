/*
 * RTCFunctions.c
 *
 * Created: 05/06/2018 04:47:49 م
 *  Author: Khaled Mohamed Nasser
 */ 


#include "RTCFunctions.h"

void ds1307_set_time(uint8_t hours,uint8_t minutes,uint8_t seconds){
	i2c_start();
	i2c_write(DS1307_address_write_mode); //write address of ds1307
	i2c_write(0x00);					 //write address of first byte to access to register pointer
	i2c_write(seconds);
	i2c_write(minutes);
	i2c_write(hours);
	i2c_stop();
}


void ds1307_set_date(uint8_t year,uint8_t month,uint8_t day){
	i2c_start();
	i2c_write(DS1307_address_write_mode); //write address of ds1307
	i2c_write(0x04);					 //write address of first byte to access to register pointer
	i2c_write(day);
	i2c_write(month);
	i2c_write(year);
	i2c_stop();
}


time_t ds1307_get_time(){
	time_t time;
	i2c_start();
	i2c_write(DS1307_address_write_mode); //write address of ds1307
	i2c_write(0x00);					 //write address of first byte to access to register pointer
	i2c_start();
	i2c_write(DS1307_address_read_mode);  // read
	time.seconds=i2c_read(1);
	time.minutes=i2c_read(1);
	time.hours=i2c_read(0);
	i2c_stop();
	return time;
}


date_t ds1307_get_date(){
	date_t date;
	i2c_start();
	i2c_write(DS1307_address_write_mode); //write address of ds1307
	i2c_write(0x04);					 //write address of first byte to access to register pointer
	i2c_start();
	i2c_write(DS1307_address_read_mode);
	date.day=i2c_read(1);
	_delay_ms(50);
	date.month=i2c_read(1);
	_delay_ms(50);
	date.year=i2c_read(0);
	_delay_ms(50);
	i2c_stop();
	return date;
}