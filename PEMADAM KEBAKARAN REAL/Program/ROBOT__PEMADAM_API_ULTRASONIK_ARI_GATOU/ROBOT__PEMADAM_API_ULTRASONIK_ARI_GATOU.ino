#include <NewPing.h>
#define Mright_Dir 12
#define Mright_Vel 10
#define Mleft_Dir 13
#define Mleft_Vel 11
#define fullspeed 255//seting maximal speed motor255
#define nospeed 0
#define FLAME_SENSOR 2 // FLAME_SENSOR to digital pin2
#define FAN 5//fan in pin digital pin 3
#define BUZZER 4//standart driver 

int middle, left, right;
#define MIDDLE 8 //echo and trig in digital pin8
#define LEFT 9//echo and trig in  digital pin7
#define RIGHT 7 //echo and trig in digital pin9
#define MAX 100
NewPing sonar(MIDDLE, MIDDLE, MAX);
NewPing sonar1(RIGHT, RIGHT, MAX);
NewPing sonar2(LEFT, LEFT, MAX);
void forward(){
digitalWrite(Mright_Dir,HIGH);
analogWrite(Mright_Vel,100);
digitalWrite(Mleft_Dir,HIGH);
analogWrite(Mleft_Vel,100);

}

void back(){
digitalWrite(Mright_Dir,LOW);
analogWrite(Mright_Vel,100);
digitalWrite(Mleft_Dir,LOW);
analogWrite(Mleft_Vel,100);

}

void stop(){
digitalWrite(Mright_Dir,LOW);
analogWrite(Mright_Vel,nospeed);
digitalWrite(Mleft_Dir,LOW);
analogWrite(Mleft_Vel,nospeed);
}

void turright(){
digitalWrite(Mright_Dir,LOW);
analogWrite(Mright_Vel,100);
digitalWrite(Mleft_Dir,HIGH);
analogWrite(Mleft_Vel,120);
delay(100);

}

void turleft(){
digitalWrite(Mright_Dir,HIGH);
analogWrite(Mright_Vel,120);
digitalWrite(Mleft_Dir,LOW);
analogWrite(Mleft_Vel,100); 
delay(100);

}

boolean isFlameDetected()

{
if(digitalRead(FLAME_SENSOR))
return false;
else return true;
}

void Beep() {
delay(100);
digitalWrite(BUZZER,HIGH);
}

void setup(){
pinMode(12,OUTPUT);
pinMode(10,OUTPUT);
pinMode(13,OUTPUT);
pinMode(11,OUTPUT);
Serial.begin(9600);

 

pinMode(FLAME_SENSOR, INPUT);
pinMode(FAN,OUTPUT);
pinMode(BUZZER,OUTPUT);
digitalWrite(FAN,HIGH);
digitalWrite(BUZZER,LOW);

}

void loop(){
delay(200);
Beep();
middle = sonar.ping_cm();
right = sonar1.ping_cm();
left = sonar2.ping_cm();
if(middle==0){
middle=MAX;
}
if(right==0){
right=MAX;
}
if(left==0){
left=MAX;
}
Serial.print(" value");
Serial.print(middle);
Serial.print(" cm ");
Serial.print(right);
Serial.print(" cm ");
Serial.print(left);
Serial.print(" cm ");

if(isFlameDetected()){
stop();
digitalWrite(FAN,LOW);
digitalWrite(BUZZER,HIGH);
delay(3500);
Serial.print("FIRE");
Serial.println("");
}else{
digitalWrite(FAN,HIGH);
digitalWrite(BUZZER,LOW);
Serial.print("CM");
Serial.println("");
if(left<=20 && middle<=20 && right<=20){
back();
}
else if((middle<=20) && (left<=20)){
turright();
}
else if((middle<=20) && (right<=20)){
turleft();
}
else if(left<=20){
turright();
}
else if(right<=20){
turleft();
}
else if(middle<=20){
back();
turright();
}
else{
forward();
}
}
}
