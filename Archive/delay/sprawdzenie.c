#define NULL '\0'
	
char pcStringSource[] = "Hello";
char pcStringDestination[6] = "XXXXXX";

void CopyString(char pcSource[], char pcDestination[]){
	
	unsigned char ucSignCounter;
	
	for(ucSignCounter		= 0; pcSource[ucSignCounter] != NULL ; ucSignCounter = ucSignCounter +1 ){
		
	pcDestination[ucSignCounter] = pcSource[ucSignCounter];
	}
  pcDestination[ucSignCounter] = NULL;
}
	

int main() {
	
	CopyString(pcStringSource, pcStringDestination);
	
	return 0;
}