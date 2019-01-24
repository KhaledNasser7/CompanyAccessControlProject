/*
 * UART.c
 *
 * Created: 21/05/2018 06:41:44 م
 *  Author: Khaled Mohamed Nasser
 */ 

#include "UART.h"

void uart_init(uart_mode_t mode,uint32_t baud_rate,uint8_t character_size,boolean_t parity_check,parity_t parity_type,uint8_t stop_bits){
	// set mode and baud rate
	uint32_t ubrr_value;
	switch(mode){
		case ASYNCHRONOUS_NORMAL_MODE :			CLRBIT(UCSRA,U2X);
												ubrr_value = (F_CPU/(16*baud_rate))-1;
												UBRRH = (ubrr_value >>8);
												UBRRL = ubrr_value;break;
		case ASYNCHRONOUS_DOUBLE_SPEED_MODE :   SETBIT(UCSRA,U2X);
												ubrr_value = (F_CPU/(8*baud_rate))-1;
												UBRRH = (ubrr_value >>8);
												UBRRL = ubrr_value;break;
	}
	
	// Enable uart transmit and receive
	SETBIT(UCSRB,TXEN);
	SETBIT(UCSRB,RXEN);
	// set character size , parity and stop bits options
	SETBIT(UCSRC,URSEL);  // select UCSRC
	switch(character_size){
		case 5 : CLRBIT(UCSRB,UCSZ2);
				 CLRBIT(UCSRC,UCSZ1);
				 CLRBIT(UCSRC,UCSZ0);break;
		case 6 : CLRBIT(UCSRB,UCSZ2);
				 CLRBIT(UCSRC,UCSZ1);
				 SETBIT(UCSRC,UCSZ0);break;
		case 7 : CLRBIT(UCSRB,UCSZ2);
				 SETBIT(UCSRC,UCSZ1);
				 CLRBIT(UCSRC,UCSZ0);break;
		case 8 : CLRBIT(UCSRB,UCSZ2);
				 SETBIT(UCSRC,UCSZ1);
				 SETBIT(UCSRC,UCSZ0);break;
		case 9 : SETBIT(UCSRB,UCSZ2);break;
		default: CLRBIT(UCSRB,UCSZ2);			// defualt case is 8-bit character
				 SETBIT(UCSRC,UCSZ1);
				 SETBIT(UCSRC,UCSZ0);break;	
	}
	if(parity_check == FALSE){
		CLRBIT(UCSRC,UPM1);
		CLRBIT(UCSRC,UPM0);
	}else{
		if(parity_type == EVEN){
			SETBIT(UCSRC,UPM1);
			CLRBIT(UCSRC,UPM0);
		}else{
			SETBIT(UCSRC,UPM1);
			SETBIT(UCSRC,UPM0);
		}
	}
	if(stop_bits == 0){
		CLRBIT(UCSRC,USBS);
	}else{
		SETBIT(UCSRC,USBS);
	}
}


void uart_transmit(uint16_t data){
	while( READBIT(UCSRA,UDRE) == 0 );		//wait till UDR is empty
	if( READBIT(UCSRB,UCSZ2) ){						// 9-bit character
		if( READBIT(data,8) ){
			SETBIT(UCSRB,TXB8);
		}else{
			CLRBIT(UCSRB,TXB8);
		}
	}else{/*MISRA*/}
	UDR = data;
}


uint16_t uart_receive(){
	while( READBIT(UCSRA,RXC) == 0 );		//wait till receive is complete
	uint16_t data=0;
	if( READBIT(UCSRB,UCSZ2) ){					// 9-bit character
		if( READBIT(UCSRB,RXB8) ){
			SETBIT(data,8);
			}else{
			CLRBIT(data,8);
		}
	}
	data|=UDR;
	return data;
}