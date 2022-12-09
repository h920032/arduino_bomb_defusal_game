#include "pin_define.h"
#include "pitches.h"

int matchlist[] = {2, 5, 7, 3, 4, 1, 6, 8};
bool flag = true;
unsigned long countdown = 8 * 60 * 1000; //5400 max

unsigned long time[2] = {0, 0}; // 記錄運行時間
unsigned long timestart = 0;

int goodcount = 0;
int badcount = 0;
int statelist[WIRENUM];

int state = -1;
int transTime(int minTime, float secTime)
{
  return (minTime * 600 + secTime * 10);
}

uint8_t segto;

void checkstate(int **wirelist, int *statelist)
{
  for(int i = 0; i < WIRENUM; i++)
    statelist[i] = digitalRead(*wirelist[i]);
}

int checkbomb(int *statelist, int *matchlist, int *goodcount, int *badcount)
{
  int o_goodcount = *goodcount;
  int o_badcount = *badcount;
  for(int i = 0; i < WIRENUM; i++)
  {
    if(statelist[i])
    {
      if(matchlist[i] <= (WIRENUM / 2))
        *goodcount++;
      else
        *badcount++;
    }
  }
  if(*goodcount == 0)
    return 2;
  else if(o_badcount != *badcount)
    return 1;
  else 
    return 0;
}

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
  checkbomb(statelist, matchlist, &goodcount, &badcount);
 
  display.setBrightness(0x0a);  //set the diplay to maximum brightness
  display.clear();
  display.showNumberDec(0);
  segto = 0x80 | display.encodeDigit(0);
  display.setSegments(&segto, 1, 1);
  Serial.begin(9600);
}

void loop()
{
  display.clear();
  display.showNumberDec(0);
  segto = 0x80 | display.encodeDigit(0);
  display.setSegments(&segto, 1, 1);
  timestart = millis();
  flag = true;
  while (flag)
  {
    checkstate(wirelist, statelist);
    state = checkbomb(statelist, matchlist, &goodcount, &badcount);
    if(state != 0)
      flag = false;
    
    time[0] = millis() - timestart;
    if (time[1] != time[0])
    { 
      //避免1毫秒運行2次
      time[1] = time[0];

      if(time[0] % 10 >= 0 and time[0] % 10 < 4)
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
  if(state =! 2)
  {
    // bomb
    digitalWrite(Sound, HIGH);
    digitalWrite(Trigger, HIGH);
    delay(5000);
    digitalWrite(Sound, LOW);
    digitalWrite(Trigger, LOW);
    state = 2;
  }
}
