/* 
 * File:   SASComms.h
 * Author: User
 *
 * Created on June 7, 2015, 7:35 PM
 */

#ifndef SASCOMMS_H
#define	SASCOMMS_H


#include "ADDRESSING.h"
#include <stdbool.h>





bool CheckThrotleConsistency();
void SetBrakeValue(int val);
void SetThrottleValue(int val);

bool receiveCommSAS();
bool requestSASData();
unsigned int GetSASRaw(char request);
void ClearSASTalk();

#endif	/* SASCOMMS_H */

