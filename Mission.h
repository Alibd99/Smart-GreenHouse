#ifndef MISSION_H
#define MISSION_H
#include <stdlib.h>  /* for using the functions calloc, free */
#include <string.h>  /* for using the function memcpy        */
#include <limits.h>  /* for using the constant UINT_MAX      */
#include "LinkList.h"

#define TRUE    1
#define FALSE   0

#define ON    1
#define OFF   0

#define RUNNING 1
#define STOPP   0

#define FAIL    0
#define SUCCESS 1
#define OK      1

#define RESET          1
#define NONRESET       0
#define OVERLIMIT      1
#define INLAW          0

#define TICK  10
#define TICKS 1000

/**Extern**/
extern int times;
extern int seconds;
extern char PrintT;
extern char PrintM;
extern char alarmStatus;
extern char KeyDone;
extern char update;



/**ADC*/
void Suntime();

void ADC_Setup(void);
void Light_Measure(void);
void ADC_Handler(void);
void Read_Light(void);
void Write_Light_Out(double light);
void Write_Grade_Out(double degree);

/**Alarm**/
typedef struct Alarm {
    double low;
    double high;
}Alarm;

void setAlarm (unsigned char current[]);
void resetAlarm (void);
void checkAlarm (double temperature);
void statusAlarm ();
void Set_Led();
void ledOn(void);
void ledOff(void);


/**Temperature**/
void Init_Temp(void);
void Temp_Measure(void);
void TC0_Handler(void);
int Update_Temp(void);

/**IN MAIM*/
void SysTick_Handler();

/**Delay**/
void Delay(int value);
/**Calender*/
void updateTime(struct LinkedList * tiger);


/**Display**/
void PrintMON(void);
void PrintMOFF(void);
void PrintON(void);
void PrintOFF(void);

void Write_Characters_2_Display(unsigned char key);
void Write_Command_2_Display(unsigned char command);
void Write_Data_2_Display(unsigned char data);
void Write_Key_Display(unsigned int key);
void Clear_Display();
unsigned char Read_Status_Display(void);
void Init_Display(void);
void Pin_Display(void);

void setPosition(int value);
void setPosition2(int value);
void setPosition3(int value);
void setPosition4(int value, int extra );

void PrintToScreen(char buff[]);
void PrintFromData(char key);
void writeValueDisplay(int value);

void PrintSunTime();
void PMemFull(List * list);
void PMem(List * list);
void Pdate(LinkedList *start);
void PAlarm();
void Write_Temp(int temperature);

/**keypad**/
int input(void);
int isBreak (int key);
int isUpdated (int key);
void inputArray(unsigned char *current, int a);
void setDate (unsigned char current[]);

/**Menu**/
void startMenu();

/**PWC**/
void PWM_Setup(void);
void Move_PWM(int key);

#endif