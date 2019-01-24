/*
 * Keypad.h
 *
 * Created: 20/05/2018 08:05:24 م
 *  Author: Khaled Mohamed Nasser
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#include <avr/io.h>
#include "Macros.h"
#include "KeypadConfig.h"
#include <util/delay.h>

typedef enum {
	PRESSED,NOT_PRESSED
	}button_status_t;

void keypad_init();

uint8_t keypad_get_pressed_key();





#endif /* KEYPAD_H_ */