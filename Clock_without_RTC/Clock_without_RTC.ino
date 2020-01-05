#include "SevSeg.h"
SevSeg Display;


const unsigned long period = 1000; //one second
const unsigned long led_period = 500; //LED blink millisecond
unsigned long startMillis=0;
unsigned long led_startMillis=0;
unsigned long currentMillis;
unsigned long led_currentMillis;
const int hrs_btn = A0;
const int min_btn = A1;
const int ledPin = A2;
int Hrs = 22;
int Min = 45;
int Sec = 0;
int Time;
int ledState = LOW;
void setup()
{
  pinMode(hrs_btn, INPUT_PULLUP);
  pinMode(min_btn, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  byte numDigits = 4;
  byte digitPins[] = {7,8,9,10};
  byte segmentPins[] = {0,1,2,3,4,5,6};
  bool updateWithDelaysIn = true;
  byte hardwareConfig = COMMON_ANODE;
  Display.begin(hardwareConfig, numDigits, digitPins, segmentPins);
  Display.setBrightness(100);
}
void loop()
{
  currentMillis = millis();
  if (currentMillis - startMillis >= period)
  {
    Sec = Sec + 1;
    startMillis = currentMillis;
  } 
  if (Sec == 60)
  {
    Sec = 0;
    Min = Min + 1;
  }
  if (Min == 60)
  {
    Min = 0;
    Hrs = Hrs + 1;
  }
  if (Hrs == 24)
  {
    Hrs = 0;
  }

  led_currentMillis = millis();
  if (led_currentMillis - led_startMillis >= led_period)
  {
    led_startMillis = led_currentMillis;
    if (ledState == LOW)
    {
      ledState = HIGH;
      if (digitalRead(hrs_btn) == LOW)
      {
        Hrs = Hrs + 1;
      }
      if (digitalRead(min_btn) == LOW)
      {
        Min = Min + 1;
        Sec = 0;
      }
    }
    else
    {
      ledState = LOW;
    }
    digitalWrite(ledPin, ledState);
  }
  Time = (Hrs*100) + Min;
  Display.setNumber(Time,3);
  Display.refreshDisplay();
}
