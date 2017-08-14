#include "PDUComms.h"
#include "StateMachine.h"
#include <xc.h>
#include "PinDef.h"
#include "xc.h"
#include "Timers.h"
#include "CarCom_PDU_MCS_BMM.h"
#include "Communications.h"

bool readyToSendPDU = true;
bool PDU_COMMS_ERROR = false;
extern struct powerStates powerSet;

bool requestPDUData() {
//    if((GetTime(PDUTIMER) > PDU_BOARD_RESEND_MIN) && (readyToSendPDU == true)){
//        SetTime(PDUTIMER);
//        RS485_Direction2(TALK);
//        ToSend(RESPONSE_ADDRESS, ECU_ADDRESS);
//        ToSend(POWER_RAILS, constructPowerSet());
//        sendData(PDU_ADDRESS);
//        return true;
//    }
//    else if(readyToSendPDU == false){
        return true;
//    }
//    else{
//        return false;
//    }
}

bool receiveCommPDU() {
//    if (receiveData()) {
//        if (ReceiveArrayGet(RESPONSE_ADDRESS) == PDU_ADDRESS) {
//            readyToSendPDU = true;
//            SetTime(PDUTIMER);
//            //INDICATOR ^= 1;
            return true;
//        }
//        else{
//            wipeRxBuffer();
//            return false;
//        }
//    } 
//    else{
//        return false;
//    }
}

bool powerChange() {
    static bool BMM, MCS, DDS, SAS;
    bool returnable = false;
    if (BMM != powerSet.BMM) {
        BMM = powerSet.BMM;
        returnable = true;
    }
    if (DDS != powerSet.DDS) {
        DDS = powerSet.DDS;
        returnable = true;
    }
    if (SAS != powerSet.SAS) {
        SAS = powerSet.SAS;
        returnable = true;
    }
    if (MCS != powerSet.MCS) {
        MCS = powerSet.MCS;
        returnable = true;
    }
    return returnable;
}

unsigned char  constructPowerSet() {
    static unsigned char powerSettings = 0;
    if (powerSet.BMM) {
        powerSettings |= 1 << 1;
    } else
        powerSettings &= ~(1 << 1);
    if (powerSet.MCS) {
        powerSettings |= 1 << 2;
    } else
        powerSettings &= ~(1 << 2);
    if (powerSet.DDS) {
        powerSettings |= 1 << 3;
    } else
        powerSettings &= ~(1 << 3);
    if (powerSet.SAS) {
        powerSettings |= 1 << 4;
    } else
        powerSettings &= ~(1 << 4);
    if (powerSet.TSS) {
        powerSettings |= 1 << 5;
    } else
        powerSettings &= ~(1 << 5);
    if (powerSet.AUX) {
        powerSettings |= 1 << 6;
    } else
        powerSettings &= ~(1 << 6);
    if (powerSet.COOLING) {
        powerSettings |= 1 << 7;
    } else
        powerSettings &= ~(1 << 7);
    return powerSettings;
}

void ClearPDUTalk(){
    readyToSendPDU = true;
}
