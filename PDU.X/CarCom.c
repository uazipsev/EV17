/*
 * File:   FastTransfer.c
 * Author: Zac Kilburn
 *
 * Created on May 31, 2015
 */

#include <xc.h>
#include <stdbool.h>
#include <stdlib.h>
#include "CarCom.h"
#include "mcc_generated_files/pin_manager.h"
#include "ADDRESSING.h"
#include "COBS.h"
#include "mcc_generated_files/mcc.h"
#include "Functions.h"
#include "CarDataDictionary.h"
#include "UART.h"
//CRC Calculator

unsigned char CRC8(const unsigned char * data, unsigned char len) {
    unsigned char crc = 0x00;
    while (len--) {
        unsigned char extract = *data++;
        unsigned char tempI;
        for (tempI = 8; tempI; tempI--) {
            unsigned char sum = (crc ^ extract) & 0x01;
            crc >>= 1;
            if (sum) {
                crc ^= polynomial;
            }
            extract >>= 1;
        }
    }
    return crc;
}


void sendData(unsigned char whereToSend, unsigned char ComandByte, unsigned char DataTable, unsigned char DataTableIndex, unsigned char *DTS, unsigned int lenth) {
    unsigned char SendArray[30];
    unsigned char COBSArray[30];
    
    cobs_encode_result  result;
    
    SendArray[0] = NUMOFEXTBYTES+lenth;//ring_buffer.count;
    SendArray[1] = ComandByte;
    SendArray[2] = DataTable;
    SendArray[3] = DataTableIndex;
    SendArray[4] = lenth;

    unsigned char i = 0;
    int count = NUMOFEXTBYTES;

    for(i;i<lenth;i++){
        SendArray[i+NUMOFEXTBYTES] = DTS[i];
        count++;
    }
    
    unsigned char CS = CRC8(SendArray, count);
    SendArray[count] = CS;
    count++;
    result = cobs_encode(COBSArray, sizeof(COBSArray), SendArray, count);
    SendArray[0] = whereToSend;
    
    for(i = 1;i<result.out_len+1;i++){
        SendArray[i] = COBSArray[i-1];
    }
    
    for(i = 0;i<result.out_len+2;i++){
        Send_put(SendArray[i]);
    }
}

unsigned char ReciveArray[30];
unsigned char ProcessArray[30];

unsigned char Data = 0;

bool receiveData(){
    if(Receive_available()>5){
        if(Receive_get() == PDU_ADDRESS){
            int i = 0;
            do{
                Data = Receive_get();
                ReciveArray[i] = Data;
                __delay_us(200);
                //printf("%u ",Data);
                i++;
            }while(Data != 0x00);
            
            //printf("\n\r ");
            
            ClearBuffer();
            
            cobs_decode_result result;

            result = cobs_decode(ProcessArray, sizeof(ProcessArray), ReciveArray, i);
            
            unsigned char CS = CRC8(ProcessArray, result.out_len-1);
            
            if(ProcessArray[result.out_len-1] == CS){
                LED1_Toggle();
                ComController(ProcessArray,result.out_len);
                return true;
            }
        }
        else{
//            do{
//                Data = Receive_get();
//            }while(Data != 0x00);
        }
    }
    else{
       // ClearBuffer();
    }
    
    return false;
}



void ComController(unsigned char *DTI, unsigned int lenth){
    if(DTI[1] == READ_TABLE){
        unsigned char DataToSend[4];
        GetDataDict(DTI[2], DTI[3], DataToSend, DTI[4]);
        FLOW_CNTL_SetHigh();// = TALK;  //RS485 set to talk
        Delay(5);
        sendData(ECU_ADDRESS, 2, 1, 1, DataToSend, DTI[4]);
        Delay(3);
        FLOW_CNTL_SetLow();  ///RS485 set to listen
    }
    if(DTI[1] == WRITE_TABLE){
        unsigned char DataToSend[4];
        unsigned char DataRecived[4];
        for(char k = 0;k<DTI[4];k++){
            DataRecived[k] = DTI[5+k];
        }
        SetDataDict(DTI[2], DTI[3], DataRecived, DTI[4]);
        GetDataDict(TABLE_FOUR_PDU, PDU_POWER_STATUS, DataToSend, 1);
        FLOW_CNTL_SetHigh();// = TALK;  //RS485 set to talk
        Delay(2);
        sendData(ECU_ADDRESS, WRITE_TABLE, TABLE_FOUR_PDU, PDU_POWER_STATUS, DataToSend, 1);
        Delay(5);
        FLOW_CNTL_SetLow();  ///RS485 set to listen
    }
}