#include <TM1637Display.h>

const int WIRENUM = 8;

const int CLK = 3; //Set the CLK pin connection to the display
const int DIO = 2; //Set the DIO pin connection to the display

TM1637Display display(CLK, DIO);  //set up the 4-Digit Display.

int Sound = 0;
int Wire1 = 4;
int Wire2 = 5;
int Wire3 = 6;
int Wire4 = 7;  
int Wire5 = 8;
int Wire6 = 9;
int Wire7 = 10;
int Wire8 = 11;

int Trigger = 12;
int Led = 13;

int *wirelist[] = {&Wire1, &Wire2, &Wire3, &Wire4, &Wire5, &Wire6, &Wire7, &Wire8};
