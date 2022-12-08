#include "TM1637Display.h"

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
  if (count == 0)
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
        
/* -----落牌單張----- */
        setRelayTime(Relay1, 2805, 2815);

/* -----落瀑布牌----- */
        setRelayTime(Relay2, 2895, 2899);

/* -----落球3------- */
        setRelayTime(Relay3, 2338, 2348);

/* -----落球2------- */
        setRelayTime(Relay4, 2243, 2253);

/* -----結尾蘋果----- */
        setRelayTime(Relay5, 0001, 0011);

/* -----落球1------- */
        setRelayTime(Relay6, 2150, 2160);

/* -----開場蘋果----- */
        //setRelayTime(Relay7, transTime(0,4), transTime(0,14));

/* -----緩降球------ */
        setRelayTime(Relay8, 2505, 2580);

/* -----落絲巾------ */
        setRelayTime(Relay9, 1835, 1844);

/* -----結尾落帽子--- */
        setRelayTime(Relay10, transTime(5,14), transTime(5,15.5));

/* -----五球5------- */
        setRelayTime(Relay11, 3098, 3128);

/* -----五球4------- */
        setRelayTime(Relay12, 3096, 3126);

/* -----五牌2------- */
        setRelayTime(Relay13, 3020, 3050);

/* -----五球3------- */
        setRelayTime(Relay14, 3094, 3124);

/* -----五球2------- */
        setRelayTime(Relay15, 3092, 3122);

/* -----五牌1------- */
        setRelayTime(Relay16, 3018, 3148);

/* -----五球1------- */
        setRelayTime(Relay17, 3090, 3120);

/* -----未使用1------ */
        //setRelayTime(Relay18, 0, 0);
        
/* -----未使用2------- */
        //setRelayTime(Relay19, 0, 0);

/* -----未使用3------- */
        //setRelayTime(Relay20, 0, 0);

/* -----伺服馬達1----- */
        setServoTime(servo1, transTime(4,33), 0);    //start out
        setServoTime(servo1, transTime(4,33.8), 90); //stop out
        setServoTime(servo1, transTime(4,34.5), 180);  //start back
        setServoTime(servo1, transTime(4,35.3), 90); //stop back
        setServoTime(servo1, transTime(4,36), 0);    //start out
        setServoTime(servo1, transTime(4,36.8), 90); //stop out
        setServoTime(servo1, transTime(4,38), 180);  //start back
        setServoTime(servo1, transTime(4,38.8), 90); //stop back

/* -----伺服馬達2----- */
        // servo2.write(0);
        // servo2.write(90);

/* -----伺服馬達2----- */
        // servo3.write(0);
        // servo3.write(90);

/* -----伺服馬達4----- */
        // servo4.write(0);
        // servo4.write(90);
      }
    }
    count++;
  }
}
