/*
 * UARTConfig.h
 *
 * Created: 21/05/2018 06:41:25 م
 *  Author: Khaled Mohamed Nasser
 */ 


#ifndef UARTCONFIG_H_
#define UARTCONFIG_H_

#define F_CPU 8000000ul

typedef enum{
	EVEN,ODD
	}parity_t;

typedef enum{
	ASYNCHRONOUS_NORMAL_MODE, ASYNCHRONOUS_DOUBLE_SPEED_MODE//, SYNCHRONOUS_MASTER_MODE, SYNCHRONOUS_SLAVE_MODE
	}uart_mode_t;	



#endif /* UARTCONFIG_H_ */