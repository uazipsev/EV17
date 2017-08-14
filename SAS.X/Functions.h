/* 
 * File:   Functions.h
 * Author: Rick
 *
 * Created on May 19, 2015, 1:33 AM
 */

#ifndef FUNCTIONS_H
#define	FUNCTIONS_H


#ifndef __DELAY_H
#define FOSC  72000000LL  // clock-frequecy in Hz with suffix LL (64-bit-long), eg. 32000000LL for 32MHz
#define FCY       (FOSC/2)  // MCU is running at FCY MIPS
#define delay_us(x) __delay32(((x*FCY)/1000000L)) // delays x us
#define delay_ms(x) __delay32(((x*FCY)/1000L))  // delays x ms
#define __DELAY_H 1
#include <libpic30.h>
#endif

#define PPSin(fn,pin)    iPPSInput(IN_FN_PPS##fn,IN_PIN_PPS##pin)
#define PPSout(fn,pin)    iPPSOutput(OUT_PIN_PPS##pin,OUT_FN_PPS##fn)

void Delay(int ms);
void Setup(void);
void PinSetMode(void);
void timerOne(void);
void timerTwo(void);

#endif	/* FUNCTIONS_H */

