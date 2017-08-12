

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef CARDATADICTIONARY_H
#define	CARDATADICTIONARY_H

unsigned char GetDataDict(unsigned char DataTable, unsigned char DataTableIndex, unsigned char *DataArray, unsigned char numbofbytes);
unsigned char SetDataDict(unsigned char DataTable, unsigned char DataTableIndex, unsigned char *DataArray, unsigned char numbofbytes);

#endif	/* XC_HEADER_TEMPLATE_H */

