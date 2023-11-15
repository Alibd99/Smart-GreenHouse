#include "system_sam3x.h"
#include "at91sam3x8.h"
#include <stdio.h>
#include "Mission.h"

extern Alarm alarm;
extern char DarkTime;
extern char ShyneTime;
extern char SunTime;
char PrintM = OFF;
char PrintT = OFF;

void PrintSunTime (){
    setPosition4(0, 32);
    PrintToScreen("S+D|");
    writeValueDisplay(SunTime );
    PrintToScreen("+");
    writeValueDisplay(ShyneTime );
    if (ShyneTime < 10 && SunTime < 10){
        PrintToScreen("H");
    }
}

void PrintMON(){
    PrintM = ON;
}

void PrintMOFF(){
    PrintM = OFF;
}

void PrintON(){
    PrintT = ON;
}

void PrintOFF(){
    PrintT = OFF;
}

void PrintFromData(char key){
    key = key - ' ';
    Write_Data_2_Display(key);
    Write_Command_2_Display(0xC0);
}

void PrintToScreen(char buff[]){
    int i = 0;
    while (buff[i] != '\0'){
        PrintFromData(buff[i]);
        i++;
    }
}

void writeValueDisplay(int value){
    char cValue[50];
    sprintf(cValue, "%d", value);
    PrintToScreen(cValue);
}

