#define RX  1
#define TX  3

#include "SoftwareSerial.h"

SoftwareSerial myESP(RX,TX);

void setup() { 
  Serial.begin(9600);
  myESP.begin(9600);
}

void loop() {
  if (Serial.available()) {
    myESP.write("Tª4100500000MC9--");
    while(myESP.available() > 0) {
      Serial.println(myESP.read());
    }
  }
  
}
