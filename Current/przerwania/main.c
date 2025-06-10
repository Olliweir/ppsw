#include "led.h"
#include "timer_interrups.h" 
#include "keyboard.h" 

void Automat(){
	enum LedState{LED_RIGHT,LED_LEFT, LED_STOP};
  static enum LedState eLedState = LED_STOP;
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
	}
	
int main (){
	
	unsigned int iMainLoopCtr;
  LedInit();
	KeyboardInit();
	Timer0Interrupts_Init(100000,&Automat);// w mikroseconds &LedStepLeft bierzesz adres
	
	 while(1){
	 	iMainLoopCtr++;
		iMainLoopCtr++;
		iMainLoopCtr++;
		iMainLoopCtr++;
		iMainLoopCtr++;
	}	
}
