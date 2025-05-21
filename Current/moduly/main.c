#include <LPC21xx.H>
#include "keyboard.h"
#include "led.h"

void Delay(int iMilliSec) {
    int iLimitSeconds;
    int iCounter;
    
    for (iCounter = 0; iCounter < iMilliSec; iCounter++) {
        for (iLimitSeconds = 0; iLimitSeconds < 1500; iLimitSeconds++) {
        }
    }
}

int main(){
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


