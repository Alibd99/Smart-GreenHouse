#include "at91sam3x8.h"
#include "Mission.h"

void PWM_Setup(void){
    *AT91C_PIOB_PDR  = (1<<17);
    *AT91C_PIOB_ABMR = (1<<17);
    *AT91C_PMC_PCER1 = (1 << 4); // Enable PWM Clock
    *AT91C_PWMC_ENA = (1<<1);
    *AT91C_PWMC_CH1_CMR = (AT91C_PWMC_CPRE_MCK_DIV_32);//(5<<1);
    *AT91C_PWMC_CH1_CPRDR   = (52500<<0); // (20ms) // 84 000 000 HZ / 32 * 20 ((1/frek) = period)
    *AT91C_PWMC_CH1_CDTYR = (890);  // (1ms)*/
    // MAX:6900
    // MIN: 890
}

void Move_PWM(int key){
    *AT91C_PWMC_CH1_CDTYUPDR = (890 + 33.4 * key);
    return;    
}


