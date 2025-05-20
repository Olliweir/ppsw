#include <LPC21xx.H>
 

#define LED0_bm 0x10000  
#define LED1_bm 0x20000  
#define LED2_bm 0x40000 
#define LED3_bm 0x80000 

#define S0_bm 0x10       
#define S1_bm 0x40       
#define S2_bm 0x20       
#define S3_bm 0x80       

void Delay(int iMilliSec) {
    int iLimitSeconds;
    int iCounter;
    
    for (iCounter = 0; iCounter < iMilliSec; iCounter++) {
        for (iLimitSeconds = 0; iLimitSeconds < 1500; iLimitSeconds++) {
        }
    }
}


void LedInit() {
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


enum KeyboardState { RELEASED, BUTTON_0, BUTTON_1, BUTTON_2, BUTTON_3 };


enum KeyboardState eKeyboardRead() {
    if (!(IO0PIN & S0_bm)) {
        return BUTTON_0;
    } else if (!(IO0PIN & S1_bm)) {
        return BUTTON_1;
    } else if (!(IO0PIN & S2_bm)) {
        return BUTTON_2;
    } else if (!(IO0PIN & S3_bm)) {
        return BUTTON_3;
    }
    return RELEASED;
}


void KeyboardInit() {
    IO0DIR &= ~(S0_bm | S1_bm | S2_bm | S3_bm);
}



enum LedDirection { Right, Left };


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
void LedStepRight(){
	LedStep(Right);
}
 
void LedStepLeft(){
	LedStep(Left);
}


int main() {
	LedInit();
	KeyboardInit();
	
	while(1){
			Delay(500);
		switch (eKeyboardRead()){
			case BUTTON_1:
				LedStepRight();
			break;
			case BUTTON_2:
				LedStepLeft();
			break;
			default:
				break;
		}
	}
}
