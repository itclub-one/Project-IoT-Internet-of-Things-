#include "TimerOne.h"
#include <LiquidCrystal_I2C.h>      //https://www.arduino.cc/reference/en/libraries/liquidcrystal-i2c/
LiquidCrystal_I2C lcd(0x27, 16, 2);
 
volatile unsigned int mycounter = 0;
volatile unsigned int turns = 0;
float turnsperminute = 0;
unsigned int speed = 0;
 
void setup()
{
  pinMode(A5, INPUT);
  pinMode(8, OUTPUT);
  
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("   Welcome To  ");
  lcd.setCursor(0, 1);
  lcd.print("Taxi Fare Meter");
  delay(2000);
  lcd.clear();
  
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(timerIsr);
 
  attachInterrupt(digitalPinToInterrupt(2), count, RISING);
  attachInterrupt(digitalPinToInterrupt(3), finalfare, HIGH);
}
 
void count()
{
  mycounter++;
  turns++;
  delay(10);
}
 
void timerIsr()
{
  detachInterrupt(digitalPinToInterrupt(2));
  Timer1.detachInterrupt();
  lcd.clear();
 
  float speed = (mycounter / 20.0) * 60.0;
  float totalturns = 230 * (turns / 20);
  turnsperminute = totalturns / 100;
 
  lcd.setCursor(0, 0);
  lcd.print("Dist:");
  lcd.print(turnsperminute);
  lcd.print("m");
  lcd.setCursor(0, 1);
  lcd.print("Speed:");
  lcd.print(speed);
  lcd.print("rpm");
 
  mycounter = 0;
 
  int analoginput = analogRead(A5);
  int motorspeed = map(analoginput, 0, 1023, 0, 255);
  analogWrite(8, motorspeed);
 
  Timer1.attachInterrupt(timerIsr);
  attachInterrupt(digitalPinToInterrupt(2), count, RISING);
}
 
void finalfare()
{
  detachInterrupt(digitalPinToInterrupt(2));
  Timer1.detachInterrupt();
  float price = turnsperminute * 0.5;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Fare: ");
  lcd.print(price);
  lcd.print("$");
  lcd.setCursor(0, 1);
  lcd.print("0.5$ Per Meter");
}
 
void loop()
{
}
