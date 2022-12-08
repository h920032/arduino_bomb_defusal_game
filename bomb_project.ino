#include "pin_define.h"

int MatchTable[] = {2, 5, 7, 3, 4, 1, 6, 8};

bool flag = true;
unsigned long endtime = 600; //5400 max

unsigned long time[2] = {0, 0}; // 記錄運行時間
unsigned long timestart = 0;

int transTime(int minTime, float secTime)
{
  return (minTime * 600 + secTime * 10);
}

uint8_t segto;

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
      int minute = time[0] / 60000;
      int second = (time[0] % 60000) / 1000;
      int t = (minute * 100 + second);
      display.showNumberDec(t);
      segto = 0x80 | display.encodeDigit(minute);
      display.setSegments(&segto, 1, 1);
      if (time[0] >= endtime*7200)
      {
        flag = false;
      }
    }
  }
}
