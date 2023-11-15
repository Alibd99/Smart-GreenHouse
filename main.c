#include "at91sam3x8.h"
#include "core_cm3.h"
#include "core_cmFunc.h"
#include "core_cmInstr.h"
#include "system_sam3x.h"
#include "Mission.h"
#include "LinkList.h"

//Use for save value when press on keypad
unsigned char temp3[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};

//Flag for menu
char Mem = 0;
char Sensor = 0;
char Lamp = 0;

//Value of Temperature
int temperature = 0;

//Limit Node of Memory
int week  = 7;

//Systicks Handle;
int ticks;
int times = 0;

//Average, Min and Max Value
double sum = 0;
double avg = 0;
double max = 0;
double min = 100;
int peek   = 0; //Count Measure Temperature Time

//Fast Mode
char Fast;

//Start a new day
char NextDay;

//Active LightShade
char ReadLight;

//Memory Flag
char well;
char fullsize;

//SunTime
extern char SunTime;

//Struct LinkedList and List
extern struct LinkedList list;
struct List * myWeek;
struct Temperature * Max;
struct Temperature * Min;


void config (void);


/**Confiq**/
void config(void) {
    SystemInit();
    SysTick_Config(SystemCoreClock/TICKS); // 1ms
    Init_Display();
    Clear_Display();
    Set_Led();
    Init_Temp();
    Temp_Measure();
    ADC_Setup();
    PWM_Setup();
}

int main(void) {
    config();
    list.years   = 1000;
    list.months  = 10;
    list.days    = 10;
    list.hours   = 00;
    list.minutes = 38;
    list.seconds = 00;
    list.sensorData = 0;
    resetAlarm();
    startMenu();
    ticks = TICKS;
    myWeek = create();
    Max = creatTemperature(0,0,0,0);
    Min = creatTemperature(0,0,0,0);
    
    while (1){
        updateTime(&list);

        if (times % 1000 == 0){
            Read_Light();
        }

        if (times % 1000 == 0){
            Suntime();
            temperature = Update_Temp();
            checkAlarm(temperature);
            sum += temperature;
            peek++;

            if (temperature > max) {
                max = temperature;
                Max = creatTemperature(list.hours, list.minutes, list.seconds,
                                       max);
            }

            if (temperature < min) {
                min = temperature;
                Min = creatTemperature(list.hours, list.minutes, list.seconds,
                                       min);
            }

            if (NextDay == 1){
                avg = sum / peek;

                if (myWeek->size < week){
                    append(myWeek, peek,
                           list.years, list.months, list.days,
                           list.hours, list.minutes, list.seconds,
                           avg, Max, Min);
                    well = 1;
                }
                else {
                    free(myWeek->head->min);
                    free(myWeek->head->max);
                    deleteNode(myWeek, myWeek->head);
                    append(myWeek, peek,
                           list.years, list.months, list.days,
                           list.hours, list.minutes, list.seconds,
                           avg, Max, Min);
                    well = 1;
                }

                //Reset Min Max Average and peek
                peek = 0;
                sum = 0;
                avg = 0;
                max = 0;
                min = 100;

                //Reset NextDay for new day;
                NextDay = 0;
            }
        }

        if(fullsize == 1 && well == 1){
            PMemFull(myWeek);
            well = 0;
        }
        else if (PrintM == ON && well == 1){
            PMem(myWeek);
            well = 0;
        }

        if(PrintT == ON){
            Pdate(&list);
            Write_Temp(temperature);
            PrintSunTime();
        }

        /**Operator**/
        int key = input();
        if (key != 0){
            if (key > 0 && key < 13 ){
                switch (key){

                    case 1:
                        Fast = 0;
                        PrintON();
                        setPosition(4);
                        PrintToScreen(" Fast Mode : OFF");
                        break;

                    case 2:
                        Fast = 1;
                        ticks = 500;
                        setPosition(4);
                        PrintToScreen(" Fast Mode : ON ");
                        PrintON();
                        break;


                    case 3:
                        if (fullsize != 1){
                            if (Lamp % 2 == 0){
                                PAlarm();
                            } else {
                                setPosition(5);
                                PrintToScreen("               ");
                                setPosition(6);
                                PrintToScreen("               ");
                            }
                            Delay(2000000);
                            Lamp++;
                        }
                        break;

                    case 4:
                        Clear_Display();
                        PrintMOFF();
                        inputArray(temp3,14);
                        setDate(temp3);
                        PrintON();
                        setPosition(15);
                        PrintToScreen("9.Back ");
                        Delay(2000000);
                        break;

                    case 5:
                        Clear_Display();
                        PrintMOFF();
                        inputArray(temp3,4);
                        setAlarm(temp3);
                        PAlarm();
                        statusAlarm();
                        setPosition(15);
                        PrintToScreen("9.Back ");
                        Delay(2000000);
                        break;

                    case 6:
                        Clear_Display();
                        PrintMOFF();
                        resetAlarm();
                        PAlarm();
                        statusAlarm();
                        Delay(2000000);
                        break;

                    case 7:
                        if (Sensor % 2 == 0){
                            ReadLight = 1;
                        } else {
                            ReadLight = 0;
                        }
                        Delay(2000000);
                        Sensor++;
                        break;

                    case 8:
                        if (fullsize != 1){
                            if (PrintM == 0)
                                PrintMON();
                            else
                                PrintMOFF();
                            fullsize = 0;
                            well = 1;
                            setPosition4(2, 19);
                            PrintToScreen("*.Show More Memories");
                        }

                        break;

                    case 9:
                        Clear_Display();
                        fullsize = 0;
                        PrintOFF();
                        PrintMOFF();
                        startMenu();
                        PrintToScreen("                You are Back now");
                        break;

                    case 10:
                        Clear_Display();
                        PrintMOFF();
                        fullsize = 1;
                        well = 1;
                        setPosition4(2, 0);
                        PrintToScreen("9.Back");
                        break;
                }
            }
        } else
            continue;
    }
}

void startMenu(){
    Clear_Display();
    setPosition(1);
    PrintToScreen("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    setPosition(7);
    PrintToScreen("1.Normal Mode");
    setPosition(8);
    PrintToScreen("2.Fast Mode");
    setPosition(9);
    PrintToScreen("3.Limit Alarm");
    setPosition(10);
    PrintToScreen("4.Setting Date");
    setPosition(11);
    PrintToScreen("5.Setting Alarm");
    setPosition(12);
    PrintToScreen("6.Reset Alarm");
    setPosition(13);
    PrintToScreen("7.Find The Sun");
    setPosition(14);
    PrintToScreen("8.Print Memory");
    setPosition(15);
    PrintToScreen("9.Back | Clear");

    setPosition3(3);
    PrintToScreen("!");
    setPosition3(5);
    PrintToScreen("!");
    setPosition3(7);
    PrintToScreen("!");
    setPosition3(9);
    PrintToScreen("!");
    setPosition3(11);
    PrintToScreen("!");
    setPosition3(13);
    PrintToScreen("!");
    setPosition3(15);
    PrintToScreen("!");
    setPosition3(2);
    PrintToScreen("!");
    setPosition3(4);
    PrintToScreen("!");
    setPosition3(6);
    PrintToScreen("!");
    setPosition3(8);
    PrintToScreen("!");
    setPosition3(10);
    PrintToScreen("!");
    setPosition3(12);
    PrintToScreen("!");
    setPosition3(14);
    PrintToScreen("!");
    setPosition3(16);
    PrintToScreen("!");


}

/**General Systick**/
void SysTick_Handler(){
    times++;
}