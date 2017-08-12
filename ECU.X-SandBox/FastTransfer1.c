/*
 * File:   FastTransfer1.c
 * Author: Zac Kilburn
 *
 * Created on May 31, 2015
 */

#include <xc.h>
#include <stdbool.h>
#include <stdlib.h>
#include "FastTransfer1.h"
#include "UART1.h"
#include "ADDRESSING.h"
#include "PinDef.h"

#include "COBS.h"

//volatile int receiveArray1[20];

////INTERNAL METHODS/VARIABLES HERE
//unsigned char AKNAK1(unsigned char module);
//unsigned int alignError1(void);
//unsigned int CRCError1(void);
//unsigned int addressError1(void);
//unsigned int dataAddressError1(void);
//void (*serial_write1)(unsigned char);
//unsigned char (*serial_read1)(void);
//int (*serial_available1)(void);
//unsigned char (*serial_peek1)(void);
//unsigned char rx_buffer1[RX_BUFFER_SIZE1]; //address for temporary storage and parsing buffer
//unsigned char rx_array_inx1; //index for RX parsing buffer
//unsigned char rx_len1; //RX packet length according to the packet
//unsigned char calc_CS1; //calculated Checksum
//unsigned char moduleAddress1; // the address of this module
//unsigned char returnAddress1; //the address to send the crc back to
//unsigned char maxDataAddress1; //max address allowable
//volatile int * receiveArrayAddress1; // this is where the data will go when it is received
//unsigned char * sendStructAddress1; // this is where the data will be sent from
//bool AKNAKsend1; // turns the acknowledged or not acknowledged on/off
//unsigned int alignErrorCounter1; //counts the align errors
//unsigned int crcErrorCounter1; // counts any failed crcs
//unsigned int addressErrorCounter1; // counts every time a wrong address is received
//unsigned int dataAdressErrorCounter1; // counts if the received data fall outside of the receive array
//unsigned char rx_address1; //RX address received

//struct ringBufS1 { // this is where the send data is stored before sending
//    unsigned char buf[BUFFER_SIZE];
//    int head;
//    int tail;
//    int count;
//};
//struct ringBufS1 ring_buffer1;
//
//union stuff1 { // this union is used to join and disassemble integers
//    unsigned char parts[2];
//    unsigned int integer;
//};
//union stuff1 group1;
//
//struct crcBufS1 { // this is where the address where sent to, the sent crc, the status of the AKNAK
//    unsigned char buf[CRC_BUFFER_SIZE];
//    int head;
//};
//struct crcBufS1 crc_buffer1;

unsigned char CRC81(const unsigned char * data, unsigned char len);

//void FastTransfer_buffer_flush1(struct ringBufS1* _this, const int clearBuffer);
//unsigned int FastTransfer_buffer_modulo_inc1(const unsigned int value, const unsigned int modulus);
//void crcBufS_put1(struct crcBufS1* _this, unsigned char address, unsigned char oldCRC, unsigned char status);
//void crcBufS_status_put1(struct crcBufS1* _this, unsigned char time, unsigned char status);
//unsigned char crcBufS_get1(struct crcBufS1* _this, unsigned char time, unsigned char space);
//void CRCcheck1(void);
//
//void StartFastTransfer1(){
//    begin1(receiveArray1, sizeof (receiveArray1), ECU_ADDRESS, false, Send_put1, Receive_get1, Receive_available1, Receive_peek1);
//}
//
//unsigned int ReceiveArray1Get(unsigned char location){
//    return receiveArray1[location];
//}

//void wipeRxBuffer1(void)
//{
//	int i=0;
//	for(i=0;i<RX_BUFFER_SIZE1;i++)
//	{
//		rx_buffer1[i]=0;
//		
//	}
//	
//}

//Captures address of receive array, the max data address, the address of the module, true/false if AKNAKs are wanted and the Serial address

//void begin1(volatile int * ptr, unsigned char maxSize, unsigned char givenAddress, bool error, void (*stufftosend)(unsigned char), unsigned char (*stufftoreceive)(void), int (*stuffavailable)(void), unsigned char (*stuffpeek)(void)) {
//    receiveArrayAddress1 = ptr;
//    moduleAddress1 = givenAddress;
//    serial_write1 = stufftosend;
//    serial_available1 = stuffavailable;
//    serial_peek1 = stuffpeek;
//    serial_read1 = stufftoreceive;
//    maxDataAddress1 = maxSize / 2;
//    sendStructAddress1 = (unsigned char*) & ring_buffer1;
//    AKNAKsend1 = error;
//    alignErrorCounter1 = 0;
//
//}

//CRC Calculator



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