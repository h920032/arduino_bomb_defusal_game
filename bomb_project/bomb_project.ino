// This code is for a bomb defusal game.
// It uses the 8 wires to represent the bomb, and the buzzer to sound an alarm.

// The code starts by defining some constants, such as the pin numbers for the wires and the buzzer.
// It also defines a function, `transTime()`, which is used to convert the time into a number that can be displayed on the LED display.

// The `setup()` function initializes the Arduino's pins and starts the LED display.
// The `loop()` function is the main loop of the program.
// It checks the state of the wires and the buzzer, and takes appropriate action.

// The state of the game can be one of three:
// 0: The game is in progress.
// 1: The bomb has exploded.
// 2: The bomb has been defused.

// The code also includes some comments to explain the different parts of the code.

//Including header files
#include "pin_define.h"
#include "pitches.h"

//Array containing the sequence in which the wires need to be deactivated
int matchlist[] = {2, 5, 7, 3, 4, 1, 6, 8};

//Flag to check if bomb is active or not
bool flag = true;

//Setting countdown timer to 8 minutes (8*60000 milliseconds)
unsigned long countdown = 8 * 60000; //5400 max

//Array to hold time values
unsigned long time[2] = {0, 0};

//Start time variable
unsigned long timestart = 0;

//Variables to hold the count of correct and incorrect wire deactivation attempts
int goodcount = 0;
int badcount = 0;

//Array to hold the state of each wire (activated or deactivated)
int statelist[WIRENUM];

//Variable to hold the state of bomb
int state = -1;

//Function to convert minutes and seconds to milliseconds
int transTime(int minTime, float secTime)
{
  return (minTime * 600 + secTime * 10);
}

//Variable to hold the segment value for the 7-segment display
uint8_t segto;

//Function to check the state of each wire (if they are activated or deactivated)
void checkstate(int **wirelist, int *statelist)
{
  for(int i = 0; i < WIRENUM; i++)
    statelist[i] = digitalRead(*wirelist[i]);
}

//Function to check if the bomb is defused or not
int checkbomb(int *statelist, int *matchlist, int &goodcount, int &badcount)
{
  int o_goodcount = goodcount;
  int o_badcount = badcount;
  goodcount = 0;
  badcount = 0;
  for(int i = 0; i < WIRENUM; i++)
  {
    if(statelist[i] == 1)
    {
      if(matchlist[i] <= (WIRENUM / 2))
        goodcount++;
      else
        badcount++;
    }
  }
  if(o_goodcount > goodcount)
    return 2;
  else if(o_badcount > badcount)
    return 1;
  else 
    return 0;
}

//Initialization function to setup input and output pins
void setup()
{
  pinMode(Sound, OUTPUT);
  pinMode(Wire1, INPUT);
  pinMode(Wire2, INPUT);
  pinMode(Wire3, INPUT);
  pinMode(Wire4, INPUT);
  pinMode(Wire5, INPUT);
  pinMode(Wire6, INPUT);
  pinMode(Wire7, INPUT);
  pinMode(Wire8, INPUT);
  pinMode(Trigger, OUTPUT);
  pinMode(Led, OUTPUT);

  checkstate(wirelist, statelist);
  checkbomb(statelist, matchlist, goodcount, badcount);
 
  display.setBrightness(0x0a);  //set the diplay to maximum brightness
  display.clear();
  display.showNumberDec(0);
  segto = 0x80 | display.encodeDigit(0);
  display.setSegments(&segto, 1, 1);
  // Serial.begin(9600);
}

//Main loop function to manage bomb countdown, check wire states and display status
void loop()
{
  display.clear();
  display.showNumberDec(0);
  segto = 0x80 | display.encodeDigit(0);
  display.setSegments(&segto, 1, 1);
  timestart = millis();
  flag = true;
  //Continuously checks the state of the bomb and updates the countdown timer
  while (flag)
  {
    
    checkstate(wirelist, statelist);
    state = checkbomb(statelist, matchlist, goodcount, badcount);
    if(state != 0)
      flag = false;
    // Serial.println(state * 100 + goodcount * 10 + badcount);
    /*
    unsigned long target = 0;
    for(int i = 0; i < WIRENUM; i++)
    {
      target *= 10;
      target += statelist[i];
    }
    Serial.println(target);
    */
    
    time[0] = millis() - timestart;
    
    //Check if the bomb defusing attempt was successful or not
    if (time[1] != time[0])
    { 
      //避免1毫秒運行2次
      time[1] = time[0];

      if(time[0] % 1000 >= 0 and time[0] % 1000 < 100)
        digitalWrite(Sound, HIGH);
      else
        digitalWrite(Sound, LOW);
        
      int minute = (countdown - time[0]) / 60000;
      int second = ((countdown - time[0]) % 60000) / 1000;
      int t = (minute * 100 + second);
      display.showNumberDec(t);
      segto = 0x80 | display.encodeDigit(minute);
      display.setSegments(&segto, 1, 1);
      if (time[0] >= countdown)
        flag = false;
    }
  }
  // Serial.println(state);
  if(state == 1 or state == 0)
  {
    // bomb
    display.clear();
    display.showNumberDec(0);
    segto = 0x80 | display.encodeDigit(0);
    display.setSegments(&segto, 1, 1);
      
    digitalWrite(Sound, HIGH);
    digitalWrite(Trigger, HIGH);
    digitalWrite(Led, HIGH);
    delay(5000);
    digitalWrite(Sound, LOW);
    digitalWrite(Trigger, LOW);
    digitalWrite(Led, LOW);
    state = 2;
  }
  
  //Infinite loop to halt the execution once the bomb is defused or triggered
  while(!flag)
  {
    
  }
}
