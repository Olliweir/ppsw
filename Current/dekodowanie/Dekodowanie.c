#include "dekod.h"
#include "konwersje.h"


#define MAX_TOKEN_NR 3
#define MAX_KEYWORD_NR 3
#define MAX_KEYWORD_STRING_LTH 10
#define DELIMITER_CHAR ' '

typedef enum {LD, ST, RST} KeywordCode;   //

typedef enum {KEYWORD, NUMBER, STRING} TokenType; 

typedef struct
{ 
KeywordCode eCode;
char cString[MAX_KEYWORD_STRING_LTH + 1];
} Keyword;

Keyword asKeywordList[MAX_KEYWORD_NR]=
{ 
{RST,"reset"},
{LD, "load" }, 
{ST, "store"}
};

typedef union {	
KeywordCode  eKeyword; 
unsigned int uiNumber; 
char*        pcString; 
} TokenValue; 

typedef struct
{ 
TokenType  eType;
TokenValue uValue;
} Token;  


Token asToken[MAX_TOKEN_NR];


typedef enum {TOKEN, DELIMITER} State;

unsigned char ucTokenNr;

typedef enum Result{OK, ERROR} Result;     //



//-------------------------------------------------------------------------fun1

unsigned char ucFindTokensInString (char *pcString){
	
	State eState = DELIMITER;
	
	unsigned char ucCurrentChar;
	unsigned char ucCharCounter;
	unsigned char ucTokenLength;
	
	unsigned char ucTokenNr = 0;
	
	for(ucCharCounter = 0; ; ucCharCounter++){
		
		ucCurrentChar = pcString[ucCharCounter];
		
		switch(eState){
		case(DELIMITER):
			
			if(ucCurrentChar == '\0'){
				return ucTokenNr;
			}
			else if(ucCurrentChar == DELIMITER_CHAR){
				eState = DELIMITER;
			}
			else{
				asToken[ucTokenNr].uValue.pcString = pcString + ucCharCounter;
				ucTokenNr++;
				
				ucTokenLength = 1;
				eState = TOKEN;
			}
			break;
		
		case(TOKEN): 
			
			if(ucCurrentChar == '\0'){
				return ucTokenNr;
			}
			else if(ucCurrentChar == DELIMITER_CHAR){
				eState = DELIMITER;;
			}
			else if(ucTokenLength > MAX_KEYWORD_STRING_LTH){
				return ucTokenNr;
			}
			else{
				ucTokenLength++;
				eState = TOKEN;
			}
			break;
		}
	}
}

//--------------------------------------------------------------------------------fun2
Result eStringToKeyword (char pcStr[],KeywordCode *peKeywordCode){
	
		unsigned char ucKeywordCounter;

	for(ucKeywordCounter = 0; ucKeywordCounter < MAX_KEYWORD_NR; ucKeywordCounter++){
		
		if(EQUAL == eCompareString(asKeywordList[ucKeywordCounter].cString, pcStr)){
			*peKeywordCode = asKeywordList[ucKeywordCounter].eCode;
			return OK;
		}
	}
	return ERROR;
}

//-------------------------------------------------------------------------fun3

void DecodeTokens(void){

  unsigned char ucTokenCounter;
	
	Token *psCurrentToken;
	char *pcString; 
	
  for(ucTokenCounter = 0; ucTokenCounter < ucTokenNr; ucTokenCounter++){
	
		psCurrentToken = &asToken[ucTokenCounter];
		pcString = psCurrentToken->uValue.pcString;
		
		if(OK == eStringToKeyword(pcString, &psCurrentToken->uValue.eKeyword)) {
			psCurrentToken->eType = KEYWORD;
		}
		else if(OK == eHexStringToUInt(pcString, &psCurrentToken->uValue.uiNumber)){
			psCurrentToken->eType = NUMBER;
		}
		else {
			psCurrentToken->eType = STRING;
		}
  }
}

/*
void DecodeTokens(void){

  unsigned char ucTokenCounter;
	
  for(ucTokenCounter = 0; ucTokenCounter < ucTokenNr; ucTokenCounter++){
		
		if(OK == eStringToKeyword(asToken[ucTokenCounter].uValue.pcString, &asToken[ucTokenCounter].uValue.eKeyword)) {
			asToken[ucTokenCounter].eType = KEYWORD;
		}
		else if(OK == eHexStringToUInt(asToken[ucTokenCounter].uValue.pcString, &asToken[ucTokenCounter].uValue.uiNumber)){
			asToken[ucTokenCounter].eType = NUMBER;
		}
		else {
			asToken[ucTokenCounter].eType = STRING;
		}
  }
}
*/

//--------------------------------------------------------------------------fun4
void DecodeMsg(char *pcString){ 
	
	ucTokenNr= ucFindTokensInString(pcString);
	ReplaceCharactersInString(pcString, DELIMITER_CHAR, '\0'); 

	DecodeTokens();
}