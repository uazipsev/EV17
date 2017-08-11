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
#include "COBS.h"
#include "PinDef.h"
#include "ADDRESSING.h"
#include "UART.h"
#include "Function.h"

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

void sendData(unsigned char whereToSend, unsigned char ComandByte, unsigned char DataTable, unsigned char DataTableIndex) {

    
    //calculate the crc
    
    unsigned char SendArray[30];
    unsigned char COBSArray[30];
    
    unsigned char DataLenth = 1;
    
    cobs_encode_result  result;
    
    SendArray[0] = 4+1;//ring_buffer.count;
    SendArray[1] = ComandByte;
    SendArray[2] = DataTable;
    SendArray[3] = DataTableIndex;
    SendArray[4] = DataLenth;

    //ring_buffer.count = 1;
    
    //send the rest of the packet
    int i;
    int count = 5;
    i = count;

        SendArray[5] = GetFaults(0);//ring_buffer.buf[i];
        //count++;
        SendArray[6] = GetFaults(1);//ring_buffer.buf[i];
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
        Send_put(SendArray[i]);
    }
}

 COBS_ENCODE_DST_BUF_LEN_MAX = 30;
 COBS_DECODE_DST_BUF_LEN_MAX = 30;

 char ReciveArray[30];
 char ProcessArray[30];

bool receiveData() {
    
    if(Receive_available()>5){
        if(Receive_get() == SS_ADDRESS){
            int i = 0;
            char Data = 0;
            do{
                Data = Receive_get();
                ReciveArray[i] = Data;
                __delay_us(100);
                i++;
            }while(Data != 0x00);
            
            cobs_decode_result result;

            result = cobs_decode(ProcessArray, sizeof(ProcessArray), ReciveArray, i);

            char CS = CRC8(ProcessArray, result.out_len-1);
            
            if(ProcessArray[result.out_len-1] == CS){
                INDICATOR ^= 1;
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