#include "konwersje.h"

#define NIBBLE_bm 0xF 

typedef enum Result{OK, ERROR} Result;


void CopyString(char pcSource[], char pcDestination[]){
	
		unsigned char ucSignCounter;
	
		for(ucSignCounter = 0; '\0' != pcSource[ucSignCounter]; ucSignCounter ++){
				pcDestination[ucSignCounter] = pcSource[ucSignCounter];
		}
		pcDestination[ucSignCounter] = '\0';
}


//enum CompResult { DIFFERENT , EQUAL };

enum CompResult eCompareString(char pcStr1[], char pcStr2[]){
	
		unsigned char ucSignCounter;
	
		for(ucSignCounter = 0; ('\0' != pcStr1[ucSignCounter]) || ('\0' != pcStr2[ucSignCounter]);ucSignCounter++){
				
				if(pcStr1[ucSignCounter] != pcStr2[ucSignCounter]){
						return DIFFERENT;
				}
		}
		return EQUAL;
}


void AppendString (char pcSourceStr[],char pcDestinationStr[]){
	
		unsigned char ucSignCounter;
	
		for(ucSignCounter = 0; '\0' != pcDestinationStr[ucSignCounter]; ucSignCounter++){}
		CopyString(pcSourceStr, pcDestinationStr + ucSignCounter);
}


void ReplaceCharactersInString(char pcString[],char cOldChar,char cNewChar){
	
		unsigned char ucSignCounter;
	
		for(ucSignCounter = 0; '\0' != pcString[ucSignCounter]; ucSignCounter++){
			
				if(cOldChar == pcString[ucSignCounter]){
						pcString[ucSignCounter] = cNewChar;
				}
		}
}

void UIntToHexStr (unsigned int uiValue, char pcStr[]){ 
     
    unsigned char ucNibbleCounter; 
    unsigned char ucCurrentCharacter; 
     
    pcStr[0] = '0'; 
    pcStr[1] = 'x'; 
     
    for(ucNibbleCounter = 0; ucNibbleCounter < 4; ucNibbleCounter ++){ 
         
        ucCurrentCharacter = ((uiValue >> (12 - 4 * ucNibbleCounter)) & NIBBLE_bm); 
         
        if(ucCurrentCharacter < 10){ 
            pcStr[2 + ucNibbleCounter] = ('0' + ucCurrentCharacter); 
        } 
        else{ 
            pcStr[2 + ucNibbleCounter] = ('A' + (ucCurrentCharacter-10)); 
        } 
    } 
    pcStr[6] = '\0'; 
} 

 
enum Result eHexStringToUInt(char pcStr[],unsigned int *puiValue){ 
     
    unsigned char ucCharacterCounter; 
    unsigned char ucCurrentCharacter; 
   
    if(('0' != pcStr[0]) || ('x' != pcStr[1]) || ('\0' == pcStr[2])){ 
        return ERROR; 
    } 
   
    *puiValue = 0; 
      
		for(ucCharacterCounter = 2; '\0' != pcStr[ucCharacterCounter]; ucCharacterCounter ++){  
        
				if(6 <= ucCharacterCounter){
						return ERROR;
				}
			
        ucCurrentCharacter = pcStr[ucCharacterCounter]; 
         
        if(('0' <= ucCurrentCharacter) && ('9' >= ucCurrentCharacter)){ 
            ucCurrentCharacter = ucCurrentCharacter - '0'; 
        } 
        else if(('A' <= ucCurrentCharacter) && ('F' >= ucCurrentCharacter)){ 
            ucCurrentCharacter = ucCurrentCharacter -'A'+10; 
        } 
        else{ 
            return ERROR; 
        } 
				*puiValue <<= 4; 
        *puiValue |= ucCurrentCharacter; 
    } 
    return OK; 
} 
 
 
void AppendUIntToString (unsigned int uiValue, char pcDestinationStr[]){ 
     
    unsigned char ucCharacterCounter; 
     
    for(ucCharacterCounter = 0; '\0' != pcDestinationStr[ucCharacterCounter]; ucCharacterCounter ++){} 
    UIntToHexStr(uiValue, &pcDestinationStr[ucCharacterCounter]); 
}
