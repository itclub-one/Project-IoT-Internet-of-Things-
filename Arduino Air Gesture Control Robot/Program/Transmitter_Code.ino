/*
 * Arduino Air Gesture Control Robot
 * Transmitter Circuit
 * 
 * I recreated this sktech from file (simpleGesture.ino) which is created by DF_Robot
 * @ https://github.com/DFRobot/DFRobot_Gesture_Touch (Library)
 * Contact me on Instagram https://www.instagram.com/diy.builder/
 * You need to include the (RF24) and (DFRobot_Gesture_Touch) library before uploading this sketch 
 * Follow this procedure to include the library first go to Sketch >> Include Library >> Manage Libraries >> Type RF24 in the search bar >> Find the Rf24 >> Click install >> Done.
 * 
 * Copyright   [DFRobot](http://www.dfrobot.com), 2016
 * Copyright   GNU Lesser General Public License
 *
 * version  V1.0
 * date  2020-2-21
*/



#include<SPI.h>
#include<nRF24L01.h>
#include<RF24.h>
#include<Wire.h>
#include "DFRobot_Gesture_Touch.h"
#ifdef __AVR__
#include "SoftwareSerial.h"
SoftwareSerial mySerial(0,1);
#endif

DFRobot_Gesture_Touch DFGT(&mySerial);

RF24 radio(8,10);
const byte address[6] = "00001";

struct Data_Package {
  byte xValue;
};

Data_Package data;

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
mySerial.begin(9600);
delay(500);
while(mySerial.available())
mySerial.read();
Serial.println("Gesture&Touch sensor Test");
DFGT.setGestureDistance(20);
DFGT.enableFunction(DFGT_FUN_ALL);

radio.begin();
  radio.openWritingPipe(address);
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_LOW);
  radio.stopListening();
  
data.xValue = 0;

}

void loop() {
  // put your main code here, to run repeatedly:
int8_t rslt = DFGT.getAnEvent();
if(rslt!=DF_ERR) {
delay(5);
data.xValue = rslt;

}
radio.write(&data, sizeof(Data_Package));
}
