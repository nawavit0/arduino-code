#include "MFRC522.h"
#include <SPI.h>

#define RST_PIN  5
#define SS_PIN  4
#define SW_PIN  2
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522_1 instance

int SW_value = 1;
int SW_temp = 1;

void setup() {
  Serial.begin(9600);    // Initialize serial communications
  SPI.begin();           // Init SPI bus
  mfrc522.PCD_Init();    // Init MFRC522_1
  pinMode(SW_PIN, INPUT);
}

void loop() {
  SW_value = digitalRead(SW_PIN);
  if( (SW_value==0) && (SW_temp==1) ){
    Serial.println(F("Reading...."));
    check_reader(mfrc522, 1);
  }
  SW_temp = SW_value;
  delay(200);
}

void check_reader(MFRC522 reader, int id) {
    // Look for cards
    Serial.print(F("Card detected in reader: "));
    Serial.println(id);
//    if ( ! reader.PICC_ReadCardSerial() ) {
//      Serial.println(F("Card UID hex: No detected"));
//      return;
//    }
    
    // A card has been detected  
    unsigned int hex_num;      
    hex_num =  reader.uid.uidByte[0] << 24;
    hex_num += reader.uid.uidByte[1] << 16;
    hex_num += reader.uid.uidByte[2] <<  8;
    hex_num += reader.uid.uidByte[3];
    Serial.print(F("Card UID hex:"));
    Serial.println(hex_num);
}
