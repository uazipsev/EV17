/*
 * File:   FastTransfer1.c
 * Author: Zac Kilburn
 *
 * Created on May 31, 2015
 */

#include <xc.h>
#include <stdbool.h>
#include <stdlib.h>
#include "CarCom_SAS_DDS_SS.h"
#include "UART1.h"
#include "ADDRESSING.h"
#include "PinDef.h"

#include "COBS.h"

unsigned char CRC81(const unsigned char * data, unsigned char len);


void sendData1(unsigned char whereToSend, unsigned char ComandByte, unsigned char DataTable, unsigned char DataTableIndex, unsigned char *DTS, unsigned int lenth) {

    
    //calculate the crc
    
    unsigned char SendArray[30];
    unsigned char COBSArray[30];
    
    unsigned char DataLenth = 1;
    
    cobs_encode_result  result;
    
    SendArray[0] = 4+1;//ring_buffer.count;
    SendArray[1] = ComandByte;
    SendArray[2] = DataTable;
    SendArray[3] = DataTableIndex;
    SendArray[4] = lenth;

    //ring_buffer.count = 1;
    
    //send the rest of the packet
    unsigned int i;
    int count = 5;
    i = count;

        SendArray[5] = DTS[0];//ring_buffer.buf[i];
        //count++;
        SendArray[6] = DTS[1];//ring_buffer.buf[i];
        //count++;

    unsigned char CS = CRC8(SendArray, 7);
    //send the crc
    //printf("CRC = %x\n",CS);
    
    SendArray[7] = CS;
    
    result = cobs_encode(COBSArray, sizeof(COBSArray), SendArray, 8);
    
    SendArray[0] = whereToSend;
    
    for(i = 1;i<result.out_len+1;i++){
        SendArray[i] = COBSArray[i-1];
    }
    
    
    for(i = 0;i<result.out_len+2;i++){
        Send_put1(SendArray[i]);
    }
}

 unsigned char ReciveArray1[30];
 unsigned char ProcessArray1[30];

bool receiveData1() {
    if(Receive_available1()>5){
        if(Receive_get1() == ECU_ADDRESS){
            int i = 0;
            unsigned char Data = 0;
            do{
                Data = Receive_get1();
                ReciveArray1[i] = Data;
                DelayUS(200);
                //printf("%u ",Data);
                i++;
            }while(Data != 0x00);
            
            //printf("\n\r ");
            
            ClearBuffer();
            
            cobs_decode_result result;

            result = cobs_decode(ProcessArray1, sizeof(ProcessArray1), ReciveArray1, i);
            
            unsigned char CS = CRC8(ProcessArray1, result.out_len-2);
            
            if(ProcessArray1[result.out_len-2] == CS){
                INDICATOR ^= 1;
                ComController1(ProcessArray1,result.out_len);
                return true;
            }
        }
        else{
            //ClearBuffer();
        }
    }
    else{
       // ClearBuffer();
    }
    
    return false;
}

#define READ_TABLE 1

void ComController1(unsigned char *DTI, unsigned int lenth){
    if(DTI[1] == READ_TABLE){
        unsigned char DataToSend[4];
        GetDataDict(DTI[2], DTI[3], DataToSend, DTI[4]);
        RS485_2_Direction = TALK;  //RS485 set to talk
        Delay(5);
        sendData(ECU_ADDRESS, 1, 1, 1, DataToSend, DTI[4]);
        Delay(3);
        RS485_2_Direction = LISTEN;   ///RS485 set to listen
    }
}

unsigned char CRC81(const unsigned char * data, unsigned char len) {
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