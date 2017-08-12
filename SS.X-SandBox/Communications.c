#include <stdbool.h>
#include <xc.h>
#include "CarCom.h"
#include "Communications.h"
#include "ADDRESSING.h"
#include "PinDef.h"
#include "Function.h"
#include "UART.h"

char receiveArray[10];

void ComStart(){
    EUSART1_Initialize();  //Config USART  
}

void updateComms() {
    if (receiveData()) {  // If data is here for us 
        //INDICATOR ^= 1;
    }
}




