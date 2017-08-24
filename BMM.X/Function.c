#include "Function.h"
#include "timers.h"
#include "Communications.h"
#include "BatteryManagment.h"
#include "spi2.h"
#include "UART1.h"
#include "PinDef.h"
void Setup(void) {
    PinSetMode();
   // INDICATOR = 1;
    FaultValue=0;
    // setup internal clock for 72MHz/36MIPS
    // 12 /3 = 4  *32 = 128 / 2=64
    CLKDIVbits.PLLPRE = 0x01; // PLLPRE (N2) 0=/2c
    CLKDIVbits.DOZE = 0;
    PLLFBD = 0x1E; // pll multiplier (M) = +2
    CLKDIVbits.PLLPOST = 0x00; // PLLPOST (N1) 0=/2 
    // Initiate Clock Switch to Primary Oscillator with PLL (NOSC = 0b011)
    __builtin_write_OSCCONH(0x03);
    __builtin_write_OSCCONL(OSCCON | 0x01);
    // Wait for Clock switch to occur
    while (OSCCONbits.COSC != 0b011);
    while (!OSCCONbits.LOCK); // wait for PLL ready
    TRISBbits.TRISB9=0;
    TRISBbits.TRISB8=0;
    TRISBbits.TRISB7=0;
    IEC1bits.INT1IE=1;
    TRISCbits.TRISC8 = 0;
    TRISCbits.TRISC9 = 1;

    PPSUnLock;
    PPSout(_U1TX, _RP24);
    PPSin(_U1RX, _RP25);
    PPSout(_U2TX, _RP22);
    PPSin(_U2RX, _RP23);
    PPSout(_SDO1, _RP21);
    PPSout(_SCK1, _RP19);
    PPSin(_SDI1, _RP20);
    PPSLock;

    
    initTimerOne();
    CommStart();
    UART1_init();
    //initTimerTwo();
}

void Delay(int wait) {
    int x;
    for (x = 0; x < wait; x++) {
        delay_ms(1); //using predif fcn
    }
}

void PinSetMode(void) {
    AD1PCFGL = 0XFFFF;
    TRISBbits.TRISB1 = OUTPUT; //Set LED as output
    TRISBbits.TRISB5 = OUTPUT; //BMS Slave Turn on
    TRISBbits.TRISB6 = OUTPUT; //Fan control OUT
    TRISAbits.TRISA4 = OUTPUT;
    TRISAbits.TRISA7 = OUTPUT;
    TRISAbits.TRISA8 = OUTPUT;
    TRISBbits.TRISB7 = OUTPUT; // RS485 Direction Pin OUTPUT
    LATBbits.LATB6 = 1; 
    LATBbits.LATB7 = 0;
    //SS CLEAR AND SET
    TRISAbits.TRISA1=OUTPUT;
    TRISBbits.TRISB0=OUTPUT;
    TRISBbits.TRISB2 = OUTPUT;
    TRISBbits.TRISB3 = OUTPUT;
    TRISAbits.TRISA9= OUTPUT;
    TRISBbits.TRISB4 = OUTPUT;
    TRISCbits.TRISC7 = OUTPUT;
    TRISCbits.TRISC6 = INPUT;
    //LATCbits.LATC6=1;
    //LATCbits.LATC7=1;
    BMS_TURN_ON = 1;
}

 void ledDebug() {
    if (time_get(LEDTM) > 500) {
        INDICATOR = !INDICATOR;
        time_Set(LEDTM, 0);
    }
}