void PMemFull(List * list){
    Clear_Display();
    LinkedList *currNode = list->head;
    setPosition4(2, 0);
    PrintToScreen(" 9.Back");
    setPosition4(3, 0);
    PrintToScreen(" Contains ");
    writeValueDisplay(list->size);
    if(list->size < 2){
        PrintToScreen(" Day");
    } else {
        PrintToScreen(" Days");
    }

    if (currNode == NULL) {
        setPosition4(5,0);
        PrintToScreen(" List is Empty!");
        setPosition4(9,0);
        PrintToScreen("Please Waiting...");
        return;
    }

    /**Write Head Content**/
    int moves = 1;
    int move = 5;
    while (currNode != NULL) {
        setPosition4(move, 0);
        PrintToScreen("Date:");
        /** Write Date **/
        if (currNode->days < 10)
            PrintToScreen("0");
        writeValueDisplay(currNode->days);
        PrintToScreen("/");
        if (currNode->months < 10)
            PrintToScreen("0");
        writeValueDisplay(currNode->months);
        PrintToScreen("/");
        if (currNode->years < 1000)
            PrintToScreen("0");
        if (currNode->years < 100)
            PrintToScreen("0");
        if (currNode->years < 10)
            PrintToScreen("0");
        writeValueDisplay(currNode->years);

        /** Write Temperature **/
        PrintToScreen("|");//3
        if (currNode->sensorData < 10) {
            PrintToScreen("0");
        }
        writeValueDisplay(currNode->sensorData);
        move++;


        setPosition4(move, 0);
        /** Write Time and Max**/
        PrintToScreen("Max :");
        if (currNode->max->hours < 10)
            PrintToScreen("0");
        writeValueDisplay(currNode->max->hours);
        PrintToScreen(":");

        if (currNode->max->minutes < 10)
            PrintToScreen("0");
        writeValueDisplay(currNode->max->minutes);
        PrintToScreen(":");

        if (currNode->max->seconds < 10)
            PrintToScreen("0");
        writeValueDisplay(currNode->max->seconds);
        PrintToScreen("|");

        if (currNode->max->temperature < 10)
            PrintToScreen("0");
        writeValueDisplay(currNode->max->temperature);
        move++;


        setPosition4(move, 0);
        /** Write Time and Min**/
        PrintToScreen("Min :");
        if (currNode->min->hours < 10)
            PrintToScreen("0");
        writeValueDisplay(currNode->min->hours);
        PrintToScreen(":");

        if (currNode->min->minutes < 10)
            PrintToScreen("0");
        writeValueDisplay(currNode->min->minutes);
        PrintToScreen(":");

        if (currNode->min->seconds < 10)
            PrintToScreen("0");
        writeValueDisplay(currNode->min->seconds);
        PrintToScreen("|");

        if (currNode->min->temperature < 10)
            PrintToScreen("0");
        writeValueDisplay(currNode->min->temperature);
        move += 2;

        if (move >= 18){
            setPosition4(moves, 20);
            PrintToScreen("Date:");
            /** Write Date **/
            if (currNode->days < 10)
                PrintToScreen("0");
            writeValueDisplay(currNode->days);
            PrintToScreen("/");
            if (currNode->months < 10)
                PrintToScreen("0");
            writeValueDisplay(currNode->months);
            PrintToScreen("/");
            if (currNode->years < 1000)
                PrintToScreen("0");
            if (currNode->years < 100)
                PrintToScreen("0");
            if (currNode->years < 10)
                PrintToScreen("0");
            writeValueDisplay(currNode->years);


            /** Write Temperature **/
            PrintToScreen("|");
            if (currNode->sensorData < 10) {
                PrintToScreen("0");
            }
            writeValueDisplay(currNode->sensorData);
            moves++;


            setPosition4(moves, 20);
            /** Write Time and Max**/
            PrintToScreen("Max :");
            if (currNode->max->hours < 10)
                PrintToScreen("0");
            writeValueDisplay(currNode->max->hours);
            PrintToScreen(":");

            if (currNode->max->minutes < 10)
                PrintToScreen("0");
            writeValueDisplay(currNode->max->minutes);
            PrintToScreen(":");

            if (currNode->max->seconds < 10)
                PrintToScreen("0");
            writeValueDisplay(currNode->max->seconds);
            PrintToScreen("|");

            if (currNode->max->temperature < 10)
                PrintToScreen("0");
            writeValueDisplay(currNode->max->temperature);
            moves++;


            setPosition4(moves, 20);
            /** Write Time and Min**/
            PrintToScreen("Min :");
            if (currNode->min->hours < 10)
                PrintToScreen("0");
            writeValueDisplay(currNode->min->hours);
            PrintToScreen(":");

            if (currNode->min->minutes < 10)
                PrintToScreen("0");
            writeValueDisplay(currNode->min->minutes);
            PrintToScreen(":");

            if (currNode->min->seconds < 10)
                PrintToScreen("0");
            writeValueDisplay(currNode->min->seconds);
            PrintToScreen("|");

            if (currNode->min->temperature < 10)
                PrintToScreen("0");
            writeValueDisplay(currNode->min->temperature);
            moves += 2;
        }
        currNode = currNode->next;
    }
}

