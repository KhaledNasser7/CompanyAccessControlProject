/*
 * UART.h
 *
 * Created: 21/05/2018 06:41:34 م
 *  Author: Khaled Mohamed Nasser
 */ 


#ifndef UART_H_
#define UART_H_

#include "Macros.h"
#include <avr/io.h>
#include "UARTConfig.h"
#include <util/delay.h>

void uart_init(uart_mode_t mode,uint32_t baud_rate,uint8_t character_size,boolean_t parity_check,parity_t parity_type,uint8_t stop_bits);
void uart_transmit(uint16_t data);
uint16_t uart_receive();




#endif /* UART_H_ */