/*Arduino Air Gesture Control Robot
 * Receiver Circuit
 * Created by DIY BUILDER
 * Contact me on Instagram https://www.instagram.com/diy.builder/
 * You need to include the (RF24) library before uploading this sketch 
 * Follow this procedure to include the library first go to Sketch >> Include Library >> Manage Libraries >> Type RF24 in the search bar >> Find the Rf24 >> Click install >> Done.
 * 
*/


#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

int ENA = 3;
int ENB = 9;
int MotorA1 = 4;
int MotorA2 = 5;
int MotorB1 = 6;
int MotorB2 = 7;


RF24 radio(8, 10);   // nRF24L01 (CE, CSN)
const byte address[6] = "00001";

struct Data_Package {
  byte xValue;
};
Data_Package data;


void setup() {
  // put your setup code here, to run once:

 Serial.begin(9600);
  
 radio.begin();
  radio.openReadingPipe(0, address);
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening(); //  Set the module as receiver

pinMode(ENA, OUTPUT);
pinMode(ENB, OUTPUT);
pinMode(MotorA1, OUTPUT);
pinMode(MotorA2, OUTPUT);
pinMode(MotorB1, OUTPUT);
pinMode(MotorB2, OUTPUT);


}

void loop() {
  
  // put your main code here, to run repeatedly:
if(radio.available()) {
  radio.read(&data, sizeof(Data_Package));
  Serial.print("j1PotX: ");
  Serial.println(data.xValue);
  if(data.xValue == 1) {
    analogWrite(ENA, 255);
    analogWrite(ENB, 255);
    digitalWrite(MotorA1, LOW);
    digitalWrite(MotorA2, HIGH);
    digitalWrite(MotorB1, HIGH);
    digitalWrite(MotorB2, LOW);
    
  }else if(data.xValue == 2) {
    analogWrite(ENA, 255);
    analogWrite(ENB, 255);
    digitalWrite(MotorA1, HIGH);
    digitalWrite(MotorA2, LOW);
    digitalWrite(MotorB1, LOW);
    digitalWrite(MotorB2, HIGH);
    
  }else if(data.xValue == 3) {
    analogWrite(ENA, 255);
    analogWrite(ENB, 255);
    digitalWrite(MotorA1, LOW);
    digitalWrite(MotorA2, HIGH);
    digitalWrite(MotorB1, LOW);
    digitalWrite(MotorB2, HIGH);
    
  }else if(data.xValue == 4) {
    analogWrite(ENA, 255);
    analogWrite(ENB, 255);
    digitalWrite(MotorA1, HIGH);
    digitalWrite(MotorA2, LOW);
    digitalWrite(MotorB1, HIGH);
    digitalWrite(MotorB2, LOW);
    
  }else if(data.xValue == 0) {
    analogWrite(ENA,0);
    analogWrite(ENB,0);
    digitalWrite(MotorA1, LOW);
    digitalWrite(MotorA2, LOW);
    digitalWrite(MotorB1, LOW);
    digitalWrite(MotorB2, LOW);
    
  }else if(data.xValue == 5) {
    analogWrite(ENA, 0);
    analogWrite(ENB, 0);
    digitalWrite(MotorA1, LOW);
    digitalWrite(MotorA2, LOW);
    digitalWrite(MotorB1, LOW);
    digitalWrite(MotorB2, LOW);
  }
 }
}
