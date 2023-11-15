#include "system_sam3x.h"
#include "at91sam3x8.h"
#include "Mission.h"

char LS1Flag = 0;
char LS2Flag = 0;
char Dark = 0;
char Sun  = 0;
extern char ReadLight;
extern char Shyne;
extern char fullsize;
char ShyneTime = 0;
char DarkTime = 0;
char SunTime = 0;
char OnDay = 0;
int  degree;


void Suntime(){
    if (degree == 0 || degree == 180 ){
        Dark = 1;
        Sun  = 0;
    } else {
        Sun  = 1;
        Dark = 0;
    }

    if (SunTime + ShyneTime < 17 && Dark == 1 && OnDay == 1){
        ledOn();
        if(Shyne == 1){
            ledOn();
        }
    }

    if(ShyneTime + SunTime >= 17 || Sun == 1 || OnDay == 0){
        ledOff();
        if(Shyne == 0){
            ledOff();
        }
    }
}

void ADC_Setup(void){
    *AT91C_PMC_PCER = (1 << 11); // Enable PMC_PIOA
    *AT91C_PMC_PCER1 = (1 << 5); // Start clock for ADC
    *AT91C_ADCC_MR = (1 << 9);
    *AT91C_ADCC_CHER = (1 << 1); // select channel in ADC_CHER 1
    *AT91C_ADCC_CHER = (1 << 2); // select channel in ADC_CHER 2
    NVIC_ClearPendingIRQ((IRQn_Type) 37);
    NVIC_SetPriority((IRQn_Type) 37, 0);
    NVIC_EnableIRQ((IRQn_Type) 37);
}
 
void Light_Measure(void){
    *AT91C_ADCC_CR = (1 << 1);  // Start an ADC in ADC_CR
    *AT91C_ADCC_IER = (1 << 1); // End of Conversion
    *AT91C_ADCC_IER = (1 << 2); // End of Conversion
}

void ADC_Handler(void){
    int x = *AT91C_ADCC_SR;     // get the one that triggered
    if ((x & (1 << 1)) == (1 << 1)){
        *AT91C_ADCC_IDR = (1 << 1); // Disable interrupt for ADC5
        *AT91C_ADCC_IDR = (1 << 2); // Disable interrupt for ADC6
        LS1Flag = 1;
    }
    if ((x & (1 << 2)) == (1 << 2)){
        LS2Flag = 1;
        *AT91C_ADCC_IDR = (1 << 1); // Disable interrupt for ADC5
        *AT91C_ADCC_IDR = (1 << 2); // Disable interrupt for ADC6
    }
}

void Read_Light(void){
    Light_Measure();
    double sensor1 = 0;
    double sensor2 = 0;
    if (LS1Flag != 0) // Light Sensor 1 Has a new value
        return;

    setPosition(2);
    sensor1 = (*AT91C_ADCC_CDR1 * 3.3)/0xF;
    LS1Flag = 0;
    sensor2 = 2*(*AT91C_ADCC_CDR2 * 3.3)/0xF;
    LS2Flag = 0;

    if (ReadLight == 1 && fullsize != 1) {
        PrintToScreen(" Degree: ");
    }
    double delta_degree = sensor2 - sensor1;
    if (delta_degree > 90)
      delta_degree = 90;
    else if(delta_degree < -90)
      delta_degree = -90;
    if(delta_degree >= -90)
      degree = delta_degree * (-1) + 90;
    else 
      degree = delta_degree;

    if (ReadLight == 1 && fullsize != 1) {
        Write_Grade_Out(degree);
    }

    if (ReadLight == 1){
        Move_PWM(degree);
        setPosition4(0,27);
        PrintToScreen("MOVE");
    } else {
        setPosition4(0,27);
        PrintToScreen("STOP");
    }
}

void Write_Light_Out(double light) {
    double temp[] = {0,0,0,0};
    int count = 0;
    double save;

    for (int x = light * 100; count < 4; count++) {
        save = x % 10;
        temp[count] = save;
        x = x / 10;
    }

    if (count > 3)
        count = 3;

    writeValueDisplay(0x10 + temp[count - 2]);
    PrintToScreen(".");

    for (int i = count - 3; i >= 0; i--) {
        writeValueDisplay(0x10 + temp[i]);
    }
}

void Write_Grade_Out(double degree) {
    if (degree < 10){
        PrintToScreen("  ");
        writeValueDisplay(degree);
        return;
    } else if (degree < 100){
        PrintToScreen(" ");
        writeValueDisplay(degree);
        return;
    } else {
        writeValueDisplay(degree);
        return;
    }
}