void PMem(List * list){
    LinkedList *currNode = list->head;
    if (currNode == NULL) {
        setPosition4(1,22);
        PrintToScreen("List is Empty!");
        return;
    }
    else{
        setPosition4(1,22);
        PrintToScreen("~~~~~~~~~~~~~~~");
    }
      

    /**Write Head Content**/
    int move = 4;

    /**Oldest Recording*/
    setPosition4(move,19);
    PrintToScreen("Oldest Recording");
    move+=2;
    setPosition4(move,19);
    PrintToScreen("Date:");
    /** Write Date **/
    if (currNode->days < 10)
        PrintToScreen("0");
    writeValueDisplay(currNode->days);

    if (currNode->months < 10)
        PrintToScreen("0");
    writeValueDisplay(currNode->months);

    if (currNode->years < 1000)
        PrintToScreen("0");
    if (currNode->years < 100)
        PrintToScreen("0");
    if (currNode->years < 10)
        PrintToScreen("0");
    writeValueDisplay(currNode->years);

    /** Write Temperature **/
    PrintToScreen(" - ");
    if (currNode->sensorData < 10){
        PrintToScreen("0");
    }
    writeValueDisplay(currNode->sensorData);
    move++;


    setPosition4(move,19);
    /** Write Time and Max**/
    PrintToScreen(" Max:");
    if (currNode->max->hours < 10)
        PrintToScreen("0");
    writeValueDisplay(currNode->max->hours);
    PrintToScreen(":");

    if (currNode->max->minutes < 10)
        PrintToScreen("0");
    writeValueDisplay(currNode->max->minutes);
    PrintToScreen(":");

    if (currNode->max->seconds < 10)
        PrintToScreen("0");
    writeValueDisplay(currNode->max->seconds);
    PrintToScreen(" ");

    if (currNode->max->temperature < 10)
        PrintToScreen("0");
    writeValueDisplay(currNode->max->temperature);
    PrintToScreen(" ");
    PrintToScreen("Size");
    move++;

    setPosition4(move,19);
    /** Write Time and Min**/
    PrintToScreen(" Min:");
    if (currNode->min->hours < 10)
        PrintToScreen("0");
    writeValueDisplay(currNode->min->hours);
    PrintToScreen(":");

    if (currNode->min->minutes < 10)
        PrintToScreen("0");
    writeValueDisplay(currNode->min->minutes);
    PrintToScreen(":");

    if (currNode->min->seconds < 10)
        PrintToScreen("0");
    writeValueDisplay(currNode->min->seconds);
    PrintToScreen(" ");

    if (currNode->min->temperature < 10)
        PrintToScreen("0");
    writeValueDisplay(currNode->min->temperature);
    PrintToScreen(" ");
    if (currNode->store < 10){
        PrintToScreen("  ");
    } else if (currNode->store < 100) {
        PrintToScreen(" ");
    }
    writeValueDisplay(currNode->store);
//--------------------------------------------------------------------------------------------------------------------
    /**New Recording **/
    currNode = list->tail;

    setPosition4(move+2,19);
    PrintToScreen("Newest Recording");
    move += 2;
    setPosition4(12,19);
    PrintToScreen("Date:");
    /** Write Date **/
    if (currNode->days < 10)
        PrintToScreen("0");
    writeValueDisplay(currNode->days);

    if (currNode->months < 10)
        PrintToScreen("0");
    writeValueDisplay(currNode->months);

    if (currNode->years < 1000)
        PrintToScreen("0");
    if (currNode->years < 100)
        PrintToScreen("0");
    if (currNode->years < 10)
        PrintToScreen("0");
    writeValueDisplay(currNode->years);

    /** Write Temperature **/
    PrintToScreen(" - ");
    if (currNode->sensorData < 10){
        PrintToScreen("0");
    }
    writeValueDisplay(currNode->sensorData);
    move++;


    setPosition4(move+2,19);
    /** Write Time and Max**/
    PrintToScreen(" Max:");
    if (currNode->max->hours < 10)
        PrintToScreen("0");
    writeValueDisplay(currNode->max->hours);
    PrintToScreen(":");

    if (currNode->max->minutes < 10)
        PrintToScreen("0");
    writeValueDisplay(currNode->max->minutes);
    PrintToScreen(":");

    if (currNode->max->seconds < 10)
        PrintToScreen("0");
    writeValueDisplay(currNode->max->seconds);
    PrintToScreen(" ");

    if (currNode->max->temperature < 10)
        PrintToScreen("0");
    writeValueDisplay(currNode->max->temperature);
    PrintToScreen(" ");
    PrintToScreen("Size");
    move++;

    setPosition4(move+2,19);
    /** Write Time and Min**/
    PrintToScreen(" Min:");
    if (currNode->min->hours < 10)
        PrintToScreen("0");
    writeValueDisplay(currNode->min->hours);
    PrintToScreen(":");

    if (currNode->min->minutes < 10)
        PrintToScreen("0");
    writeValueDisplay(currNode->min->minutes);
    PrintToScreen(":");

    if (currNode->min->seconds < 10)
        PrintToScreen("0");
    writeValueDisplay(currNode->min->seconds);
    PrintToScreen(" ");

    if (currNode->min->temperature < 10)
        PrintToScreen("0");
    writeValueDisplay(currNode->min->temperature);
    PrintToScreen(" ");
    if (currNode->store < 10){
        PrintToScreen("  ");
    } else if (currNode->store < 100) {
        PrintToScreen(" ");
    }
    writeValueDisplay(currNode->store);

}

