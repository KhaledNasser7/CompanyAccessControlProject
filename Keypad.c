/*
 * Keypad.c
 *
 * Created: 20/05/2018 08:05:33 م
 *  Author: Khaled Mohamed Nasser
 */ 


#include "Keypad.h"

void keypad_init(){
	// set rows as outputs from microcontroller (inputs to keypad)
	SETBIT(Keypad_R0_DIR,Keypad_R0);
	SETBIT(Keypad_R1_DIR,Keypad_R1);
	SETBIT(Keypad_R2_DIR,Keypad_R2);
	SETBIT(Keypad_R3_DIR,Keypad_R3);
	
	// set columns as inputs to microcontroller (outputs from keypad)
	CLRBIT(Keypad_C0_DIR,Keypad_C0);
	CLRBIT(Keypad_C1_DIR,Keypad_C1);
	CLRBIT(Keypad_C2_DIR,Keypad_C2);
	CLRBIT(Keypad_C3_DIR,Keypad_C3);
	
	// initialize outputs to high (rows)
	SETBIT(Keypad_R0_PORT,Keypad_R0);
	SETBIT(Keypad_R1_PORT,Keypad_R1);
	SETBIT(Keypad_R2_PORT,Keypad_R2);
	SETBIT(Keypad_R3_PORT,Keypad_R3);
	
	// enable pull-up resistors to the inputs (columns)
	SETBIT(Keypad_C0_PORT,Keypad_C0);
	SETBIT(Keypad_C1_PORT,Keypad_C1);
	SETBIT(Keypad_C2_PORT,Keypad_C2);
	SETBIT(Keypad_C3_PORT,Keypad_C3);
}


uint8_t keypad_get_pressed_key(){
	uint8_t keypad [4][4] = { {'1','2','3','A'},
							  {'4','5','6','B'},
							  {'7','8','9','C'},
							  {'*','0','#','D'}};
	button_status_t button_status = NOT_PRESSED;
	uint8_t row,col,key=255;
	for(row=0;row<4;row++){
		switch(row){
			case 0: CLRBIT(Keypad_R0_PORT,Keypad_R0);
					SETBIT(Keypad_R1_PORT,Keypad_R1);
					SETBIT(Keypad_R2_PORT,Keypad_R2);
					SETBIT(Keypad_R3_PORT,Keypad_R3);break;
			case 1: SETBIT(Keypad_R0_PORT,Keypad_R0);
					CLRBIT(Keypad_R1_PORT,Keypad_R1);
					SETBIT(Keypad_R2_PORT,Keypad_R2);
					SETBIT(Keypad_R3_PORT,Keypad_R3);break;
			case 2: SETBIT(Keypad_R0_PORT,Keypad_R0);
					SETBIT(Keypad_R1_PORT,Keypad_R1);
					CLRBIT(Keypad_R2_PORT,Keypad_R2);
					SETBIT(Keypad_R3_PORT,Keypad_R3);break;
			case 3: SETBIT(Keypad_R0_PORT,Keypad_R0);
					SETBIT(Keypad_R1_PORT,Keypad_R1);
					SETBIT(Keypad_R2_PORT,Keypad_R2);
					CLRBIT(Keypad_R3_PORT,Keypad_R3);break;
		}
		if(READBIT(Keypad_C0_PIN,Keypad_C0) == 0){
			col=0;
			button_status = PRESSED;
			break;
		}
		if(READBIT(Keypad_C1_PIN,Keypad_C1) == 0){
			col=1;
			button_status = PRESSED;
			break;
		}
		if(READBIT(Keypad_C2_PIN,Keypad_C2) == 0){
			col=2;
			button_status = PRESSED;
			break;
		}
		if(READBIT(Keypad_C3_PIN,Keypad_C3) == 0){
			col=3;
			button_status = PRESSED;
			break;
		}
	}
	if(button_status == PRESSED){
		key = keypad[row][col];
	}
	//_delay_ms(100);
	while( (READBIT(Keypad_C0_PIN,Keypad_C0) && READBIT(Keypad_C1_PIN,Keypad_C1)
	&& READBIT(Keypad_C2_PIN,Keypad_C2) && READBIT(Keypad_C3_PIN,Keypad_C3)) == 0);

	return key;
	
}