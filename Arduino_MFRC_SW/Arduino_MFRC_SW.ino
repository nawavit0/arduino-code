#include "MFRC522.h"
#include <SPI.h>

#define RST_PIN  5
#define SS_PIN_1  4
#define SS_PIN_2  0
#define SW_PIN  2
MFRC522 mfrc522_1(SS_PIN_1, RST_PIN);   // Create MFRC522_1 instance
MFRC522 mfrc522_2(SS_PIN_2, RST_PIN);   // Create MFRC522_2 instance

int SW_value = 1;
int SW_temp = 1;

void setup() {
  Serial.begin(9600);    // Initialize serial communications
  SPI.begin();           // Init SPI bus
  mfrc522_1.PCD_Init();    // Init MFRC522_1
  mfrc522_2.PCD_Init();    // Init MFRC522_2
  pinMode(SW_PIN, INPUT);
}

void loop() {
  SW_value = digitalRead(SW_PIN);
  if( (SW_value==0) && (SW_temp==1) ){
    Serial.println(F("Reading...."));
    mfrc522_1.PCD_Init();    // Init MFRC522_1
    mfrc522_2.PCD_Init();    // Init MFRC522_2
    check_reader(mfrc522_1, 1);
    check_reader(mfrc522_2, 2);
  }
  SW_temp = SW_value;
  delay(1000);
}

void check_reader(MFRC522 reader, int id) {
    // Look for cards
//    if ( ! reader.PICC_ReadCardSerial() ) {
//      delay(50);
//      return;
//    }
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
    return;
}

