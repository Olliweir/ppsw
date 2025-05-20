#include <LPC21xx.H>

#define NULL '\0'

void CopyString(char pcSource[], char pcDestination[]){
	
	unsigned char ucSignCounter;
	
	for(ucSignCounter = 0; pcSource[ucSignCounter] != NULL ; ucSignCounter++){
		
		pcDestination[ucSignCounter] = pcSource[ucSignCounter];
	}
	pcDestination[ucSignCounter] = NULL;
}

enum CompResult {DIFFERENT, EQUAL};
enum CompResult eCompareString(char pcStr1[], char pcStr2[]){
	
	unsigned char ucSignCounter; 
	
	for(ucSignCounter = 0; (pcStr1[ucSignCounter] !=NULL) || (pcStr2[ucSignCounter] != NULL); ucSignCounter++){
		
		if (pcStr1[ucSignCounter] != pcStr2[ucSignCounter]){
			
			return DIFFERENT;
		}
	}
	return EQUAL;
}


void AppendString (char pcSourceStr[], char pcDestinationStr[]){

    unsigned char ucSignCounter ;

    for(ucSignCounter = 0 ; pcDestinationStr[ucSignCounter] != NULL ; ucSignCounter++){}
    CopyString(pcSourceStr, pcDestinationStr + ucSignCounter);
}


void ReplaceCharactersInString(char pcString[], char cOldChar, char cNewChar){

    unsigned char ucSignCounter;

    for(ucSignCounter = 0 ; pcString[ucSignCounter] != NULL; ucSignCounter++){
        if(pcString[ucSignCounter] == cOldChar){
					
            pcString[ucSignCounter] = cNewChar;  
        }
    }
}