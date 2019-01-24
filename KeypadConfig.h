/*
 * KeypadConfig.h
 *
 * Created: 20/05/2018 08:05:11 م
 *  Author: Khaled Mohamed Nasser
 */ 


#ifndef KEYPADCONFIG_H_
#define KEYPADCONFIG_H_

#define F_CPU		   12000000ul

// outputs (rows)
#define Keypad_R0	   7
#define Keypad_R0_DIR  DDRA
#define Keypad_R0_PORT PORTA

#define Keypad_R1	   6
#define Keypad_R1_DIR  DDRA
#define Keypad_R1_PORT PORTA

#define Keypad_R2	   5
#define Keypad_R2_DIR  DDRA
#define Keypad_R2_PORT PORTA

#define Keypad_R3	   4
#define Keypad_R3_DIR  DDRA
#define Keypad_R3_PORT PORTA

// inputs (columns)
#define Keypad_C0	   3
#define Keypad_C0_DIR  DDRA
#define Keypad_C0_PORT PORTA
#define Keypad_C0_PIN  PINA

#define Keypad_C1	   2
#define Keypad_C1_DIR  DDRA
#define Keypad_C1_PORT PORTA
#define Keypad_C1_PIN  PINA

#define Keypad_C2	   1
#define Keypad_C2_DIR  DDRA
#define Keypad_C2_PORT PORTA
#define Keypad_C2_PIN  PINA

#define Keypad_C3	   0
#define Keypad_C3_DIR  DDRA
#define Keypad_C3_PORT PORTA
#define Keypad_C3_PIN  PINA




#endif /* KEYPADCONFIG_H_ */