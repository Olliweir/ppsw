#include <LPC21xx.H>

#include "konwersje.h"

#define MAX_TOKEN_NR 3 //MAKS ILOSC TOKENOW
#define MAX_KEYWORD_STRING_LTH 10 // MAKS Dlugosc komendy 
#define MAX_KEYWORD_NR 3 //ILOSC POPRAWNYCH SLOW
#define NULL 0 
#define SPACE ' ' 

typedef enum {KEYWORD, NUMBER, STRING} TokenType;
typedef enum  {LD, ST, RST} KeywordCode;

typedef union { // pola dziela te same miejsce, wspolna i mniejsz pamiec, przechowuje tylko jedna wartosc na raz 
	KeywordCode eKeyword;
	unsigned int     uiNumber; 
	char *           pcString;
}TokenValue;

typedef struct { // wszystkie pola maja wlasne mijesce w pamieci, laczy rozne zmienne w jedna calosc, grupowanie danych roznych typow razem
	TokenType eType;
	TokenValue uValue;
}Token;
	
typedef struct {
	KeywordCode eCode;
	char cString[MAX_KEYWORD_STRING_LTH + 1]; //rezerwuje miejsce na nulla 
}Keyword; 

Keyword asKeywordList[MAX_KEYWORD_NR] = { // uzywana przez bStringToCommand
	{RST, "reset"},
  {LD, "load"},
  {ST, "store"}
};
Token asToken[MAX_TOKEN_NR];  // wypelniana przez DecodeMsg na podstawie cUartRxBuffer i asCommandList
unsigned char ucTokenNr;// liczba tokenów w zdekodowanym komunikacie
typedef enum {TOKEN, DELIMITER} State;  // token jestes wewntarz tokenu na literze slowie, delimiter jestes miedzy tokenami na spacji itd

typedef enum Result {OK,ERROR} Result;


//----------------------------------------------------------------------- 1 
unsigned char ucFindTokensInString (char *pcString){
	unsigned char ucCurrentChar; 
  unsigned char ucCharCounter; 
  unsigned char ucTokenNr = 0;
	State eState = DELIMITER;
	
	 for (ucCharCounter=0; ;ucCharCounter++){ // nieskonczona petla for iterujaca po znakach pcString 
		 ucCurrentChar = pcString[ucCharCounter];
		 switch(eState){
			 case DELIMITER:
				 if (ucCurrentChar == NULL){
				 return ucTokenNr;
			 } 
			 else if (ucCurrentChar == SPACE){
				 eState = DELIMITER;
			 } 
			 else if (ucTokenNr < MAX_TOKEN_NR){
				 asToken[ucTokenNr].uValue.pcString = pcString + ucCharCounter;
				 ucTokenNr++; 
         eState = TOKEN;
			 }
			 break; 
			 
			 case TOKEN:
				 if (ucCurrentChar == NULL){
				 return ucTokenNr;
			 } 
			 else if (ucCurrentChar == SPACE){
				 eState = DELIMITER;
			 }
			 else {
				 eState=TOKEN;
			 }
			 break;
		 }
	 }
 }
 
 //--------------------------------------------------------------------------------fun2
Result eStringToKeyword (char pcStr[],KeywordCode *peKeywordCode){ //deklaruje licznik po iteracji asKewordList
	
		unsigned char ucKeywordCounter;

	for(ucKeywordCounter = 0; ucKeywordCounter < MAX_KEYWORD_NR; ucKeywordCounter++){ //iteruje po tablicy asKeywordList 
		
		if(EQUAL == eCompareString(asKeywordList[ucKeywordCounter].cString, pcStr)){ //Wywoluje eCompareString do porównania pcStr z cString w asKeywordList.
			*peKeywordCode = asKeywordList[ucKeywordCounter].eCode; // zapisuje kod slowa kluczowego do peKeyword np LD
			return OK;
		}
	}
	return ERROR;
}

//-------------------------------------------------------------------------------fun3
void DecodeTokens(void){

  unsigned char ucTokenCounter;
	
	Token *psCurrentToken;
	char *pcString; //Deklaruje licznik tokenów, wskaznik na token i wskaznik na lancuch.
	
  for(ucTokenCounter = 0; ucTokenCounter < ucTokenNr; ucTokenCounter++){ //Iteruje po tokenach w tablicy asToken (do ucTokenNr).
	
		psCurrentToken = &asToken[ucTokenCounter];
		pcString = psCurrentToken->uValue.pcString;//Pobiera wskaznik na lancuch tokenu
		
		if(OK == eStringToKeyword(pcString, &psCurrentToken->uValue.eKeyword)) { //Sprawdza, czy lancuch jest slowem kluczowym (reset, load, store).
			psCurrentToken->eType = KEYWORD;
		}
		else if(OK == eHexStringToUInt(pcString, &psCurrentToken->uValue.uiNumber)){//Jesli nie jest slowem kluczowym, próbuje przekonwertowac na liczbe szesnastkowa.
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

void DecodeMsg(char *pcString) {
	ucTokenNr= ucFindTokensInString(pcString); 
	ReplaceCharactersInString(pcString, SPACE, NULL); 
	DecodeTokens();
}

 
 
 
 
 
 
 
 
 
 
 
 
 
 
		 int main() {
			 
			 
			 char test1[]="      ";
			 unsigned char count1 = ucFindTokensInString(test1);
			 
			 
			 char test2[]="   load store";
			 unsigned char count2 = ucFindTokensInString(test2);
			 
			 char test3[]="reset load store";
			 unsigned char count3 = ucFindTokensInString(test3);
			 
			 
			 while(1);
		 
		 
}

		 
		 
	 
	
	








	
