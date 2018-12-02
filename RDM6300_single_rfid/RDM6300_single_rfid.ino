//#include <SoftwareSerial.h>
//#include <RDM6300.h>
//
//SoftwareSerial rdmSerial_1(9, 8); //RX, TX
////SoftwareSerial rdmSerial_2(5, 4); //RX, TX
//
//uint8_t Payload[6]; // used for read comparisons
//
//RDM6300 RDM6300(Payload);
//
//void setup() {
//  // put your setup code here, to run once:
//  Serial.begin(9600);
//  //rdmSerial_1.begin(9600);
//  pinMode(9,INPUT);
//  pinMode(8,OUTPUT);
//}
//
//void loop() {
//  // put your main code here, to run repeatedly:
//  if (Serial.available()){
//    char ch = Serial.read();
//    Serial.println(ch);
//    if (ch=='b'){
//      Serial.println("Try to read rdmSerial_1");
//      rdmSerial_1.begin(9600);
//      if (rdmSerial_1.available()) {
//        Serial.println("rdmSerial_1 connected");
//        uint8_t c = rdmSerial_1.read();
//        decodeTag(c);
//      }
//      rdmSerial_1.end();
//    }
//  }
//}
//
//void decodeTag(uint8_t c) {
//  if (RDM6300.decode(c)) {
//    for (int i=0; i < 5; i++){
//      Serial.print(Payload[i], HEX);
//      Serial.print(" ");
//    } 
//    Serial.println();
//  }  
//}


#include <SoftwareSerial.h>
SoftwareSerial RFID(9 , 8); // RX=2 and TX=3

int i;

void setup()
{
  Serial.begin(9600);  // start serial to PC 
}

void loop()
{
  if (Serial.available()){
    char ch = Serial.read();
    Serial.println(ch);
    if (ch=='b'){
      Serial.println("Try to read rdmSerial_1");
      RFID.begin(9600);
      if (RFID.available() > 0) {
        Serial.println("connected");
        i = RFID.read();
        Serial.print(i, DEC);
        Serial.print(" - ");
      }
      RFID.end();
    }
  }

}