void PAlarm(){
    /** Write Alarm **/
    setPosition(5);
    PrintToScreen(" High Temp : ");
    if (alarm.high < 10)
        PrintToScreen("0");
    writeValueDisplay(alarm.high);

    setPosition(6);
    PrintToScreen(" Low  Temp : ");
    if (alarm.low < 10)
        PrintToScreen("0");
    writeValueDisplay(alarm.low);
}

void Pdate(LinkedList *temp) {
    /** Write Date **/
    setPosition(0);
    //PrintToScreen("Date: ");

    if (temp->days < 10)
        PrintToScreen("0");
    writeValueDisplay(temp->days);
    PrintToScreen("/");

    if (temp->months < 10)
        PrintToScreen("0");
    writeValueDisplay(temp->months);
    PrintToScreen("/");

    if (temp->years < 1000)
        PrintToScreen("0");
    if (temp->years < 100)
        PrintToScreen("0");
    if (temp->years < 10)
        PrintToScreen("0");
    writeValueDisplay(temp->years);
    PrintToScreen("  ");

    /** Write Time **/
    //setPosition(1);
    //PrintToScreen("Time: ");

    if (temp->hours < 10)
        PrintToScreen("0");
    writeValueDisplay(temp->hours);
    PrintToScreen(":");

    if (temp->minutes < 10)
        PrintToScreen("0");
    writeValueDisplay(temp->minutes);
    PrintToScreen(":");

    if (temp->seconds < 10)
        PrintToScreen("0");
    writeValueDisplay(temp->seconds);
    PrintToScreen("  ");
}

void Write_Temp(int temperature){
    /** Write Temperature **/

    if (temperature < 10){
        PrintToScreen("0");
    }
    writeValueDisplay(temperature);
    PrintToScreen("*C");
}

void setPosition(int value){
    int row = value;
    Write_Data_2_Display(row*40);
    Write_Data_2_Display((row*40)>>8);
    Write_Command_2_Display(0x24);
}

void setPosition2(int value){
    int row = value;
    Write_Data_2_Display(row*40+20);
    Write_Data_2_Display((row*40+20)>>8);
    Write_Command_2_Display(0x24);
}

void setPosition3(int value){
    int row = value;
    Write_Data_2_Display(row*40+18);
    Write_Data_2_Display((row*40+18)>>8);
    Write_Command_2_Display(0x24);
}

void setPosition4(int value, int extra ){
    int row = value;
    Write_Data_2_Display(row*40+extra);
    Write_Data_2_Display((row*40+extra)>>8);
    Write_Command_2_Display(0x24);
}

void Write_Characters_2_Display(unsigned char key) {
    int temp[5];
    for (int i = 0; (key % 10) != 0; i++){
        temp[i] = key % 10;
        key = key / 10;
    }
    int i = sizeof(temp)/sizeof(temp[0]);
    while (i >= 0){
        Write_Key_Display(temp[i]);
        i--;
    }
}

