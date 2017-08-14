#include "CarDataDictionary.h"

unsigned char DataTableArrayZeroConfig[12];
unsigned char DataTableArrayTwoSAS[8];

unsigned char GetDataDict(unsigned char DataTable, unsigned char DataTableIndex, unsigned char *DataArray, unsigned char numbofbytes){
    unsigned char Error = 0;
    unsigned char DataCount = 0;
    unsigned char ReturnCounter = 0;
    switch(DataTable){
        case 0:
            DataCount = DataTableIndex + numbofbytes;
            for(DataTableIndex;DataTableIndex<DataCount;DataTableIndex++){
                DataArray[ReturnCounter] = DataTableArrayZeroConfig[DataTableIndex];
                ReturnCounter++;
            }
            break;
        case 2:
            DataCount = DataTableIndex + numbofbytes;
            for(DataTableIndex;DataTableIndex<DataCount;DataTableIndex++){
                DataArray[ReturnCounter] = DataTableArrayTwoSAS[DataTableIndex];
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
                DataTableArrayZeroConfig[DataTableIndex] = DataArray[ReturnCounter];
                ReturnCounter++;
            }
            break;
        case 2:
            DataCount = DataTableIndex + numbofbytes;
            for(DataTableIndex;DataTableIndex<DataCount;DataTableIndex++){
                DataTableArrayTwoSAS[DataTableIndex] = DataArray[ReturnCounter];
                ReturnCounter++;
            }
            break;
        default:
            Error = -1;
    }
    return Error;
}