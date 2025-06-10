#include <LPC21xx.H>
#include "keyboard.h"
#include "led.h" 
#include "timer_interrups.h"

#define Detector (1<<10) 

enum ServoState {CALLIB, IDLE, IN_PROGRESS};
enum DetectorState {ACTIVE,INACTIVE};

struct Servo{
  enum ServoState eState; 
	unsigned int uiCurrentPosition; // aktl pozycja
	unsigned int uiDesiredPosition; // pozycja do ktorej dazy
}; struct Servo sServo;

void DetectorInit(){
	IO0DIR = IO0DIR &(~Detector); //0 wejscie
}          


enum DetectorState eReadDetector() {
	if ((IO0PIN & Detector)== 0 ){
		return ACTIVE;
	} else {
		return INACTIVE;
	}	
}

void Automat(void){
	switch(sServo.eState){
		case CALLIB: 
			if (eReadDetector()== INACTIVE){
				LedStepLeft();
			} else {
				sServo.uiCurrentPosition = 0; 
				sServo.uiDesiredPosition = 0; 
				sServo.eState = IDLE;
			}
			break;
		case IDLE:
			if (sServo.uiCurrentPosition != sServo.uiDesiredPosition){
				sServo.eState = IN_PROGRESS;
			} else {
				sServo.eState = IDLE;
			}
			break; 
		case IN_PROGRESS:
			if (sServo.uiCurrentPosition < sServo.uiDesiredPosition){
				LedStepLeft();
				sServo.uiCurrentPosition ++;
			}else if (sServo.uiCurrentPosition > sServo.uiDesiredPosition){
				LedStepRight();
				sServo.uiCurrentPosition --;
      }else {
				sServo.eState = IDLE;
			}
			break;
		}
}

void ServoInit(unsigned int uiServoFrequency){
	DetectorInit();
	LedInit();
	Timer0Interrupts_Init((1000000/uiServoFrequency),&Automat);	
	
}
void ServoCallib(void){
	sServo.eState = CALLIB;
}

void ServoGoTo(unsigned int uiPosition){
  sServo.uiDesiredPosition = uiPosition;
}