void Write_Command_2_Display(unsigned char command){
    // Wait until Read_Status_Display returns OK
    while((~Read_Status_Display() & (0xC)) == 0xC) {}

    *AT91C_PIOC_OER = (0x2F << 12);    // make databus as input
    *AT91C_PIOC_OER = (0xFF << 2);    // make databus as input

    *AT91C_PIOC_CODR = (0xFF << 2); // Clear databus
    *AT91C_PIOC_SODR = (command << 2); // Set Command to databus (To get back the 2 zeroes) PC(2-9)
    *AT91C_PIOC_CODR = (1 << 13); // Set dir as output (74chip)
    *AT91C_PIOC_CODR = (1 << 12); // Enable 'output' (74chip)
    *AT91C_PIOC_OER = (0xFF << 2); // Set databus as output
    *AT91C_PIOC_SODR = (1 << 14); // Set C/D signal High (1 = Command) //CD High gives Command Write then WR = Low
    *AT91C_PIOC_CODR = (1 << 15); // Clear chip select display
    *AT91C_PIOC_CODR = (1 << 17); // Clear write display
    Delay(20); // Make a Delay
    *AT91C_PIOC_SODR = (1 << 15); // Set chip enable display
    *AT91C_PIOC_SODR = (1 << 17); // Set write display
    *AT91C_PIOC_SODR = (1 << 12);// Disable output (74chip)
    *AT91C_PIOC_ODR = (0xFF << 2); // Make databus as input
}

void Write_Data_2_Display(unsigned char data){
    // Wait until Read_Status_Display returns an OK
    while((~Read_Status_Display() & (0xC)) == 0xC) {}

    *AT91C_PIOC_OER = (0x2F << 12); // Set databus as output
    *AT91C_PIOC_OER = (0xFF << 2); // Set databus as output

    *AT91C_PIOC_CODR = (0xFF << 2); // Clear databus
    *AT91C_PIOC_SODR = (data << 2);// Set "data" to databus
    *AT91C_PIOC_CODR = (1 << 13); // Set dir as output (74chip)
    *AT91C_PIOC_CODR = (1 << 12); // Enable 'output' (74chip)
    *AT91C_PIOC_OER = (0xFF << 2); // Set databus as output
    *AT91C_PIOC_CODR = (1 << 14); // Set C/D signal Low (0 = data) //CD Low gives Data Write then WR = Low
    *AT91C_PIOC_CODR = (1 << 15); // Clear chip select display
    *AT91C_PIOC_CODR = (1 << 17); // Clear write display

    Delay(20); // Make a Delay

    *AT91C_PIOC_SODR = (1 << 15); // Set chip enable display
    *AT91C_PIOC_SODR = (1 << 17); // Set write display
    *AT91C_PIOC_SODR = (1 << 12);// Disable output (74chip)
    *AT91C_PIOC_ODR = (0xFF << 2); // Make databus as input
}

void Write_Key_Display(unsigned int key){
    // Write on display
    int data = 0x00;
    if (key  == 1)
      data = 0x11;
    else if (key == 2)
      data = 0x12;
    else if (key == 3)
      data = 0x13;
    else if (key == 4)
      data = 0x14;
    else if (key == 5)
      data = 0x15;
    else if (key == 6)
      data = 0x16;
    else if (key == 7)
      data = 0x17;
    else if (key == 8)
      data = 0x18;
    else if (key == 9)
      data = 0x19;
    else if (key == 10) // *
      data = 0x0A;
    else if (key == 11) // 0
      data = 0x10;
    else if (key == 12) // #
      data = 0x03;
    else if (key == 13)
      data = 0x30;
    else
      return;
    // Write the data, by incrementing ADPeach time written
    Write_Data_2_Display(data);
    Write_Command_2_Display(0xC0);

    // Write the data, by Setting space between every pixel
    Write_Data_2_Display(0x00);
    Write_Command_2_Display(0xC0);
}

