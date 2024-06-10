//Arduino Table edge Avoidance Robot
//Created By DIY BUILDER
//Contact me here https://www.instagram.com/diy.builder/
//You need to include AF Motor.h library before uploading the sketch, otherwise you'll get compilation error message.

#include <AFMotor.h>

#define IR1 A0
#define IR2 A1


AF_DCMotor motor1(1, MOTOR12_1KHZ); 
AF_DCMotor motor2(2, MOTOR12_1KHZ); 
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);


char command; 

void setup() 
{       
  Serial.begin(9600);  //Set the baud rate to your Bluetooth module.
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
    
}

void loop(){
  
  /*Serial.print("Right");
    Serial.println(Right);
    Serial.print("Left");
    Serial.println(Left);*/
    
  if(Serial.available() > 0){ 
    command = Serial.read(); 
    Stop(); 
    
    Serial.println(command);
    
    
    switch(command){
    case 'F':  
      forward();
      break;
    case 'B':  
       back();
      break;
    case 'L':  
      left();
      break;
    case 'R':
      right();
      break;
    }
    
    
   
    int Right = digitalRead(IR1);
    int Left = digitalRead(IR2);
    
    if(Right == 1 || Left == 1) {
      motor1.setSpeed(255);
      motor1.run(BACKWARD);
      motor2.setSpeed(255);
      motor2.run(BACKWARD);
      motor3.setSpeed(255);
      motor3.run(BACKWARD);
      motor4.setSpeed(255);
      motor4.run(BACKWARD);
      
    }else if(Right == 0 || Left == 0) {
      command = Serial.read();
    }
 }
}

void forward()
{
  motor1.setSpeed(150); //Define maximum Speed
  motor1.run(FORWARD); //rotate the motor clockwise
  motor2.setSpeed(150); //Define maximum Speed
  motor2.run(FORWARD); //rotate the motor clockwise
  motor3.setSpeed(150);//Define maximum Speed
  motor3.run(FORWARD); //rotate the motor clockwise
  motor4.setSpeed(150);//Define maximum Speed
  motor4.run(FORWARD); //rotate the motor clockwise
}

void back()
{
  motor1.setSpeed(150); //Define maximum Speed
  motor1.run(BACKWARD); //rotate the motor anti-clockwise
  motor2.setSpeed(150); //Define maximum Speed
  motor2.run(BACKWARD); //rotate the motor anti-clockwise
  motor3.setSpeed(150); //Define maximum Speed
  motor3.run(BACKWARD); //rotate the motor anti-clockwise
  motor4.setSpeed(150); //Define maximum Speed
  motor4.run(BACKWARD); //rotate the motor anti-clockwise
}

void left()
{
  motor1.setSpeed(200); //Define maximum Speed
  motor1.run(BACKWARD); //rotate the motor anti-clockwise
  motor2.setSpeed(200); //Define maximum Speed
  motor2.run(BACKWARD); //rotate the motor anti-clockwise
  motor3.setSpeed(200); //Define maximum Speed
  motor3.run(FORWARD);  //rotate the motor clockwise
  motor4.setSpeed(200); //Define maximum Speed
  motor4.run(FORWARD);  //rotate the motor clockwise
}

void right()
{
  motor1.setSpeed(200); //Define maximum Speed
  motor1.run(FORWARD); //rotate the motor clockwise
  motor2.setSpeed(200); //Define maximum Speed
  motor2.run(FORWARD); //rotate the motor clockwise
  motor3.setSpeed(200); //Define maximum Speed
  motor3.run(BACKWARD); //rotate the motor anti-clockwise
  motor4.setSpeed(200); //Define maximum Speed
  motor4.run(BACKWARD); //rotate the motor anti-clockwise
} 

void Stop()
{
  motor1.setSpeed(0); //Define minimum Speed
  motor1.run(RELEASE); //stop the motor when release the button
  motor2.setSpeed(0); //Define minimum Speed
  motor2.run(RELEASE); //rotate the motor clockwise
  motor3.setSpeed(0); //Define minimum Speed
  motor3.run(RELEASE); //stop the motor when release the button
  motor4.setSpeed(0); //Define minimum Speed
  motor4.run(RELEASE); //stop the motor when release the button
}
