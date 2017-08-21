
#include "ThrottleBrakeControl.h"
#include "SASComms.h"
#include "PinDef.h"
#include "Timers.h"
#include "DriverConfigs.h"
#include "CarDataDictionary.h"

#define DELTAUPDATE 100

#define TRATIO 0.0423
#define BRATIO 0.0525

unsigned int throttle1, throttle2, brake1,brake2;
unsigned int ThrottlePrecent, TripThrottle, TripBrake, ThrottleMax = 0;

unsigned int DeltaLastTime = 0;

        unsigned char ADC_Data[8];
//        ADC_Data[0] = GetADC(Throttle1) & 0xFF;
//        ADC_Data[1] = GetADC(Throttle1) >> 8;
//        ADC_Data[2] = GetADC(Throttle2) & 0xFF;
//        ADC_Data[3] = GetADC(Throttle2) >> 8;
//        ADC_Data[4] = GetADC(Brake1) & 0xFF;
//        ADC_Data[5] = GetADC(Brake1) >> 8;
//        ADC_Data[6] = GetADC(Brake2) & 0xFF;
//        ADC_Data[7] = GetADC(Brake2) >> 8;
//        SetDataDict(TABLE_TWO_SAS, SAS_THROTTLE_1, ADC_Data, 8);

extern int SAS_FAULT_CONDITION;
bool CheckThrotleConsistency() {
    GetDataDict(TABLE_TWO_SAS, SAS_THROTTLE_1, ADC_Data, 8);
    //int number = buf[0] | buf[1] << 8;
    throttle1 = ADC_Data[0] | (ADC_Data[1] << 8); //GetSASRaw(GETSAST1RAW)//
    throttle1 = throttle1*TRATIO;
    throttle2 = ADC_Data[2] | (ADC_Data[3] << 8); //GetSASRaw(GETSAST1RAW)//
    throttle2 = throttle2*TRATIO;
    //throttle2 = GetSASRaw(GETSAST2RAW)*TRATIO;
    brake1 = GetSASRaw(GETSASB1RAW)*BRATIO;
    brake2 = GetSASRaw(GETSASB2RAW)*BRATIO;

    //throttle consistency check
    if((((throttle1*(ThrottlePrecent/100)) > throttle2) && ((throttle1 *((ThrottlePrecent/100)-1)) < throttle2))) {
        //SAS_FAULT_CONDITION = THROTTLE_SANITY_CHECK; // TODO: This is erroring out - need filtering!
        //throttle1=0;
        //throttle2=0;
    }
    if ((((throttle1 + throttle2) / 2) > TripThrottle) && (brake1 > TripBrake)) {
        //SAS_FAULT_CONDITION = THROTTLE_BRAKE_CHECK;  //  TODO: Fix me
        //throttle1=0;
        //throttle2=0;
        //brake1=0;
    }
    if((throttle1 > GetDriverMaxThrottle()) || (throttle2 > GetDriverMaxThrottle())){
        //throttle1 = ThrottleMax;
        //throttle2 = ThrottleMax;
    }
    return true;
}

void DeltaThrottle(){
    if((GetTime(DELTATIMER) - DeltaLastTime) > DELTAUPDATE){
        int ramp = GetDriverRamp();
        if(ramp){
            
            
        }
    }
    
}

unsigned int GetThrottleBrakeValue(char request){
    if(request == GETSAST1){
        return throttle1;
    }
    else if(request == GETSAST2){
        return throttle2;
    }
    else if(request == GETSASB1){
        return brake1;
    }
    else if(request == GETSASB2){
        return brake2;
    }
    else return 0;
}

char GetSASFalts(){
    return SAS_FAULT_CONDITION;
}

void SetThrotteMax(int val){
    ThrottleMax = val;
}