void Clear_Display(){
    //Set Cursor at (x,y) -> (0,0)
    Write_Data_2_Display(0x00); // start from (0,0)
    Write_Data_2_Display(0x00); // start from (0,0)
    Write_Command_2_Display(0x24); // Set adress pointer
    Write_Command_2_Display(0xB0);
    // colomn 32, 40, 64, 80(0x28)
    // row 2, 4, 6 ,8 ,10, 12, 14, 16, 20, 24, 28, 32(0x10)
    for (int x = 0; x < 640; x++){ // loop for colomn and row 32 * 20

        // Write "nothing" into each "pixel" of the screen
        Write_Data_2_Display(0x00); // start from (0,0)

    }
    Write_Command_2_Display(0xB2);
    //Re-Set Cursor at (x,y) -> (0,0)
    Write_Data_2_Display(0x00); // start from (0,0)
    Write_Data_2_Display(0x00); // start from (0,0)
    Write_Command_2_Display(0x24);  // Set adress pointer
}

unsigned char Read_Status_Display(){
    unsigned char temp;

    *AT91C_PIOC_OER = (0x1F << 12);    // make databus as input
    *AT91C_PIOC_ODR = (0xFF << 2);    // make databus as input

    *AT91C_PIOC_SODR = (1 << 13);   // Set dir as input
    *AT91C_PIOC_CODR = (1 << 12);   // Clear/enable output (74chip 0 = enable)
    *AT91C_PIOC_SODR = (1 << 14);     // Set C/D
    *AT91C_PIOC_CODR = (1 << 15);   // Clear chip select display  CE
    *AT91C_PIOC_CODR = (1 << 16); // Clear read display
    Delay(25); // Make a Delay
    temp = (*AT91C_PIOC_PDSR & (0xFF << 2));// Read data bus and save it in temp (PSDR?)
    *AT91C_PIOC_SODR = (1 << 15);// Set chip select display
    *AT91C_PIOC_SODR = (1 << 16);// Set read display
    *AT91C_PIOC_SODR = (1 << 12); // Disable output (74chip)
    *AT91C_PIOC_CODR = (1 << 13); // Set dir as output (74chip)
    return temp;
}

void Init_Display(){
    Pin_Display();
    *AT91C_PIOD_CODR = (0x1);   // Reset Screen
    Delay(10);              // 10ms of delay for the screen to start and such
    *AT91C_PIOD_SODR = (0x1);   // Make the display act normal

    Write_Data_2_Display(0x00);
    Write_Data_2_Display(0x00);
    Write_Command_2_Display(0x40);//Set text home address
    Write_Data_2_Display(0x00);
    Write_Data_2_Display(0x40);
    Write_Command_2_Display(0x42); //Set graphic home address
    Write_Data_2_Display(0x28);
    Write_Data_2_Display(0x00);
    Write_Command_2_Display(0x41); // Set text area
    Write_Data_2_Display(0x1e);
    Write_Data_2_Display(0x00);
    Write_Command_2_Display(0x43); // Set graphic area
    Write_Command_2_Display(0x80); // text mode
    Write_Command_2_Display(0x94); // Text on graphic off
}

void Pin_Display(){
    *AT91C_PMC_PCER = (1 << 13); //PIOD
    *AT91C_PMC_PCER = (1 << 14);// PIOC

    *AT91C_PIOC_PER =     (0xFFF << 12); // enable  pin
    *AT91C_PIOC_PER =     (0x3FC); // enable  pin

    *AT91C_PIOD_PER =     (0x1); // enable reset

    *AT91C_PIOC_PPUDR =     (0xFFF << 12); // disable  pin
    *AT91C_PIOC_PPUDR =     (0x3FC); // disable  pin
    *AT91C_PIOD_PPUDR =     (0x1); //  disable reset

    *AT91C_PIOD_OER =     (0x1); //  disble input RESET
    *AT91C_PIOC_OER =     (1 << 18); // disble input FS
    *AT91C_PIOC_OER =     (1 << 19); // disble input PV
    *AT91C_PIOC_SODR =     (1 << 18); // Set FS
    *AT91C_PIOC_CODR =     (1 << 19); // Clear RV

    *AT91C_PIOC_OER =     (1<<12); // output enable Display OE
    *AT91C_PIOC_OER =     (1<<13); // Output enable Direction
}

