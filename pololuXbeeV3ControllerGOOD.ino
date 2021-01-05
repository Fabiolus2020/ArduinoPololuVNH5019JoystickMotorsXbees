#include <EasyTransfer.h>

//create two objects
EasyTransfer ETout;
const int potpin1 = A0;
const int potpin2 = A1;


struct SEND_DATA_STRUCTURE {
  //put your variable definitions here for the data you want to receive
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  int valX;
  int valY;

};

SEND_DATA_STRUCTURE txdata;

void setup() {
  Serial.begin(9600);

  //start the library, pass in the data details and the name of the serial port. Can be Serial, Serial1, Serial2, etc.
  ETout.begin(details(txdata), &Serial);

}

void loop() {
  txdata.valY = analogRead(potpin1);
  txdata.valX = analogRead(potpin2);

  ETout.sendData();

}
