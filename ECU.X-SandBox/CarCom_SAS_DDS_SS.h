/* 
 * File:   FastTransfer1.h
 * Author: Zac Kilburn
 *
 * Created on May 31, 2015, 2:09 PM
 */

#ifndef FASTTRANSFER1_H
#define	FASTTRANSFER1_H

unsigned char CRC8_SAS_DDS_SS(const unsigned char * data, unsigned char len);
void sendData_SAS_DDS_SS(unsigned char whereToSend, unsigned char ComandByte, unsigned char DataTable, unsigned char DataTableIndex, unsigned char *DTS, unsigned int lenth);
bool receiveData_SAS_DDS_SS();
void ComController_SAS_DDS_SS(unsigned char *DTI, unsigned int lenth);
bool RecivedValidPacket_SAS_DDS_SS(void);

#endif	/* FASTTRANSFER1_H */

