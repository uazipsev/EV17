/*
 * File:   FastTransfer.c
 * Author: Zac Kilburn
 *
 * Created on May 31, 2015
 */

#include <xc.h>
#include <stdbool.h>
#include <stdlib.h>
#include "CarCom_PDU_MCS_BMM.h"
#include "UART.h"
#include "ADDRESSING.h"
#include "COBS.h"
#include "PinDef.h"
#include "Functions.h"

bool PacketRecived_PDU_MCS_BMM = false;

void sendData_PDU_MCS_BMM(unsigned char whereToSend, unsigned char ComandByte, unsigned char DataTable, unsigned char DataTableIndex, unsigned char *DTS, unsigned int lenth) {
    unsigned char SendArray[30];
    unsigned char COBSArray[30];
    
    int j = 0;
    for(j;j<sizeof(SendArray);j++){
        SendArray[j] = 0;
    }
    
    cobs_encode_result  result;
    
    SendArray[0] = NUMOFEXTBYTES+lenth;//ring_buffer.count;
    SendArray[1] = ComandByte;
    SendArray[2] = DataTable;
    SendArray[3] = DataTableIndex;
    SendArray[4] = lenth;

    unsigned char i = 0;
    int count = NUMOFEXTBYTES;
    
    for(i=0;i<lenth;i++){
        SendArray[i+NUMOFEXTBYTES] = DTS[i];
        count++;
    }
    
    unsigned char CS = CRC8_PDU_MCS_BMM(SendArray, count);
    SendArray[count] = CS;
    count++;
    
    result = cobs_encode(COBSArray, sizeof(COBSArray), SendArray, count);
    SendArray[0] = whereToSend;
     
    for(i = 1;i<result.out_len+1;i++){
        SendArray[i] = COBSArray[i-1];
    }
    
    PacketRecived_PDU_MCS_BMM = false;
    
    for(i = 0;i<result.out_len+2;i++){
        Send_put(SendArray[i]);
    }
}

 char ReciveArray[30];
 char ProcessArray[30];

bool receiveData_PDU_MCS_BMM() {
    if(Receive_available()>5){
        if(Receive_get() == ECU_ADDRESS){
            int i = 0;
            unsigned char Data = 0;
            do{
                Data = Receive_get();
                ReciveArray[i] = Data;
                DelayUS(200);;
                i++;
            }while(Data != 0x00);
            
            ClearBuffer();
            
            cobs_decode_result result;

            result = cobs_decode(ProcessArray, sizeof(ProcessArray), ReciveArray, i);
            
            unsigned char CS = CRC8_PDU_MCS_BMM(ProcessArray, result.out_len-2);
            
            if(ProcessArray[result.out_len-2] == CS){
                PacketRecived_PDU_MCS_BMM = true;
                ComController_PDU_MCS_BMM(ProcessArray,result.out_len);
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

void ComController_PDU_MCS_BMM(unsigned char *DTI, unsigned int lenth){
    if(DTI[1] == READ_TABLE){
        unsigned char DataToSend[4];
        //GetDataDict(DTI[2], DTI[3], DataToSend, DTI[4]);
        //RS485_1_Direction = TALK;// = TALK;  //RS485 set to talk
        //Delay(5);
        //sendData(ECU_ADDRESS, 1, 1, 1, DataToSend, DTI[4]);
        //Delay(3);
        //RS485_1_Direction = LISTEN;  ///RS485 set to listen
    }
}

unsigned char CRC8_PDU_MCS_BMM(const unsigned char * data, unsigned char len) {
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

bool RecivedValidPacket_PDU_MCS_BMM(void){
    return PacketRecived_PDU_MCS_BMM;
}