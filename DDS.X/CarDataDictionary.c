#include "CarDataDictionary.h"
#include "UART.h"
#include "Function.h"

unsigned char DataTableArrayOne[10];
unsigned char DataTableArrayTwo[3];

unsigned char GetDataDict(unsigned char DataTable, unsigned char DataTableIndex, unsigned char *DataArray, unsigned char numbofbytes){
    unsigned char Error = 0;
    unsigned char DataCount = 0;
    unsigned char ReturnCounter = 0;
    switch(DataTable){
        case 0:
            DataCount = DataTableIndex + numbofbytes;
            for(DataTableIndex;DataTableIndex<DataCount;DataTableIndex++){
                DataArray[ReturnCounter] = DataTableArrayOne[DataTableIndex];
                ReturnCounter++;
            }
            break;
        case 1:
            DataCount = DataTableIndex + numbofbytes;
            for(DataTableIndex;DataTableIndex<DataCount;DataTableIndex++){
                DataArray[ReturnCounter] = DataTableArrayTwo[DataTableIndex];
                ReturnCounter++;
            }
            break;
        default:
            Error = -1;
    }
    return Error;
}

unsigned char SetDataDict(unsigned char DataTable, unsigned char DataTableIndex, unsigned char *DataArray, unsigned char numbofbytes){
    unsigned char Error = 0;
    unsigned char DataCount = 0;
    unsigned char ReturnCounter = 0;
    switch(DataTable){
        case 0:
            DataCount = DataTableIndex + numbofbytes;
            for(DataTableIndex;DataTableIndex<DataCount;DataTableIndex++){
                DataTableArrayOne[DataTableIndex] = DataArray[ReturnCounter];
                ReturnCounter++;
            }
            break;
        case 1:
            DataCount = DataTableIndex + numbofbytes;
            for(DataTableIndex;DataTableIndex<DataCount;DataTableIndex++){
                DataTableArrayTwo[DataTableIndex] = DataArray[ReturnCounter];
                ReturnCounter++;
            }
            break;
        default:
            Error = -1;
    }
    return Error;
}