#include "MK64F12.h"

void initPort(void);
void PORTB_IRQHandler(void);
void Led(void);
void delayMs(int n);

int main(void) {
	initPort();
	
	while (1){
		
		if ((PTB -> PDIR & 0x08) == 0){
			PTA -> PDDR |= 0x02;
				if((PTB->PDIR & 0x0400) == 0){
					PTA -> PDDR &= !(0x02);
					break;
		}
			
				

			}
		if((PTD->PDIR & 0x08) == 0){
					PTB -> PDDR &= !(0x03);
					
		}
			
		
	}
	
}
	

        

       



void initPort(void) {
        SIM -> SCGC5 |= (1 << SIM_SCGC5_PORTA_SHIFT) | (1 << SIM_SCGC5_PORTB_SHIFT) | (1 << SIM_SCGC5_PORTD_SHIFT);
        PORTB -> PCR[3] = 1 << PORT_PCR_MUX_SHIFT;
        PORTB -> PCR[10] = 1 << PORT_PCR_MUX_SHIFT;
				PORTB -> PCR[11] = 1 << PORT_PCR_MUX_SHIFT;
        PORTA -> PCR[1] = 1 << PORT_PCR_MUX_SHIFT;
				PTB -> PDDR &= !(1 << 3);
        PTB -> PDDR &= !(1 << 10);
				PTB -> PDDR &= !(1 << 11);
        __disable_irq();
        PORTB->PCR[10] &= ~0xF0000;
        PORTB->PCR[10] |= 0x90000;
        NVIC->ISER[1] |= 0x10000000;
        __enable_irq();
	

}

void PORTB_IRQHandler(void){
     if((PTB->PDIR & 0x400)==0){
      PTA -> PDDR &= !(0x02);
	}
}

void Led(void){
        PORTD -> PCR[0] = 1 << PORT_PCR_MUX_SHIFT;
        PORTD -> PCR[1] = 1 << PORT_PCR_MUX_SHIFT;
        PORTD -> PCR[2] = 1 << PORT_PCR_MUX_SHIFT;
        PORTD -> PCR[3] = 1 << PORT_PCR_MUX_SHIFT;
				PORTB -> PCR[10] = 1 << PORT_PCR_MUX_SHIFT;
				PTD -> PDDR &= !0x400;
				PTD -> PDDR &= !0x4000;
				PTD -> PDDR &= !0x1000;
				PTD -> PDDR &= !0x800;
				
}
   
void delayMs(int n) {
        int i;
        SysTick -> LOAD = 20480 - 1;
        SysTick -> CTRL = 5;
        for (i = 0; i < n; i++)
                while ((SysTick -> CTRL & 0x10000) == 0) {}
        SysTick -> CTRL = 0;
}               




