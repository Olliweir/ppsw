#include <LPC21xx.H>


void Delay (int iMilliSec){
	//int iLimitSeconds;
	int iCounter = iMilliSec; 
	
	for (iCounter = 0; iCounter != iMilliSec ; iCounter ++){
	}		
}
	
int main() 
 
{
	 IO1DIR = 0x00010000 ;  
	
   IO1SET = 0x00010000 ;
	 Delay(1000);
	 IO1CLR = 0x00010000 ;
	

		
}