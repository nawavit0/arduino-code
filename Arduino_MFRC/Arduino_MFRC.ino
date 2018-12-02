#include "MFRC522.h"
#include <SPI.h>

#define RST_PIN  5
#define SS_PIN_1  4
#define SS_PIN_2  0
MFRC522 mfrc522_1(SS_PIN_1, RST_PIN);   // Create MFRC522_1 instance
MFRC522 mfrc522_2(SS_PIN_2, RST_PIN);   // Create MFRC522_2 instance

void setup() {
  Serial.begin(9600);    // Initialize serial communications
  SPI.begin();           // Init SPI bus
  mfrc522_1.PCD_Init();    // Init MFRC522_1
//  mfrc522_2.PCD_Init();    // Init MFRC522_2
}

void loop() {
  delay(1000);
  check_reader(mfrc522_1, 1);
//  check_reader(mfrc522_2, 2);
}

void check_reader(MFRC522 reader, int id) {
    // Look for cards
    if ( ! reader.PICC_ReadCardSerial() ) {
      delay(50);
      return;
    }  
    if ( ! reader.PICC_IsNewCardPresent()) 
    {
      return;
    }
    // Select one of the cards

    Serial.print(F("Card detected in reader: "));
    Serial.println(id);
    // A card has been detected  
    unsigned int hex_num;      
    hex_num =  reader.uid.uidByte[0] << 24;
    hex_num += reader.uid.uidByte[1] << 16;
    hex_num += reader.uid.uidByte[2] <<  8;
    hex_num += reader.uid.uidByte[3];
    Serial.print(F("Card UID hex:"));
    Serial.println(hex_num);
}

