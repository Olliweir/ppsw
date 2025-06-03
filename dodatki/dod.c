int main(){
	
		enum LedState{STATE_STOP, STATE_RIGHT, STATE_LEFT, STATE_WIPER};
		enum LedState eLedState = STATE_RIGHT;

		unsigned char ucWiperCounter = 0;

		LedInit();
		KeyboardInit();

		while(1){
				
				Delay(100);
				
				switch(eLedState){
					
						case STATE_RIGHT:
								if(eKeyboardRead() == BUTTON_1){
										eLedState = STATE_STOP;
								}
								else{
										LedStepRight();
										eLedState = STATE_RIGHT;
								}
								break;								
								
						case STATE_LEFT:
								if(eKeyboardRead() == BUTTON_1){
										eLedState = STATE_STOP;
								}
								else if(eKeyboardRead() == BUTTON_3){
									
										eLedState = STATE_WIPER;
										ucWiperCounter = 0;
								}
								else{
										LedStepLeft();
										eLedState = STATE_LEFT;
								}
								break;
						
						case STATE_STOP:
								if(eKeyboardRead() == BUTTON_0){
										eLedState = STATE_LEFT;
								}
								else if(eKeyboardRead() == BUTTON_2){
										eLedState = STATE_RIGHT;
								}
								else{
										eLedState = STATE_STOP;
								}
								break;
								
						case STATE_WIPER:
								if(ucWiperCounter == 4){
									
										eLedState = STATE_RIGHT;
								}
								else{
		
										if((ucWiperCounter % 2) == 0){
												LedStepRight();
										}
										else{
												LedStepLeft();
										}
										ucWiperCounter ++;
										eLedState = STATE_WIPER;
								}
								break;
								
						default:
								break;
						
				}
		}
}		
int main(void) {
	enum LedState eLedState = LED_STOP;

  LedInit();
  KeyboardInit();

  while(1){
		switch(eLedState){
			case LED_STOP:
				if (eKeyboardRead() == BUTTON_0) {
					eLedState = LED_LEFT;
				}
				else if (eKeyboardRead() == BUTTON_2) {
					eLedState = LED_RIGHT;
				}
				else {
					break;
				}
				break;

			case LED_LEFT:
        if (eKeyboardRead() == BUTTON_1) {
					eLedState = LED_STOP;
        }
				else if (eKeyboardRead() == BUTTON_3){
					eLedState = BLINK;
				}
				else {
					LedStepLeft();
				}
        break;

      case LED_RIGHT:
        if (eKeyboardRead() == BUTTON_1) {
					eLedState = LED_STOP;
        }
				else {
					LedStepRight();
				}
        break;
				
			case BLINK:
				if (ucBlinkCounter == 18) {
					ucBlinkCounter = 0;
					eLedState = LED_RIGHT;
				} else {
					ucBlinkCounter++;
					if ((ucBlinkCounter % 2) == 0) {
							LedOn(3);
					} else {
							LedOn(4);
					}
					eLedState = BLINK;
				}
				break;
    }
    delay(100);