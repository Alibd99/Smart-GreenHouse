#include <stdio.h>
#include "Mission.h"
extern char Fast;
extern char NextDay;
extern char Dark;
extern char Sun;
extern char DarkTime;
extern char SunTime;
extern char ShyneTime;
extern char Shyne;
extern char OnDay;
extern char Fast;
extern int ticks;

char mm = 0;
char hh = 0;
char dd = 0;

void Delay(int value){
    int i;
    for(i = 0; i < value ;i++)
        asm("nop");
} 

void updateTime(LinkedList *time) {
    if (times % ticks == 0) {
        if (Fast == 1){
            time->minutes = time->minutes + 30;
            mm = 1;// The Key!!
        } else {
            time->seconds++;
        }
        times = times % ticks;
    }
    else {
        return;
    }

    if (time->seconds == 60){
        time->seconds = 0;
        time->minutes++;
        mm = 1;//The Key!!
    }
    //Do you have The Key ?
    if (mm != 1) return; //For go faster save loop

    if (time->minutes >= 60){
        time->minutes %= 60;
        time->hours++;

        if (time->hours >= 6 && Shyne == 1 && Dark == 1) {
            ShyneTime++;
        }

        if (Sun == 1){
            SunTime++;
        }

        mm = 0;//Leave The Old Key Here!!
        hh = 1;//The New Key
    }

    //Do you have The New Key ?
    if (hh != 1) return; //For go faster save loop

    if (Fast){
        if (time->hours == 23 && time->minutes >= 30 && time->minutes <= 59 ) {
            NextDay = 1;
        }
    }
    else {
        if (time->hours == 23 && time->minutes == 59) {
            NextDay = 1;
        }
    }

    if (time->hours == 24) {
        time->hours = 0;
        time->days++;
        hh = 0;//Leave The Old Key Here!!
        dd = 1;//The New Key
        SunTime = 0; //Reset SunTime
        ShyneTime = 0;
    }

    if (time->hours >= 4 ){
        OnDay = 1;
    } else {
        OnDay = 0;
    }

    //Do you have The New Key ?
    if (dd != 1) return; //For go faster save loop

    if(time->years % 4 == 0){
        if (time->months == 2 && time->days == 30){
            time->days = 01;
            time->months++;
            dd = 0;//Leave The Old Key Here!!
        }
    } else if (time->months == 2 && time->days == 29){
        time->days = 01;
        time->months++;
        dd = 0;//Leave The Old Key Here!!
    }

    if(time->months == 4 || time->months == 6 || time->months == 9 || time->months == 11){
        if (time->days == 31){
            time->days = 01;
            time->months++;
            dd = 0;//Leave The Old Key Here!!
        }
    }

    if(time->months == 1 || time->months == 3 || time->months == 5 || time->months == 7 ||
            time->months == 8 || time->months == 10 || time->months == 12 ) {
        if (time->days == 32) {
            time->days = 01;
            time->months++;
        }
        dd = 0;//Leave The Old Key Here!!
    }

    if (time->months == 13){
        time->months = 1;
        time->years++;
    }
}


