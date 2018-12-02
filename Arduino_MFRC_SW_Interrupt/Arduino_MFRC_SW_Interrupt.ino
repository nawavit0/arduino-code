#include "MFRC522.h"
#include <SPI.h>

#define RST_PIN  15
#define SS_PIN  4
#define SW_PIN  2
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522_1 instance

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);    // Initialize serial communications
  SPI.begin();           // Init SPI bus
  mfrc522.PCD_Init();    // Init MFRC522_1
  attachInterrupt(digitalPinToInterrupt(SW_PIN), check_reader, RISING);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void check_reader(){
  read_MFRC(mfrc522,1);
}

void read_MFRC(MFRC522 reader, int id) {
    // Look for cards
    Serial.print(F("Card detected in reader: "));
    Serial.println(id);
 
    unsigned int hex_num;      
    hex_num =  reader.uid.uidByte[0] << 24;
    hex_num += reader.uid.uidByte[1] << 16;
    hex_num += reader.uid.uidByte[2] <<  8;
    hex_num += reader.uid.uidByte[3];
    Serial.print(F("Card UID hex:"));
    Serial.println(hex_num);
    return;
}
