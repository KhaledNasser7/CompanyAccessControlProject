/*
 * VirtualTerminal.c
 *
 * Created: 24/05/2018 04:13:49 م
 *  Author: Khaled Mohamed Nasser
 */ 

#include "VirtualTerminal.h"


void virtual_terminal_init(){
	uart_init(ASYNCHRONOUS_NORMAL_MODE,9600,8,FALSE,ODD,1);
}


void virtual_terminal_print_character(uint8_t character){
	uart_transmit(character);
}


void virtual_terminal_print_string(uint8_t * string){
	uint8_t i=0;
	while(string[i] != '\0'){
		virtual_terminal_print_character(string[i]);
		i++;
	}
}


void virtual_terminal_print_number(uint32_t num){
	uint32_t arr[10];
	uint8_t i;
	for(i=0;i<10;i++){
		arr[i]=0;
	}
	i=0;
	while(num != 0){
		arr[10-i-1]=num%10;
		num/=10;
		i++;
	}
	boolean_t leading_zeros_flag = TRUE;
	for(i=0;i<10;i++){
		if(arr[i] != 0){
			leading_zeros_flag = FALSE;
		}
		if(!leading_zeros_flag){
		virtual_terminal_print_character( (arr[i]+48) );
		}
	}
	if(leading_zeros_flag){
		virtual_terminal_print_character( '0' );
	}
	
}


void virtual_terminal_newLine(){
	uart_transmit('\r');
}


void virtual_terminal_clear(){
	uart_transmit('\f');
}

void virtual_terminal_backspace(){
	uart_transmit('\b');
}