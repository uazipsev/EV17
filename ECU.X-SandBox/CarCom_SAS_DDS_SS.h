/* 
 * File:   FastTransfer1.h
 * Author: Zac Kilburn
 *
 * Created on May 31, 2015, 2:09 PM
 */

#ifndef FASTTRANSFER1_H
#define	FASTTRANSFER1_H

void sendData1(unsigned char whereToSend, unsigned char ComandByte, unsigned char DataTable, unsigned char DataTableIndex, unsigned char *DTS, unsigned int lenth);
bool receiveData1();
void ComController1(unsigned char *DTI, unsigned int lenth);

#define polynomial 0x8C  //polynomial used to calculate crc

#endif	/* FASTTRANSFER1_H */

