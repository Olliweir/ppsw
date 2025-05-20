#include <LPC21xx.H>


void Delay (int iMilliSec){
	int iLimitSeconds;
	int iCounter ; 
	
	for (iCounter = 0; iCounter < iMilliSec ; iCounter ++){
		for (iLimitSeconds =0; iLimitSeconds <1500; iLimitSeconds++){
		}
	}		
}
	
int main() {
	
IO1DIR = 0x10000;
while(1){
	 
	 Delay(1000);
   IO1SET = 0x10000 ;
	 Delay(1000);
	 IO1CLR = 0x10000;
	 
}


		
}
