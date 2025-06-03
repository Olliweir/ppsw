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
enum LedState{LED_RIGHT,LED_LEFT, LED_STOP};
enum LedState eLedState = LED_STOP;
//unsigned int ucCounter ;
int main(){ 
	LedInit();
	KeyboardInit();


//--------------- zadanie 6 
while(1){
	
	switch(eLedState){
			case LED_RIGHT: 
				if (BUTTON_1 == eKeyboardRead()){
					eLedState = LED_STOP;
					} else {
						LedStepRight();
					}
					break;
			case LED_LEFT: 
				if (BUTTON_1 == eKeyboardRead()){
					eLedState = LED_STOP;
					} else {
						LedStepLeft();
					}
					break;
			case LED_STOP:
				if (BUTTON_2 == eKeyboardRead()){
					eLedState = LED_RIGHT;	
				}
				else if (BUTTON_0 == eKeyboardRead()){
					eLedState = LED_LEFT;	
				}
				break;
			default:
				break;
		}
		Delay(250);
	}
}
	






//---------- zadanie 5 
/*
while(1){
	
	
	KeyboardInit();
	LedInit();
	
	switch(eLedState){
		case LED_RIGHT:
			; 
			LedStepRight();
      if (BUTTON_0 == eKeyboardRead()){
		  } else {
			eLedState = LED_STOP;
		  }
		break;
		case LED_STOP:
			if (BUTTON_1 == eKeyboardRead()){
				eLedState = LED_RIGHT;	
			}
		break;
}
Delay(500);
}
}
*/

//---------zadanie 4
/*
while(1){
	
	
	KeyboardInit();
	LedInit();
	
	switch(eLedState){
		case LED_RIGHT:
			ucCounter++; 
			LedStepRight();
			if (3<=ucCounter){
		eLedState = LED_STOP;
		}
		break;
		case LED_STOP:
			if (BUTTON_0 == eKeyboardRead()){
				ucCounter = 0 ;
				eLedState = LED_RIGHT;	
			}
		break;
}
Delay(500);
}
}
*/

//--------------zadanie 3 
/* 
while(1){
	
	
	KeyboardInit();
	LedInit();
	
	switch(eLedState){
		case LED_LEFT:
			ucCounter++; 
			LedStepLeft();
		if (3<=ucCounter){
		eLedState = LED_RIGHT;
		}
		break;
		case LED_RIGHT:
			ucCounter-- ; 
			LedStepRight();
		if (0>=ucCounter){
		eLedState = LED_LEFT;
		}
		break;
}
Delay(1000);

}
}*/
