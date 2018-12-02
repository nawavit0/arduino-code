#include <MFRC522.h>
#include <SPI.h>

#define RST_PIN 5 // RST-PIN for RC522 - RFID - SPI - Modul GPIO15 
#define SS_PIN1 5  // SDA-PIN for RC522 - RFID - SPI - Modul GPIO5
#define SS_PIN2 4  // SDA-PIN for RC522 - RFID - SPI - Modul GPIO4
#define SW_PIN 0
MFRC522 mfrc522_1(SS_PIN1, RST_PIN); 
MFRC522 mfrc522_2(SS_PIN2, RST_PIN); 

int SW_value = 0;
int SW_temp = 1;

int reader_size = 2;
unsigned int cardID[2] = {0, 0};
unsigned int ans[2] = {2529140569, 4188446809};

void setup() {
  delay(3000);
  Serial.begin(115200);    // Initialize serial communications
  SPI.begin();           // Init SPI bus
  mfrc522_1.PCD_Init();    // Init MFRC522_1
  mfrc522_2.PCD_Init();    // Init MFRC522_2
  pinMode(SW_PIN, INPUT);
}

void loop() {  
  SW_value = digitalRead(SW_PIN);
  Serial.println(SW_value);
  if( (SW_value==0) && (SW_temp==1) ){
    check_reader(mfrc522_1, 1);
    check_reader(mfrc522_2, 2);
    bool isTrue = true;
    for(int i=0;i<reader_size;i++){
      if(cardID[i]!=ans[i]){
        isTrue = false;
      }
    }
    if(isTrue==true){
      Serial.println("Answer is True.");
    }
    else{
      Serial.println("Answer is False.");
    }
  }
  SW_temp = SW_value;
}

void check_reader(MFRC522 reader, int id) {
    // Look for cards
    if ( ! reader.PICC_IsNewCardPresent() || ! reader.PICC_ReadCardSerial() ) {
      cardID[id-1] = 0;
      delay(50);
    }
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
    cardID[id-1] = hex_num;
}

