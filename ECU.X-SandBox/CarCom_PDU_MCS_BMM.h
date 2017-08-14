/* 
 * File:   FastTransfer.h
 * Author: Igor
 * Revised May 28, 2015 Zac Kilburn
 * Created on March 23, 2015, 1:21 PM
 */

#ifndef FASTTRANSFER_H
#define	FASTTRANSFER_H

unsigned char CRC8_PDU_MCS_BMM(const unsigned char * data, unsigned char len);
void sendData_PDU_MCS_BMM(unsigned char whereToSend, unsigned char ComandByte, unsigned char DataTable, unsigned char DataTableIndex, unsigned char *DTS, unsigned int lenth);
bool receiveData_PDU_MCS_BMM();
void ComController_PDU_MCS_BMM(unsigned char *DTI, unsigned int lenth);

#endif	/* FASTTRANSFER_H */

