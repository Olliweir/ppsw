#include <LPC21xx.H>
#include "timer_interrups.h"

// TIMER 0 
#define mCOUNTER_ENABLE (1 << 0)
#define mCOUNTER_RESET  (1 << 1)

// CompareMatch
#define mINTERRUPT_ON_MR0 (1 << 0)
#define mRESET_ON_MR0     (1 << 1)
#define mMR0_INTERRUPT    (1 << 0)

// VIC (Vector Interrupt Controller) VICIntEnable
#define VIC_TIMER0_CHANNEL_NR 4  //str 103 

// VICVectCntlx Vector Control Registers
#define mIRQ_SLOT_ENABLE (1 << 5) //Bit 5 (ENABLE bit) – 	1 = aktywuj slot; 0 = nieaktywny (nieuzywany) (bit 5 w VICVectCntl)
                                 //If cleared, the slot is disabled even if an interrupt occurs on the assigned source.

/**********************************************/

void (*ptrTimer0InterruptFunction)(void); // Globalny wskaznik na funkcje, która bedzie wywolywana w przerwaniu

//(Interrupt Service Routine) of Timer 0 interrupt
// __irq oznacza, ze jest to ISR; kompilator generuje odpowiedni kod wejscia/wyjscia dla trybu IRQ
//Jest to procedura obslugi przerwania (ISR – Interrupt Service Routine), która automatycznie wykonuje sie, gdy Timer 0 zglosi przerwanie
//Ta funkcja dziala jako "most" miedzy sprzetem (Timer 0 i VIC) a oprogramowaniem (funkcja uzytkownika)
__irq void Timer0IRQHandler(){

	T0IR = mMR0_INTERRUPT; 	// skasowanie flagi przerwania 
	ptrTimer0InterruptFunction();		// cos do roboty
	VICVectAddr = 0x00; 	// potwierdzenie wykonania procedury obslugi przerwania
                        // Informuje VIC, ze ISR sie zakonczylo, umozliwiajac obsluge kolejnych przerwan
}
/**********************************************/
void Timer0Interrupts_Init(unsigned int uiPeriod,void(*ptrInterruptFunction)(void)){	// microseconds
	ptrTimer0InterruptFunction = ptrInterruptFunction;

        // inicjalizowanie interrupts

	VICIntEnable |= (1 << VIC_TIMER0_CHANNEL_NR);            // Enable Timer 0 interrupt channel 
	VICVectCntl1  = mIRQ_SLOT_ENABLE | VIC_TIMER0_CHANNEL_NR;  // Enable Slot 1 and assign it to Timer 0 interrupt channel
	VICVectAddr1  =(unsigned long)Timer0IRQHandler; 	   // Ustawia adres procedury ISR (Timer0IRQHandler) dla slotu 1
                                                    // VIC bedzie skakal do tej procedury przy przerwaniu z Timera 0 

        // moduly porownan 

	T0MR0 = 15 * uiPeriod;                 	      // value 15 000 cykli = 1 ms przy PCLK=15 MHz
	T0MCR |= (mINTERRUPT_ON_MR0 | mRESET_ON_MR0); // action przerwanie i reset na MR0

        // timer

	T0TCR |=  mCOUNTER_ENABLE; //timer start 
	}
