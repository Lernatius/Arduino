#include <Servo.h>
#include <Wire.h>




#define uslt A2
#define usle A3
#define usft A0
#define usfe A1
#define usrt 12
#define usre 13

#define qtr 11

#define lcdsda A4
#define lcdscl A5

#define infrared 5

#define firesensor 2

#define motorin1 8
#define motorin2 4
#define motorin3 7
#define motorin4 9
#define motoren1 3
#define motoren2 5


int error;
Servo brushless;
Servo servo1;
int fanspeed;
float cm, leftdistance, frontdistance, rightdistance;

void setup() {
  Serial.begin(9600);
  pinMode(usle, INPUT);
  pinMode(usfe, INPUT);
  pinMode(usre, INPUT);

  pinMode(uslt, OUTPUT);
  pinMode(usft, OUTPUT);
  pinMode(usrt, OUTPUT);

  pinMode(motorin1, OUTPUT);
  pinMode(motorin2, OUTPUT);
  pinMode(motorin3, OUTPUT);
  pinMode(motorin4, OUTPUT);
  pinMode(motoren1, OUTPUT);
  pinMode(motoren2, OUTPUT);

  pinMode(firesensor, INPUT);

  //attachInterrupt(0, dampfire, HIGH);

  brushless.attach(6);
  servo1.attach(11);
  brushless.write(40);
  servo1.write(50);
  delay(4000);

  fanspeed = 120;
}

void wallfallow()
{
  measure();
  error = 30 * (rightdistance - 10);
  if (frontdistance >= 13)
  {
    if (rightdistance >= 10 && rightdistance <= 18)
    {
      moveforward(225, 225 - error);
    }
    else if (rightdistance < 10)
    {
      moveforward(225 + error, 255);
    }
    else
    {
      moveforward(100, 100);
      delay(300);
      moveforward(120, 0);
      delay(700);
      moveforward(100, 100);
      delay(500);
      measure();
      if (rightdistance >= 20)
      {
        moveforward(0, 0);
        delay(300);
        controlroom();
        moveback(100, 100);
        delay(500);
        moveback(120, 0);
        delay(700);
        measure();
        if (frontdistance < 35)
        {
          while (frontdistance > 14)
          {
            moveforward(100, 100);
            measure();
          }
        }
        else
        {
          moveforward(255, 255);
          delay(500);
        }
      }
    }

  }
  else
  {
    stopmotor(120, 120);
    moveforward(0, 255);
    delay(550);
    stopmotor(0, 120);
  }
}

void controlroom()
{
  for (int i = 0; i < 14; i++)
  {
    if (digitalRead(firesensor) == 1)
    {
      fan(true);
      delay(1000);

    }
    else
    {
      fan(false);
    }
    servo1.write(48 + i);
    delay(250);
  }
  servo1.write(55);
}



void measure()
{
  digitalWrite(uslt, LOW);
  delayMicroseconds(5);
  digitalWrite(uslt, HIGH);
  delayMicroseconds(10);
  digitalWrite(uslt, LOW);
  leftdistance = pulseIn(usle, HIGH) / 58.2;
  delay(1);
  digitalWrite(usft, LOW);
  delayMicroseconds(5);
  digitalWrite(usft, HIGH);
  delayMicroseconds(10);
  digitalWrite(usft, LOW);
  frontdistance = pulseIn(usfe, HIGH) / 58.2;
  delay(1);
  digitalWrite(usrt, LOW);
  delayMicroseconds(5);
  digitalWrite(usrt, HIGH);
  delayMicroseconds(10);
  digitalWrite(usrt, LOW);
  rightdistance = pulseIn(usre, HIGH) / 58.2;
  delay(1);
}






void fan(boolean f)
{
  if (f == true)
  {
    brushless.write(fanspeed);
  }
  else
  {
    brushless.write(40);
  }
}

void dampfire()
{
  fan(true);
  delay(700);
  fan(false);
}

void moveforward(int l, int r)
{
  digitalWrite(motorin1, HIGH);
  digitalWrite(motorin2, LOW);
  digitalWrite(motorin3, HIGH);
  digitalWrite(motorin4, LOW);

  analogWrite(motoren1, l);
  analogWrite(motoren2, r);
}

void moveback(int l, int r)
{
  digitalWrite(motorin1, LOW);
  digitalWrite(motorin2, HIGH);
  digitalWrite(motorin3, LOW);
  digitalWrite(motorin4, HIGH);

  analogWrite(motoren1, l);
  analogWrite(motoren2, r);
}

void stopmotor(int l, int r)
{
  digitalWrite(motorin1, LOW);
  digitalWrite(motorin2, HIGH);
  digitalWrite(motorin3, LOW);
  digitalWrite(motorin4, HIGH);

  analogWrite(motoren1, l);
  analogWrite(motoren2, r);

  delay(40);
}

void loop()
{
  measure();
   wallfallow();
  controlroom();
}
