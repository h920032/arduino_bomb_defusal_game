#include "pin_define.h"
#include "pitches.h"

int matchlist[] = {2, 5, 7, 3, 4, 1, 6, 8};
bool flag = true;
unsigned long countdown = 8 * 60 * 1000; //5400 max

unsigned long time[2] = {0, 0}; // 記錄運行時間
unsigned long timestart = 0;

int goodcount = 0;
int badcount = 0;

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

  int *wirelist[] = {&Wire1, &Wire2, &Wire3, &Wire4, &Wire5, &Wire6, &Wire7, &Wire8};
  int statelist[WIRENUM];
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
    time[0] = millis() - timestart;
    if (time[1] != time[0])
    { 
      //避免1毫秒運行2次
      time[1] = time[0];
      int minute = (countdown - time[0]) / 60000;
      int second = ((countdown - time[0]) % 60000) / 1000;
      int t = (minute * 100 + second);
      display.showNumberDec(t);
      segto = 0x80 | display.encodeDigit(minute);
      display.setSegments(&segto, 1, 1);
      if (time[0] >= countdown)
      {
        flag = false;
      }
    }
  }
}
