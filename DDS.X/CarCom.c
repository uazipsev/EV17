/*
 * File:   CarComm - SS
 * Author: Richard Johnson
 *
 * Created on May 31, 2015
 */

#include <xc.h>
#include <stdbool.h>
#include <stdlib.h>
#include "CarCom.h"
#include "COBS.h"
#include "ADDRESSING.h"
#include "UART.h"
#include "Function.h"
#include "CarDataDictionary.h"
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/mcc.h"


#define polynomial 0x8C  //polynomial used to calculate crc

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

//Sends out send buffer with a 2 start bytes, where the packet is going, where it came from, the size of the data packet, the data and the crc.

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

bool receiveData() {
    
    if(Receive_available()>5){
        if(Receive_get() == DDS_ADDRESS){
            int i = 0;
            do{
                Data = Receive_get();
                ReciveArray[i] = Data;
                __delay_us(100);
                i++;
            }while(Data != 0x00);
            
            
            cobs_decode_result result;

            result = cobs_decode(ProcessArray, sizeof(ProcessArray), ReciveArray, i);

            unsigned char CS = CRC8(ProcessArray, result.out_len-1);
            
            if(ProcessArray[result.out_len-1] == CS){
                INDICATOR_Toggle();
                ComController(ProcessArray,result.out_len);
                return true;
            }
        }
        else{
            do{
                Data = Receive_get();
            }while(Data != 0x00);
            
//        Talk_LAT = TALK;  //RS485 set to talk
//        Delay(5);
        //sendData(ECU_ADDRESS, WRITE_TABLE, TABLE_ONE_SS, SS_FAULT_STATUS, DataToSend, DTI[4]);
//        int k = 0;
//        for(k=0;k<10;k++){
//            printf("%u",ProcessArray[k]);
//        }
//        Delay(3);
//        Talk_LAT = LISTEN;  ///RS485 set to listen
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
        Talk_LAT = TALK;  //RS485 set to talk
        Delay(5);
        sendData(ECU_ADDRESS, WRITE_TABLE, TABLE_ONE_SS, SS_FAULT_STATUS, DataToSend, DTI[4]);
        Delay(3);
        Talk_LAT = LISTEN;  ///RS485 set to listen
    }
}