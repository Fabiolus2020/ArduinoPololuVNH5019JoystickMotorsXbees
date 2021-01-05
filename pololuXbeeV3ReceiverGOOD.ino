
#include <DualVNH5019MotorShield.h>
#include <EasyTransfer.h>
DualVNH5019MotorShield md;

void stopIfFault()
{
  if (md.getM1Fault())
  {
    Serial.println("M1 fault");
    while (1);
  }
  if (md.getM2Fault())
  {
    Serial.println("M2 fault");
    while (1);
  }
}

EasyTransfer ETin;

struct RECEIVE_DATA_STRUCTURE {
  //put your variable definitions here for the data you want to receive
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  int valX;
  int valY;

};

RECEIVE_DATA_STRUCTURE rxdata;

void setup() {
  Serial.begin(9600);

  md.init(); //initiates default pololu shield pins
  ETin.begin(details(rxdata), &Serial);

}

void loop() {

  for (int i = 0; i < 5; i++) {
    if (ETin.receiveData()) {

      rxdata.valY = map(rxdata.valY, 0, 1023, -250, 250);
      rxdata.valX = map(rxdata.valX, 0, 1023, -250, 250);

      if (rxdata.valX >= 10)
      {
        md.setM1Speed(rxdata.valX);
        md.setM2Speed(rxdata.valX);
        stopIfFault();
      }

      else if  (rxdata.valX <= -10)
      {
        md.setM1Speed(rxdata.valX);
        md.setM2Speed(rxdata.valX);
        stopIfFault();
      }

      else if  (rxdata.valY <= -10)
      {
        md.setM1Speed(rxdata.valY);
        md.setM2Speed(-rxdata.valY);
        stopIfFault();
      }


      else if  (rxdata.valY >= 10)
      {
        md.setM1Speed(-rxdata.valY);
        md.setM2Speed(rxdata.valY);
        stopIfFault();
      }

      else {
        md.setM1Speed(0);
        md.setM2Speed(0);
      }
    }
    delay(10);
  }
}
