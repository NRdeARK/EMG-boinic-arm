unsigned long TIME;
unsigned long lastTime;
unsigned long servoTime;
int i = 0;
int val;
int sum;
int diff = 10;
bool startAVG = false;
int average;
int data[100];
bool isActive = false;
#include <Servo.h>
Servo myservo;

void setup()
{
  Serial.begin(9600);
  lastTime = millis();
}

void loop()
{
  TIME = millis();
  if (TIME > lastTime + 10)
  {
    lastTime = TIME;
    i++;
    val = analogRead(A0);
    Serial.println(val);
    ///reset and start average cal
    if (i > 99)
    {
      i = 0;
      startAVG = true;
    }
    sum += val ;
    ///cal
    if (startAVG)
    {
      sum -= data[i];
      average = sum / 100;
    }
    data[i] = val;
    if (val > average + diff) {
      isActive = true;
      digitalWrite(13, 1);
    }
    if (val <= average) {
      isActive = false;
      digitalWrite(13, 0);
    }
  }
  if (isActive) {
    servoTime = TIME;
    myservo.write(180);
  }
  else {
    if (servoTime + 500 > TIME) {
      myservo.write(0);
    }
  }
}
