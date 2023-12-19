#include <Servo.h>

Servo horizontal; // horizontal servo
int servoh = 180; 
int servohLimitHigh = 175;
int servohLimitLow = 5; 

Servo vertical; // vertical servo
int servov = 45;
int servovLimitHigh = 100;
int servovLimitLow = 1;

// LDR pin connections
// name = analogpin;
int ldrlt = A0; 
int ldrrt = A1; 
int ldrld = A2; 
int ldrrd = A3; 
int ldrmt = A5;

const int button1 = 7;
const int button2 = 8;
const int motorA = 9;
const int motorB = 10;
int buttonStateA = 0;
int buttonStateB = 0;

int pos = 0;
int pos2 = 0;
int oldvalue;
int oldvalue2;

void setup() {
  horizontal.attach(10);
  vertical.attach(9);
  horizontal.write(180);
  vertical.write(45);
  pinMode(motorA, OUTPUT);
  pinMode(motorB, OUTPUT);
  pinMode(button1, INPUT);
  pinMode(button1, INPUT);
  delay(2500);
}
void loop() {
  int ldrStatus = analogRead(ldrmt);
  if (ldrStatus > 30) {
    buttonStateA = digitalRead(button1);
    if (buttonStateA == LOW) {
      digitalWrite(motorA, HIGH); //ccw
      digitalWrite(motorB, LOW);
    } else {
      digitalWrite(motorA, LOW);
      digitalWrite(motorB, LOW);
    }

    int lt = analogRead(ldrlt); // top left
    int rt = analogRead(ldrrt); // top right
    int ld = analogRead(ldrld); // down left
    int rd = analogRead(ldrrd); // down right
    int dtime = 10;
    int tol = 90; // dtime=diffirence time, tol=toleransi
    int avt = (lt + rt) / 2; // average value top
    int avd = (ld + rd) / 2; // average value down
    int avl = (lt + ld) / 2; // average value left
    int avr = (rt + rd) / 2; // average value right
    int dvert = avt - avd; // check the difference of up and down
    int dhoriz = avl - avr; // check the difference of left and rigt

    if (-1 * tol > dvert || dvert > tol) {
      if (avt > avd) {
        servov = ++servov;
        if (servov > servovLimitHigh) {
          servov = servovLimitHigh;
        }
      } else if (avt < avd) {
        servov = --servov;
        if (servov < servovLimitLow) {
          servov = servovLimitLow;
        }
      }
      vertical.write(servov);
    }
    if (-1 * tol > dhoriz || dhoriz > tol) 
    {
      if (avl > avr) {
        servoh = --servoh;
        if (servoh < servohLimitLow) {
          servoh = servohLimitLow;
        }
      } else if (avl < avr) {
        servoh = ++servoh;
        if (servoh > servohLimitHigh) {
          servoh = servohLimitHigh;
        }
      } else if (avl = avr) {
        delay(10);
      }
      horizontal.write(servoh);
    }
    delay(dtime);

  } else {
    oldvalue = horizontal.read();
    oldvalue2 = vertical.read();

    for (pos = oldvalue; pos <= 180; pos += 1) { // goes from 0-180 degrees
      horizontal.write(pos);
      delay(15);
    }
    for (pos2 = oldvalue2; pos2 <= 0; pos2 += 1) { // goes from 0-180 degrees
      vertical.write(pos2); // tell servo to go to position in variable 'pos'
      delay(15);
    }
    buttonStateB = digitalRead(button2);
    if (buttonStateB == LOW) {
      digitalWrite(motorA, LOW); //clockwise
      digitalWrite(motorB, HIGH);
    } else {
      digitalWrite(motorA, LOW);
      digitalWrite(motorB, LOW);
    }
  }
}