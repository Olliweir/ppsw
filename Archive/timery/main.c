#include <LPC21xx.H>

#include "led.h"
#include "timer.h"

int main(){
	
		LedInit();
		//InitTimer0Match0(300000);
	  InitTimer0();
	
		while(1){
			
				LedStepRight();
				
				//WaitOnTimer0Match0();
			  WaitOnTimer0(300000);
		}
}
	

	







