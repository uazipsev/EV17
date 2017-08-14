/* 
 * File:   main.h
 * Author: User
 *
 * Created on May 27, 2015, 5:30 PM
 */

#ifndef MAIN_H
#define	MAIN_H

    extern volatile bool ADCSamp;
    extern void handleADCValues();
    extern volatile bool ADCDataReady;
    extern volatile unsigned int LEDtime, ADCTime;

    extern void Delay(int ms);
    extern void Setup(void);

#endif	/* MAIN_H */

