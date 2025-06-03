#include <LPC21xx.H>
#include "timer.h"

#define Counter0_Enable_bm (1 << 0) //Wlacza licznik timera i preskalera (1 = wlaczony, 0 = wylaczony).
#define Counter0_Reset_bm (1 << 1) // Resetuje licznik timera TC i preskalera PC na nastepnym zboczu PCLK. 

#define Reset_On_MR0_bm (1 << 1) 
#define Interupt_On_MR0_bm (1 << 0)
#define MR0_Interupt_Flag_bm (1 << 0 )

void InitTimer0(void){
	T0TCR = Counter0_Enable_bm;
}

void WaitOnTimer0(unsigned int uiTime){
	
	T0TCR |= Counter0_Reset_bm; // resetuje timer0 
	T0TCR &= ~(Counter0_Reset_bm); // wylacza resetowanie 
	
	while((uiTime *15) > T0TC){} // zegar rdzenia 60MHz, dla timer0 to 1/4 taktowania rdzenia procesora,
		                           //  czeka az do wartosci podanej, T0TC przechwouje wartosc licznika 
}

void InitTimer0Match0(unsigned int iDelayTime){
	T0MR0 = (iDelayTime * 15);
	T0MCR |= (Reset_On_MR0_bm | Interupt_On_MR0_bm);//po osiagnieciu wartosci MR0 przez timer0 wysyla flage przerwania i zeruje sie timer 
	
	T0TCR |= Counter0_Reset_bm; // resetowanie timera 0 
	T0TCR &= ~(Counter0_Reset_bm); // wylaczeniu bitu resetowania 
	T0TCR = Counter0_Enable_bm; 	// odpalenie timera0 
}

void WaitOnTimer0Match0(void){
	while(0 ==(T0IR & MR0_Interupt_Flag_bm)){}
		T0IR |= MR0_Interupt_Flag_bm; // reset flagi przerwania zapis(1 do bitu 0 w T0IR) 
}























/*TIMERY:
while (T0TC < (uiTime*15)) dlaczego nie moze byc równa sie?
Odp. Timer i petla while pracuja z rózna czestotliwoscia. Timer 15MHz, petla while 60MHz dlatego moga
nigdy nie natrafic na takie same wartosci.
Co zrobic aby natrafily na takie same wartosci? Zwiekszyc czestotliwosc petli while albo zmniejszyc
Timera.
Pomiedzy wlaczeniem resetu ( T0TCR = T0TCR | Timer_Reset) a T0TCR = Timer_Enable musi byc wylaczenie
resetu, zeby nikt sie nie musial domyslac.
Czy w linijce T0IR = MR0_INTERRUPT_FLAG moze byc suma logiczna? Nie moze bo moglibysmy nieswiadomie
zmieniac poprzednio ustalone bity w rejestrze IR.
Mialam napisac przykladowe dzialanie sumy logicznej dla wymyslonego IT i na podstawie koncowego wyniku
okreslic jakie beda funkcje, typu zgaszenie/zapalenie flagi przerywania danego rejestru itp.
Z ilu zródel przychodza przerywania w IR? z 8.

Co gdy wartosc MR0 zrówna sie z wartoscia TC? Jakie funkcje sa wlaczone?
W jakich jednostkach ustalony jest czas/ jaki jest ? argumentMikrosekundy
7. Timery
T0IR = T0IR|MR0_INTERRUPT_FLAG; ?- niepoprawnie // co robi ta linijka
powinno byc
odp: wpisanie logicznej jedynki do odpowiedniego bitu rejestru IR powoduje zresetowanie interrupta (u
nas MR0_INTERRUPT_FLAG (1<<0).
odp 2: suma logiczna w tej linijce powoduje wyzerowanie wszystkich flag przerwania w rejestrze dlatego
zamiast niej powinno byc zwykle przypisanie T0IR = MR0_INTERRUPT_FLAG
Jakie dwa cykle pracy maja timery ?
odp: Timer albo Counter
U mnie nie zaliczyl odpowiedzi timer albo counter :(. Ucieszyl sie jak mu powiedzialem ze chodzi o cykl
pracy timera i petli while. Sa taktowane z róznych zegarów i dlatego wartosci moga nigdy nie byc
równe.Zeby tak bylo to cykl petli (de facto procesora[60MHz])musialaby byc duzo czestszy od cyklu
timera[15MHz].
Uruchomic debugger i w oknie timera pokazac dzialanie
pokazac skad wiadomo, ze jest przerwanie (0x00000001 w Interrupt Register po prawej stronie okienka
timera)
pokazac gdzie jest zapisana wartosc z która ma byc porównywany timer counter (MR0: w Match Channels)
Co sie moze stac gdy wartosc TC zrówna sie z wartoscia w rejestrze MR0 (wyzerowanie TC i zapalenie
flagi przerwania to za malo, trzeba znac wiecej opcji nawet jak sie ich nie uzywa w programie....)
*/
