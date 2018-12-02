/*
 * --------------------------------------------------------------------------------------------------------------------
 * Example sketch/program showing how to read data from a PICC to serial.
 * --------------------------------------------------------------------------------------------------------------------
 * This is a MFRC522 library example; for further details and other examples see: https://github.com/miguelbalboa/rfid
 * 
 * Example sketch/program showing how to read data from a PICC (that is: a RFID Tag or Card) using a MFRC522 based RFID
 * Reader on the Arduino SPI interface.
 * 
 * When the Arduino and the MFRC522 module are connected (see the pin layout below), load this sketch into Arduino IDE
 * then verify/compile and upload it. To see the output: use Tools, Serial Monitor of the IDE (hit Ctrl+Shft+M). When
 * you present a PICC (that is: a RFID Tag or Card) at reading distance of the MFRC522 Reader/PCD, the serial output
 * will show the ID/UID, type and any data blocks it can read. Note: you may see "Timeout in communication" messages
 * when removing the PICC from reading distance too early.
 * 
 * If your reader supports it, this sketch/program will read all the PICCs presented (that is: multiple tag reading).
 * So if you stack two or more PICCs on top of each other and present them to the reader, it will first output all
 * details of the first and then the next PICC. Note that this may take some time as all data blocks are dumped, so
 * keep the PICCs at reading distance until complete.
 * 
 * @license Released into the public domain.
 * 
 * Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 */

/**
 *  Signal:   RST     MOSI      MISO      SCK       SDA(1)    SDA(2)    GND     3.3V
 *  PIN:      5       51        50        52        8         9         GND     3.3V
 *  Color:    Purple  Green     Orange    Yellow    Blue      Blue      Black   Red
 */

#include <SPI.h>
#include <MFRC522.h>

constexpr uint8_t RST_1_PIN = 8;
constexpr uint8_t RST_2_PIN = 9;         // Configurable, see typical pin layout above
constexpr uint8_t RST_3_PIN = 10;
constexpr uint8_t RST_4_PIN = 11;
constexpr uint8_t RST_5_PIN = 12;
constexpr uint8_t RST_6_PIN = 13;  
  
constexpr uint8_t SS_1_PIN = 32;         // Configurable, see typical pin layout above
constexpr uint8_t SS_2_PIN = 34; 
constexpr uint8_t SS_3_PIN = 36; 
constexpr uint8_t SS_4_PIN = 38; 
constexpr uint8_t SS_5_PIN = 40; 
constexpr uint8_t SS_6_PIN = 42;  

constexpr uint8_t NR_OF_READERS = 6;

int count = 0;

byte ssPins[] = {SS_1_PIN, SS_2_PIN, SS_3_PIN, SS_4_PIN, SS_5_PIN, SS_6_PIN};
byte rstPins[] = {RST_1_PIN, RST_2_PIN, RST_3_PIN, RST_4_PIN, RST_5_PIN, RST_6_PIN};

MFRC522 mfrc522[NR_OF_READERS];
//MFRC522 mfrc522_1(SS_1_PIN, RST_1_PIN);  // Create MFRC522 instance
//MFRC522 mfrc522_2(SS_2_PIN, RST_2_PIN);

void(* resetFunc) (void) = 0;

void setup() {
  Serial.begin(9600);   // Initialize serial communications with the PC
  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();      // Init SPI bus
  for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
    mfrc522[reader].PCD_Init(ssPins[reader], rstPins[reader]); // Init each MFRC522 card
  }
//  Serial.println("Start");
  //mfrc522_1.PCD_Init();   // Init MFRC522
  //mfrc522_2.PCD_Init();
  //mfrc522_1.PCD_DumpVersionToSerial();  // Show details of PCD - MFRC522 Card Reader details
  //Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
}

void loop() {
      String Ordered_set = "";
      String content= "";
      for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
        if (reader>0){
          Ordered_set.concat(",");
        }
        bool canRead = true;
        // Look for new cards
        if ( ! mfrc522[reader].PICC_IsNewCardPresent()) {
          canRead = false;
        }
      
        // Select one of the cards
        if ( ! mfrc522[reader].PICC_ReadCardSerial()) {
          canRead = false;
        }

        if ( canRead == false ) {
          if ( ! mfrc522[reader].PICC_IsNewCardPresent()) {
            Ordered_set.concat("XXXXXXXX");
            continue;
          }
          if ( ! mfrc522[reader].PICC_ReadCardSerial()) {
            Ordered_set.concat("XXXXXXXX");
            continue;
          }
        }
      
        // Dump debug info about the card; PICC_HaltA() is automatically called
        //mfrc522_1.PICC_DumpToSerial(&(mfrc522_1.uid));
      
        //Show UID on serial monitor
//        Serial.println();
//        Serial.print(" Reader ");
//        Serial.print(reader);
//        Serial.print(" UID tag :");
        content= "";
        for (byte i = 0; i < mfrc522[reader].uid.size; i++) 
        {
//           Serial.print(mfrc522[reader].uid.uidByte[i] < 0x10 ? "0" : "");
//           Serial.print(mfrc522[reader].uid.uidByte[i], HEX);
           content.concat(String(mfrc522[reader].uid.uidByte[i] < 0x10 ? "0" : ""));
           content.concat(String(mfrc522[reader].uid.uidByte[i], HEX));
        }
        content.toUpperCase();
        Ordered_set.concat(content);
        //Serial.println();
      }
      Serial.println(Ordered_set);
      delay(100);
      count = count + 1;
      if(count=1){
        Serial.end();
        resetFunc();
      }
}
