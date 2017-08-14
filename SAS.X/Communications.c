
#include "Communications.h"
#include "ADC.h"
#include "CarCom.h"
#include "ADC.h"
#include "ADDRESSING.h"

void updateComms() {
    if(receiveData()){
        unsigned char ADC_Data[8];
        ADC_Data[0] = GetADC(Throttle1) & 0xFF;
        ADC_Data[1] = GetADC(Throttle1) >> 8;
        ADC_Data[2] = GetADC(Throttle2) & 0xFF;
        ADC_Data[3] = GetADC(Throttle2) >> 8;
        ADC_Data[4] = GetADC(Brake1) & 0xFF;
        ADC_Data[5] = GetADC(Brake1) >> 8;
        ADC_Data[6] = GetADC(Brake2) & 0xFF;
        ADC_Data[7] = GetADC(Brake2) >> 8;
        SetDataDict(TABLE_TWO_SAS, SAS_THROTTLE_1, ADC_Data, 8);
    }

}