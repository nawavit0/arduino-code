#include <SPI.h>
#include <MFRC522.h>

constexpr uint8_t RST_PIN = 5;     // Configurable, see typical pin layout above
constexpr uint8_t SS_1_PIN = 8;   // Configurable, take a unused pin, only HIGH/LOW required, must be diffrent to SS 2
constexpr uint8_t SS_2_PIN = 9;    // Configurable, take a unused pin, only HIGH/LOW required, must be diffrent to SS 1

constexpr uint8_t NR_OF_READERS = 2;

byte ssPins[] = {SS_1_PIN, SS_2_PIN};

MFRC522 mfrc522[NR_OF_READERS];   // Create MFRC522 instance.

void setup() {
  Serial.begin(9600); // Initialize serial communications with the PCv
  SPI.begin();        // Init SPI bus

  for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
    mfrc522[reader].PCD_Init(ssPins[reader], RST_PIN); // Init each MFRC522 card
    Serial.print(F("Reader "));
    Serial.print(reader+1);
    Serial.print(F(": "));
    mfrc522[reader].PCD_DumpVersionToSerial();
  }

}

void loop() {
  if (Serial.available()){
    char ch = Serial.read();
    Serial.println(ch);
    if (ch=='b'){
      for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
        Serial.print(F("Reader "));
        Serial.println(reader+1);
        if ( ! mfrc522[reader].PICC_IsNewCardPresent()) {
          Serial.println("YYYYYYYY");
          //continue;
        }
        if ( ! mfrc522[reader].PICC_ReadCardSerial()) {
          Serial.println("XXXXXXXX");
          //continue;
        }
        dump_byte_array(mfrc522[reader].uid.uidByte, mfrc522[reader].uid.size);
        Serial.println();
        //mfrc522[reader].PICC_HaltA();
        //mfrc522[reader].PCD_StopCrypto1();
      }
      delay(500);
    }
  }
}

void dump_byte_array(byte *buffer, byte bufferSize) {
  
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? "0" : "");
    Serial.print(buffer[i], HEX);
  }
  
}
