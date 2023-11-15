#include <stdio.h>
#include "system_sam3x.h"
#include "at91sam3x8.h"
#include "Mission.h"

struct Alarm alarm;
char LedON;
char Shyne;

void checkAlarm (double temperature){
    if(temperature > alarm.high){
        setPosition(3);
        PrintToScreen("!!Warning: High Temp!! Please Check Temp");
        ledOn();
        return;
    } else if(temperature < alarm.low) {
        setPosition(3);
        PrintToScreen("!!Warning: Low Temp!! Please Check Temp");
        ledOff();
        return;
    } else if (LedON == 1){
        ledOn();
    }
}

void setAlarm (unsigned char current[]){
    alarmStatus = NONRESET;
    if(KeyDone == ON){
        alarm.high = current[0] * 10 + current[1];
        setPosition4(13,0);
        if (alarm.high < 20){
            PrintToScreen("Too Low for the required High Alarm");
        }
        alarm.low = current[2] * 10 + current[3];
        if (alarm.low > 20){
            PrintToScreen("Too High for the required Low Alarm");
        }
    }
    KeyDone = OFF;
}

void statusAlarm (){
    if (alarmStatus == RESET){
        setPosition(8);
        PrintToScreen("Alarm was reset!");
    } else if (alarmStatus == NONRESET){
        setPosition(8);
        PrintToScreen("Alarm is Updated! ");
    }
    setPosition(15);
    PrintToScreen("9.Back ");
}

void resetAlarm (){
    alarmStatus = RESET;
    alarm.high = 40;
    alarm.low = 00;
    ledOff();
}

void Set_Led(){
    *AT91C_PMC_PCER= (1<<14); //Enable peripheral clock for PIOD
    *AT91C_PIOD_PER = 0x8; //Enable PIO for PIOD
    *AT91C_PIOD_OER = 0x8; //Make the pin as output
    *AT91C_PIOD_PPUDR = 0x8; //Disable the internal pull up resistor
}

void ledOn(void){
    *AT91C_PIOD_SODR=(1<<3);  //set the output data register for PD3 pin 28
    LedON = 1;
    Shyne = 1;
}

void ledOff(void){
    *AT91C_PIOD_CODR=(1<<3);  // clear the output data register for PD3 pin 28
    LedON = 0;
    Shyne = 0;
}


