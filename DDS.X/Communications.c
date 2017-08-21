#include <stdbool.h>
#include <xc.h>
#include "CarCom.h"
#include "Communications.h"
#include "ADDRESSING.h"
#include "IO.h"
#include "mcc_generated_files/pin_manager.h"
#include "Function.h"

unsigned int DataBarGraphA, DataBarGraphB;

void updateComms() {
  
    if (receiveData()) {
        //INDICATOR_Toggle();
//        if (ReceiveArrayGet(RESPONSE_ADDRESS) == ECU_ADDRESS) {
//            respondECU();
//            handleIndicators(ReceiveArrayGet(LED_DDS));
//            DataBarGraphs(ReceiveArrayGet(THROTTLE_DDS), ReceiveArrayGet(BRAKE_DDS));
//            //ReceiveArrayGet(RESPONSE_ADDRESS) = 0;
//        }

    }
}

void handleIndicators(int receivedIndicators) {
    static int oldIndicators = 0;
    if (receivedIndicators != oldIndicators) {
        int i = 0;
        for (i = 0; i < NUM_INDICATORS; i++) {
            SetLEDOut(i, ((receivedIndicators >> i)&0x01));
        }
        oldIndicators = receivedIndicators;
    }

}

void DataBarGraphs(unsigned BGA, unsigned int BGB) {
    DataBarGraphA = BGA;
    DataBarGraphB = BGB;
}

unsigned int GetDataBarGraphA() {
    return DataBarGraphA;
}

unsigned int GetDataBarGraphB() {
    return DataBarGraphA;
}

unsigned int buttonsCollector() {
    unsigned int sendVal = 0;
    int i = 0;
    for (i = 0; i < NUM_BUTTONS; i++) {
        sendVal = sendVal | ((GetButtonState(i)&0x01) << i);
    }
    return sendVal;
}
