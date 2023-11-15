#include <stdlib.h>
#include "system_sam3x.h"
#include "at91sam3x8.h"
#include "Mission.h"
#include "LinkList.h"

struct LinkedList list;
/**Flag**/
char setFlag = 0;

/**MainValue**/
double temp;

void Init_Temp(void){
    *AT91C_PMC_PCER  = (1<<12); // Peripheral Clock Enable
    *AT91C_PIOB_PER = (1<<25);              // Activate PIOB pins
    *AT91C_PMC_PCER = (1 << 27);    // Peripheral Clock Enable Continued
    *AT91C_TC0_CMR = (*AT91C_TC0_CMR & 0xfff8 | 1<<17| 1<<18);
    *AT91C_TC0_CCR  = (1<<0)|(1<<2);                 //  Enable and reset the clock
    *AT91C_PIOB_OER  = (1<<25);           // Enable Output
    *AT91C_PIOB_SODR = AT91C_PIO_PB25;
    *AT91C_PIOB_CODR = AT91C_PIO_PB25;
    times = 0;
    while (times < 14) {}                // Wait for RESET pulse to be complete
    *AT91C_PIOB_SODR = AT91C_PIO_PB25;
    NVIC_EnableIRQ((IRQn_Type)27);
    NVIC_ClearPendingIRQ((IRQn_Type)27);
    NVIC_SetPriority((IRQn_Type)27, 2);
    *AT91C_TC0_SR;
}

void Temp_Measure(void){
    *AT91C_PIOB_OER  = (1<<25);   // Enable output
    *AT91C_PIOB_SODR = AT91C_PIO_PB25; // HIGH
    *AT91C_PIOB_CODR = (1<<25);   // Clear output LOW
    times = 0;
    while (times < 14) {}                // Wait for RESET pulse to be complete
    *AT91C_PIOB_SODR = AT91C_PIO_PB25; // HIgh
    *AT91C_PIOB_CODR = (1<<25);   // Clear output'
    *AT91C_PIOB_SODR = AT91C_PIO_PB25; //HIGH     
    *AT91C_PIOB_ODR = AT91C_PIO_PB25; // Disable PIO pin needed as output   
    *AT91C_TC0_SR;    // READ
    setFlag = 0;
    *AT91C_TC0_CCR  = (1<<2);          // sw_reset
    *AT91C_TC0_IER  = (1<<6);          // Enable interrupt
}

int Update_Temp(void){
    if (setFlag == 0){
        return 0;
    }
    temp = (double)((*AT91C_TC0_RB) - (*AT91C_TC0_RA));
    temp = (temp/42.0);
    temp = ((temp/5.0)-273.15);
    Temp_Measure();
    return temp;
}

void TC0_Handler(void){
    *AT91C_TC0_IDR  = (1<<6);     // Disable interrupt
    setFlag = 1;                  // Rising Edge detected, set TC Flag
}








