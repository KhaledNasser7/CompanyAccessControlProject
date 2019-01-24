/*
 * VirtualTerminal.h
 *
 * Created: 24/05/2018 04:13:34 م
 *  Author: Khaled Mohamed Nasser
 */ 


#ifndef VIRTUALTERMINAL_H_
#define VIRTUALTERMINAL_H_

#include "UART.h"

void virtual_terminal_init();
void virtual_terminal_print_character(uint8_t character);
void virtual_terminal_print_string(uint8_t * string);
void virtual_terminal_print_number(uint32_t num);
void virtual_terminal_newLine();
void virtual_terminal_backspace();
void virtual_terminal_clear();



#endif /* VIRTUALTERMINAL_H_ */