#include <LPC21xx.H>
#include "led.h"

#define LED0_bm (1<<16)  
#define LED1_bm (1<<17)
#define LED2_bm (1<<18) 
#define LED3_bm (1<<19)

enum LedDirection { Right, Left };

void LedInit(void) {
    IO1DIR |= (LED0_bm | LED1_bm | LED2_bm | LED3_bm);
    IO1CLR = LED0_bm | LED1_bm | LED2_bm | LED3_bm;
    IO1SET = LED0_bm;
}
void LedOn(unsigned char ucLedIndeks) {
    IO1CLR = LED0_bm | LED1_bm | LED2_bm | LED3_bm;
    switch (ucLedIndeks) {
        case 0:
            IO1SET = LED0_bm;
            break;
        case 1:
            IO1SET = LED1_bm;
            break;
        case 2:
            IO1SET = LED2_bm;
            break;
        case 3:
            IO1SET = LED3_bm;
            break;
        case 4:
            break;
    }
}

void LedStep(enum LedDirection Direction) {
	static unsigned int LedCounter = 0 ;
    if (Direction == Right) {
        LedCounter = (LedCounter + 3) % 4; 
    } 
		else if (Direction == Left )  {
        LedCounter = (LedCounter + 1) % 4; 
    }
    LedOn(LedCounter);
}
void LedStepRight(void){
	LedStep(Right);
}
 
void LedStepLeft(void){
	LedStep(Left);
}

