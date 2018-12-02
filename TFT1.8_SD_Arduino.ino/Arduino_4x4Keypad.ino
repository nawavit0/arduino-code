#include <SoftwareSerial.h>
#include <Keypad.h>

char keys[4][4] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPin[4] = {6, 7, 8, 9};
byte colPin[4] = {10, 11, 12, 13};

SoftwareSerial node1Serial(3, 2); //RX, TX
SoftwareSerial node2Serial(5, 4); //RX, TX
Keypad keypad = Keypad(makeKeymap(keys), rowPin, colPin, 4, 4);

void setup() {
  Serial.begin(115200);
  pinMode(13, OUTPUT);
  pinMode(3, INPUT);
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, INPUT);
  Serial.println("Arduino is available");
}

boolean flag = false;
boolean pressable = false;
char pw[4] = "1231";
char pres[4];
float val = 0;
int count = -1;

void loop() {
  if (flag == false) {
    //Receive data from NodeMCU#1
    Serial.println("wait data from node1");
    node1Serial.begin(4800);
    //receive from node1
    while (node1Serial.available() > 0) {
      Serial.println("node1 connected");
      float val1 = node1Serial.parseFloat();
      if (node1Serial.read() == '\n' && val1 == 1) {
        val = val1;
        Serial.println(val1);
        flag = true;
      }
    }
  }
  delay(1000);
  if (flag == true && pressable == false && count == -1) {
    node1Serial.end(); //End Serial communication with NodeMCU#1
    Serial.println("node1 end");
    node2Serial.begin(4800); //Start Serial communication with NodeMCu#2
    Serial.println("node2 connected");
    node2Serial.print(val); //Send data to NodeMCU#2 to open Servo motor
    node2Serial.print("\n");
    pressable = true;
    Serial.println("Enter password");
  }
  //4x4 switch button
  if (pressable == true) {
    int i = 0;
    while (i < 4) {
      char pressed = keypad.getKey();
      if (pressed) {
        Serial.println(pressed);
        pres[i] = pressed;
        i++;
      }
    }
    count = 0;
    for (int i = 0; i < 4; i++) {
      if (pres[i] != pw[i]) {
        Serial.println("Wrong password, again!");
        node2Serial.begin(4800);
        node2Serial.print(1.2);
        node2Serial.print("\n");
        break;
      }
      else {
        count++;
      }
    }
    if (count == 4) {
      Serial.println("correct password");
      pressable = false;
      node2Serial.begin(4800);
      node2Serial.print(2); //Send data to NodeMCU#2 to open Step motor
      node2Serial.print("\n");    
    }
  }
}
