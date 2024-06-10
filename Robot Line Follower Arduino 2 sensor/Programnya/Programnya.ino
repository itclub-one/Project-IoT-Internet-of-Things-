#include <AFMotor.h>
const int pinSensorKiri = A0;
const int pinSensorKanan = A1;

char val;
AF_DCMotor motor1(3, MOTOR12_64KHZ); //Jadikan motor kanan, 64KHZ
AF_DCMotor motor2(4, MOTOR12_64KHZ); //Jadikan motor kiri, 642hHZ

void setup() {
  // put your setup code here, to run once:
Serial.begin (9600);
pinMode (pinSensorKiri, INPUT);
pinMode (pinSensorKanan, INPUT);
motor1.setSpeed(120); //Set kecepatan motor 1 240 (range 0-255)
motor2.setSpeed(120); //Set kecepatan motor 2 240 (range 0-255)
}

void loop() {
  // put your main code here, to run repeatedly:
int dataAnalog1 = digitalRead (pinSensorKiri);
int dataAnalog2 = digitalRead (pinSensorKanan);
Serial.print ("Sensor : ");
Serial.print (dataAnalog1);
Serial.print (", Sensor : ");
Serial.print (dataAnalog2);

if (dataAnalog1 == 0 && dataAnalog2 == 0) {
  motor1.run(FORWARD); //Motor kanan maju
  motor2.run(FORWARD); //Motor kiri maju
}
else if(dataAnalog1 == 0 && dataAnalog2 == 1) {
  motor1.run(BACKWARD); //Motor kanan mundur
  motor2.run(FORWARD); //Motor kiri maju
}
else if(dataAnalog1 == 1 && dataAnalog2 == 0){
  motor1.run(FORWARD); //Motor kanan maju
  motor2.run(BACKWARD); //Motor kiri mundur
}
else {
  motor1.run(RELEASE); //Motor kanan berhenti
  motor2.run(RELEASE); //Motor kiri berhenti
}
}
