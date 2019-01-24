/*
 * I2CConfig.h
 *
 * Created: 03/06/2018 09:42:33 م
 *  Author: Khaled Mohamed Nasser
 */ 


#ifndef I2CCONFIG_H_
#define I2CCONFIG_H_

#define F_CPU 8000000ul

#define START_BIT_SENT				0x08
#define REPEATED_START_BIT_SENT		0x10
#define SLA_W_SENT_ACK_RECEIVED		0x18
#define SLA_W_SENT_NACK_RECEIVED	0x20
#define DATA_SENT_ACK_RECEIVED		0x28
#define DATA_SENT_NACK_RECEIVED		0x30



#endif /* I2CCONFIG_H_ */