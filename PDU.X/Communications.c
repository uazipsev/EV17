/*
 PDU Communications
    Authored by Zac Kilburn 6/2/2015
 */

#include <stdbool.h>
#include <xc.h>
#include "Communications.h"
#include "ADDRESSING.h"
#include "Functions.h"
#include "PDU.h"
#include "CarCom.h"
#include "mcc_generated_files/pin_manager.h" 
#include "CarDataDictionary.h"



void updateComms() {
    if (receiveData()){
        unsigned char DataGet[2];
        GetDataDict(TABLE_FOUR_PDU, PDU_POWER_CONTROL, DataGet, 1);
        processPowerRequest(DataGet[0]);
        DataGet[0] = FaultsCollector();
        SetDataDict(TABLE_FOUR_PDU, PDU_POWER_STATUS, DataGet, 1);
    }
}


void processPowerRequest(unsigned char powerSet) {

    if (((powerSet >> 1)  & 0x01)){
        EnableSlavePower(BMM, ON);
    }
    else{
        EnableSlavePower(BMM, OFF);
    }
    if (((powerSet >> 2)  & 0x01)){
        EnableSlavePower(MCS, ON);
    }
    else{
        EnableSlavePower(MCS,OFF);
    }
    if (((powerSet >> 3)  & 0x01)){
        EnableSlavePower(DDS,ON);
    }
    else{
        EnableSlavePower(DDS,OFF);
    }
    if(((powerSet >> 4)  & 0x01)){
        EnableSlavePower(SAS,ON);
    }
    else{
        EnableSlavePower(SAS,OFF);
    }
    if(((powerSet >> 5)  & 0x01)){
        EnableSlavePower(TSS, ON);
    }
    else{
        EnableSlavePower(TSS,OFF);
    }
    Update();
}

unsigned char FaultsCollector() {
    unsigned int sendVal = 0;
    int i = 0;
    for (i = 0; i < 5; i++) {
        sendVal = sendVal | ((GetPDUFault(i)&0x01) << i);
    }
    return sendVal;
}