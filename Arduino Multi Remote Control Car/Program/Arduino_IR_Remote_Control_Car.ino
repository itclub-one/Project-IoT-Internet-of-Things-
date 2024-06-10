/*  Arduino IR Remote Control Car
 *  Creted By DIY Builder
 *  Date 06-07-2021
 *  version 1.0
 */
 
/*  This file is part of Arduino-IRremote https://github.com/Arduino-IRremote/Arduino-IRremote.
 *  Copyright (C) 2020-2021  Armin Joachimsmeyer
 *  armin.joachimsmeyer@gmail.com
 *  MIT License
 */


#include<Arduino.h>
#include<IRremote.h>
#define IR_RECEIVE_PIN 11

#define ENA 5
#define IN1 6
#define IN2 7
#define IN3 8
#define IN4 9
#define ENB 10

int motorSpeedA = 0;
int motorSpeedB = 0;

void setup () {
  
  Serial.begin (115200);
  Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK, USE_DEFAULT_FEEDBACK_LED_PIN);
  Serial.print(F("Ready to receive IR signals at pin "));
  Serial.println(IR_RECEIVE_PIN);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  
}


void loop() {
  if (IrReceiver.decode()) {
    IrReceiver.printIRResultShort(&Serial);
    if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
      IrReceiver.printIRResultRawFormatted(&Serial, true);
    }

    switch(IrReceiver.decodedIRData.command) {
      //Default Remote
      case 0x18 : //Paste your command Value here
      Serial.println ("Move Forward");
      Forward();
      break;
      case 0x52:
      Serial.println("Move Backward");
      Backward();
      break;
      case 0x8:
      Serial.println("Turn Left");
      Left();
      break;
      case 0x5A:
      Serial.println("Turn Right");
      Right();
      break;
      case 0x1C:
      Serial.println("Stop");
      Stop();
      break;
      case 0x45:
      Serial.println("normal Speed");
      normalSpeed();
      break;
      case 0x46:
      Serial.println("medium Speed");
      mediumSpeed();
      break;
      case 0x47:
      Serial.println("full Speed");
      fullSpeed();
      break;
      
      //TV Remote
      case 0x16:
      Serial.println("Move Forward");
      Forward();
      break;
      case 0x24:
      Serial.println("Move Backward");
      Backward();
      break;
      case 0x21:
      Serial.println("Turn Left");
      Left();
      break;
      case 0x23:
      Serial.println("Turn Right");
      Right();
      break;
      case 0x25:
      Serial.println("Stop");
      Stop();
      break;
      case 0x10:
      Serial.println("normal Speed");
      normalSpeed();
      break;
      case 0x20:
      Serial.println("medium Speed");
      mediumSpeed();
      break;
      case 0x30:
      Serial.println("full Speed");
      fullSpeed();
      break;
      
    }
    
  Serial.println();
  IrReceiver.resume();
  }
}

void Forward() {
  analogWrite(ENA, motorSpeedA);
  analogWrite(ENB, motorSpeedB);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void Backward() {
  analogWrite(ENA, motorSpeedA);
  analogWrite(ENB, motorSpeedB);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void Left() {
  analogWrite(ENA, motorSpeedA);
  analogWrite(ENB, motorSpeedB);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void Right() {
  analogWrite(ENA, motorSpeedA);
  analogWrite(ENB, motorSpeedB);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void Stop() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void normalSpeed() {
  motorSpeedA = 120;
  motorSpeedB = 120;
}

void mediumSpeed() {
  motorSpeedA = 175;
  motorSpeedB = 175;
}

void fullSpeed() {
  motorSpeedA = 255;
  motorSpeedB = 255;
}
