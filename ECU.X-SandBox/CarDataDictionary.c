#include "CarDataDictionary.h"

unsigned char DataTableArrayZeroConfig[12];
unsigned char DataTableArrayOneSS[3];
unsigned char DataTableArrayTwoSAS[6];
unsigned char DataTableArrayThreeDDS[6];
unsigned char DataTableArrayFourPDU[10];
unsigned char DataTableArrayFiveBMM[20];
unsigned char DataTableArraySixMCU[10];

unsigned char GetDataDict(unsigned char DataTable, unsigned char DataTableIndex, unsigned char *DataArray, unsigned char numbofbytes){
    unsigned char Error = 0;
    unsigned char DataCount = 0;
    unsigned char ReturnCounter = 0;
    switch(DataTable){
        case 0:
            DataCount = DataTableIndex + numbofbytes;
            for(;DataTableIndex<DataCount;DataTableIndex++){
                DataArray[ReturnCounter] = DataTableArrayZeroConfig[DataTableIndex];
                ReturnCounter++;
            }
            break;
        case 1:
            DataCount = DataTableIndex + numbofbytes;
            for(;DataTableIndex<DataCount;DataTableIndex++){
                DataArray[ReturnCounter] = DataTableArrayOneSS[DataTableIndex];
                ReturnCounter++;
            }
            break;
        case 2:
            DataCount = DataTableIndex + numbofbytes;
            for(;DataTableIndex<DataCount;DataTableIndex++){
                DataArray[ReturnCounter] = DataTableArrayTwoSAS[DataTableIndex];
                ReturnCounter++;
            }
            break;
        case 3:
            DataCount = DataTableIndex + numbofbytes;
            for(;DataTableIndex<DataCount;DataTableIndex++){
                DataArray[ReturnCounter] = DataTableArrayThreeDDS[DataTableIndex];
                ReturnCounter++;
            }
            break;
        case 4:
            DataCount = DataTableIndex + numbofbytes;
            for(;DataTableIndex<DataCount;DataTableIndex++){
                DataArray[ReturnCounter] = DataTableArrayFourPDU[DataTableIndex];
                ReturnCounter++;
            }
            break;
        case 5:
            DataCount = DataTableIndex + numbofbytes;
            for(;DataTableIndex<DataCount;DataTableIndex++){
                DataArray[ReturnCounter] = DataTableArrayFiveBMM[DataTableIndex];
                ReturnCounter++;
            }
            break;
        case 6:
            DataCount = DataTableIndex + numbofbytes;
            for(;DataTableIndex<DataCount;DataTableIndex++){
                DataArray[ReturnCounter] = DataTableArraySixMCU[DataTableIndex];
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
            for(;DataTableIndex<DataCount;DataTableIndex++){
                DataTableArrayZeroConfig[DataTableIndex] = DataArray[ReturnCounter];
                ReturnCounter++;
            }
            break;
        case 1:
            DataCount = DataTableIndex + numbofbytes;
            for(;DataTableIndex<DataCount;DataTableIndex++){
                DataTableArrayOneSS[DataTableIndex] = DataArray[ReturnCounter];
                ReturnCounter++;
            }
            break;
        case 2:
            DataCount = DataTableIndex + numbofbytes;
            for(;DataTableIndex<DataCount;DataTableIndex++){
                DataTableArrayTwoSAS[DataTableIndex] = DataArray[ReturnCounter];
                ReturnCounter++;
            }
            break;
        case 3:
            DataCount = DataTableIndex + numbofbytes;
            for(;DataTableIndex<DataCount;DataTableIndex++){
                DataTableArrayThreeDDS[DataTableIndex] = DataArray[ReturnCounter];
                ReturnCounter++;
            }
            break;
        case 4:
            DataCount = DataTableIndex + numbofbytes;
            for(;DataTableIndex<DataCount;DataTableIndex++){
                DataTableArrayFourPDU[DataTableIndex] = DataArray[ReturnCounter];
                ReturnCounter++;
            }
            break;
        case 5:
            DataCount = DataTableIndex + numbofbytes;
            for(;DataTableIndex<DataCount;DataTableIndex++){
                DataTableArrayFiveBMM[DataTableIndex] = DataArray[ReturnCounter];
                ReturnCounter++;
            }
            break;
        case 6:
            DataCount = DataTableIndex + numbofbytes;
            for(;DataTableIndex<DataCount;DataTableIndex++){
                DataTableArraySixMCU[DataTableIndex] = DataArray[ReturnCounter];
                ReturnCounter++;
            }
            break;
        default:
            Error = -1;
    }
    return Error;
}