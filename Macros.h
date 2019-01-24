/*
 * Macros.h
 *
 * Created: 19/05/2018 04:30:12 م
 *  Author: Khaled Mohamed Nasser
 */ 


#ifndef MACROS_H_
#define MACROS_H_

#include <stdint.h>

#define SETBIT(REG,BIT)  (REG |= 1 << BIT)
#define CLRBIT(REG,BIT)  (REG &= ~(1 << BIT))
#define TOGBIT(REG,BIT)  (REG ^= 1 << BIT)
#define READBIT(REG,BIT)  ((REG >> BIT) & 1)

typedef enum{
	FALSE,TRUE
	}boolean_t;



#endif /* MACROS_H_ */