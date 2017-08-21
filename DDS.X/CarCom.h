/* 
 * File:   FastTransfer.h
 * Author: Igor
 * Revised May 28, 2015 Zac Kilburn
 * Created on March 23, 2015, 1:21 PM
 */

#ifndef CARCOM_H
#define	CARCOM_H


void sendData(unsigned char whereToSend, unsigned char ComandByte, unsigned char DataTable, unsigned char DataTableIndex, unsigned char *DTS, unsigned int lenth);
bool receiveData();
void ComController(unsigned char *DTS, unsigned int lenth);

#endif	/* FASTTRANSFER_H */

