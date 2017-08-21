
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

unsigned int t1Raw, t2Raw, b1Raw, b2Raw;
        
extern int SAS_FAULT_CONDITION;
bool CheckThrotleConsistency() {
    GetDataDict(TABLE_TWO_SAS, SAS_THROTTLE_1, ADC_Data, 8);
    //int number = buf[0] | buf[1] << 8;
    t1Raw = ADC_Data[0] | (ADC_Data[1] << 8); //GetSASRaw(GETSAST1RAW)//
    throttle1 = t1Raw*TRATIO;
    t2Raw = ADC_Data[2] | (ADC_Data[3] << 8); //GetSASRaw(GETSAST1RAW)//
    throttle2 = t2Raw*TRATIO;
    b1Raw = ADC_Data[4] | (ADC_Data[5] << 8); //GetSASRaw(GETSAST1RAW)//
    brake1 = b1Raw*BRATIO;
    b2Raw = ADC_Data[6] | (ADC_Data[7] << 8); //GetSASRaw(GETSAST1RAW)//
    brake2 = b2Raw*BRATIO;    
    //throttle2 = GetSASRaw(GETSAST2RAW)*TRATIO;
    //brake1 = GetSASRaw(GETSASB1RAW)*BRATIO;
    //brake2 = GetSASRaw(GETSASB2RAW)*BRATIO;

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

unsigned int GetSASRaw(char request){
    if(request == GETSAST1RAW){
        return t1Raw;
    }
    else if(request == GETSAST2RAW){
        return t2Raw;
    }
    else if(request == GETSASB1RAW){
        return b1Raw;
    }
    else if(request == GETSASB2RAW){
        return b2Raw;
    }
    else return 0;
}