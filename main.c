#include "MK64F12.h"
void PORTB_IRQHandler(void);
void delayMs(int n);
  
int main(void) {
	SIM -> SCGC5 |= (1 << SIM_SCGC5_PORTB_SHIFT) | (1 << SIM_SCGC5_PORTA_SHIFT) | (1 << SIM_SCGC5_PORTD_SHIFT);
  PORTB -> PCR[3] = 1 << PORT_PCR_MUX_SHIFT;/*set GPIO Switch 1*/
  PORTB -> PCR[10] = 1 << PORT_PCR_MUX_SHIFT;/*set GPIO Switch 2*/
	PORTB -> PCR[11] = 1 << PORT_PCR_MUX_SHIFT; /*set GPIO Switch 3*/
  PORTA -> PCR[1] = 1 << PORT_PCR_MUX_SHIFT;/*set GPIO BUZZER*/	
	
	PORTD->PCR[1] = 1 << PORT_PCR_MUX_SHIFT;
  PORTD->PCR[3] = 1 << PORT_PCR_MUX_SHIFT;
  PORTD->PCR[2] = 1 << PORT_PCR_MUX_SHIFT;
  PORTD->PCR[0] = 1 << PORT_PCR_MUX_SHIFT;
	 	
  __disable_irq();              /*disable IRQs */
  PORTB->PCR[10] &= ~0xF0000;  /*clear interrupt*/
  PORTB->PCR[10] |= 0x90000;   /*enable edge interrupt*/
  NVIC->ISER[1] |= 0x10000000;  /*enable interrupt for PORTB at NVIC */
  __enable_irq();             /*enable IRQs */
    
	
	int i;
    while (1) {
						
       if ((PTB -> PDIR & 0x08) == 0){

						PTD->PDDR |= 0x0F;			                                                        
			 }
			 		 		
			 if ((PTB -> PDIR & 0x800) == 0){
						
					PTA->PDDR |= 0x02;
					for (i = 0; i < 3; i++) {
						
						
						PTD->PDDR |= (1 << 1);
						delayMs(50);
						PTD->PDDR |= (1 << 3);
						delayMs(50);
						PTD->PDDR |= (1 << 2);
						delayMs(50);
						PTD->PDDR |= (1 << 0);
						delayMs(50);
				 
						PTD->PDDR &= ~(1 << 1);
						delayMs(50);
						PTD->PDDR &= ~(1 << 3);
						delayMs(50);
						PTD->PDDR &= ~(1 << 2);
						delayMs(50);
						PTD->PDDR &= ~(1 << 0);
						delayMs(50);
					 
						PTD->PDDR |= (1 << 0);
						delayMs(50);
						PTD->PDDR |= (1 << 2);
						delayMs(50);
						PTD->PDDR |= (1 << 3);
						delayMs(50);
						PTD->PDDR |= (1 << 1);
						delayMs(50);
						
						PTD->PDDR &= ~(1 << 1);
						delayMs(50);
						PTD->PDDR &= ~(1 << 3);
						delayMs(50);
						PTD->PDDR &= ~(1 << 2);
						delayMs(50);
						PTD->PDDR &= ~(1 << 0);
						delayMs(50);
																							
					}
					PTA->PDDR &= !0x02;
					
				}
								
	}

}

void PORTB_IRQHandler(void) {
	int i;
	if ((PTB->PDIR & 0x400) == 0) {
				
				PTD->PDDR &= ~(1 << 2);
				delayMs(100);
				
				PTD->PDDR &= ~(1 << 3);
				delayMs(100);
				
				PTD->PDDR &= ~(1 << 1);
				delayMs(100);
				
		
		for(i =0; i < 5; i++) {
				PTD->PDDR &= ~(1 << 0);
				delayMs(100);
				PTD->PDDR |= (1 << 0); 
				delayMs(100);
			
				PTA->PDDR &= !0x02;
				delayMs(100);
				PTA->PDDR |= 0x02;
				delayMs(100);
				PTA->PDDR &= !0x02;
				delayMs(100);
			}
		
		PORTB->ISFR = 0x400; /* Step clear interrupt flag PortB */
	}
}
    
	
void delayMs(int n) {

		int i;
    
    SysTick->LOAD = 20480 - 1;
    SysTick->CTRL = 5; /*Enable the timer */
    
    for (i = 0; i < n; i++)
        while ((SysTick->CTRL & 0x10000) == 0) { /* wait until the COUNT flag is set */
        }
        
    SysTick->CTRL = 0; /* Stop the timer (Enable = 0) */
				
	}







