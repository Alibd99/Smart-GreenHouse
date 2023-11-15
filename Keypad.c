#include "system_sam3x.h"
#include "at91sam3x8.h"
#include <stdio.h>
#include "Mission.h"
extern LinkedList list;
unsigned char temp2[] = {0,0,0,0,0,0,0,0};
char KeyDone = OFF;
char isPress = FALSE;
char alarmStatus;

int input(void){
    isPress = FALSE;
    *AT91C_PIOC_PER   = (0x3BC);
    *AT91C_PIOD_PER   = (0x4);
    *AT91C_PIOC_PPUDR = (0x3BC);
    *AT91C_PIOD_PPUDR = (0x4);
    *AT91C_PIOD_OER   = (0x4);
    *AT91C_PIOC_OER   = (0x380);
        int value = 0;
    *AT91C_PIOD_CODR = (0x4);
    *AT91C_PIOC_SODR = (0x380);
    *AT91C_PIOC_ODR  = (0x3C);
    for(int colomn = 0; colomn < 3; colomn++){
        *AT91C_PIOC_CODR = (1 << (7 + colomn));
        for(int row = 0; row < 4; row++){

            if ((*AT91C_PIOC_PDSR & (1 << (2 + row))) == 0){
                value = row * 3 + colomn + 1;

                /**Flag**/
                isPress = TRUE;

                *AT91C_PIOC_SODR = (1 << (7 + colomn));
                *AT91C_PIOC_ODR =  (0x380);
                return value;
            }

        }
        *AT91C_PIOC_SODR = (1 << (7 + colomn));
    }
    *AT91C_PIOC_ODR =  (0x380);
    return value;
}

int isUpdated (int key) {
    if (isPress == TRUE){
        if (key!= 0) {
            return TRUE;
        }
    }
    return FALSE;
}

int isBreak (int key) {
    if (isPress == TRUE){
        if (key == 9) {
            return TRUE;
        }
    }
    return FALSE;
}

void inputArray(unsigned char *current, int a) {
    int key = 0;
    setPosition(9);
    if (a == 4){
        alarmStatus = NONRESET;
        PrintToScreen("Temperature: HH/LL");
    } else{
        PrintToScreen("Date: YYYY/MM/DD");
        setPosition(11);
        PrintToScreen("Time: HH/MM/SS");
    }

    setPosition(10);
    for (int i = 0; i < a; i++){
        Delay(2000000);
        key = input();

        if (i == 8){
            setPosition(12);
        }
        Write_Key_Display(key);
        if(!isUpdated(key)){
            i--;
        } else{
            if(key > 0 && key < 12 && key !=10){
                if (key == 11)
                    key = 0;
                current[i] = key;
            }
            else
                i--;
            key = 0;
        }
        key = 0;
    }
    KeyDone = ON;
}

void setDate (unsigned char current[]){
    if(KeyDone == ON){
        list.years = current[0] * 1000 + current[1] * 100 + current[2] * 10 + current[3];
        if (list.years > 3000){
            list.years = 3000;
        }
        list.months = current[4] * 10 + current[5];
        if (list.months > 12){
            list.months = 12;
        } else if (list.months < 1){
            list.months = 1;
        }
        list.days = current[6] * 10 + current[7];
        if (list.days < 1){
            list.days = 1 ;
        } else if (list.years % 4 == 0 && list.months == 2 && list.days > 29){
            list.days = 29;
        } else if (list.years % 4 == 0 && list.months == 2 && list.days > 28){
            list.days = 28;
        } else if ((list.months == 1 || list.months == 3 || list.months == 5 ||
                   list.months == 7 || list.months == 8 || list.months == 10 ||
                   list.months == 12) && list.days > 31){
            list.days = 31;
        } else if ( (list.months == 4 || list.months == 6 || list.months == 9 || list.months == 11) && list.days > 30){
            list.days = 30;
        }
        list.hours = current[8] * 10 + current[9];
        if (list.hours > 23){
            list.hours = 00;
        }
        list.minutes = current[10] * 10 + current[11];
        if (list.minutes > 59){
            list.minutes = 00;
        }
        list.seconds = current[12] * 10 + current[13];
        if (list.seconds > 59){
            list.seconds = 00;
        }
    }
    /**Flag**/
    KeyDone = OFF;
}