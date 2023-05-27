/**********************************************************************************
    TITLE: Blynk 2.0 + Manual Button (Momentary) control 4 Relays using NodeMCU (Real time feedback)(No Wi-Fi control)
    Preferences--> Aditional boards Manager URLs :
    https://dl.espressif.com/dl/package_esp32_index.json, http://arduino.esp8266.com/stable/package_esp8266com_index.json

    Download Board ESP8266 NodeMCU : https://github.com/esp8266/Arduino
    Download the libraries
    Blynk 1.0.1 Library:  https://github.com/blynkkk/blynk-library
 **********************************************************************************/

// Fill-in information from your Blynk Template here
#define BLYNK_TEMPLATE_ID "TMPLtWekP7SN"
#define BLYNK_DEVICE_NAME "Home Automation NodeMCU"
#define BLYNK_AUTH_TOKEN "iXSn7TrlYGbdagtzNU6YV1ANJqhsUaMR"
#define BLYNK_FIRMWARE_VERSION "0.1.0"

#define BLYNK_PRINT Serial
#define BLYNK_DEBUG

#define APP_DEBUG
// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD


// define the GPIO connected with Relays and switches
#define RelayPin1 5   //D1
#define RelayPin2 4   //D2
#define RelayPin3 14  //D5
#define RelayPin4 12  //D6

#define SwitchPin1 10  //SD3
#define SwitchPin2 D3  //D3
#define SwitchPin3 13  //D7
#define SwitchPin4 3   //RX
#define SensorPin 2    //D4
#define wifiLed 16  //D0

//Change the virtual pins according the rooms
#define VPIN_BUTTON_1 V1
#define VPIN_BUTTON_2 V2
#define VPIN_BUTTON_3 V3
#define VPIN_BUTTON_4 V4
#define VPIN_BUTTON_C V5
#define VPIN_FIRE V6
#define VPIN_FIRE_DISABLE V7

// Relay State
bool toggleState_1 = LOW;  //Define integer to remember the toggle state for relay 1
bool toggleState_2 = LOW;  //Define integer to remember the toggle state for relay 2
bool toggleState_3 = LOW;  //Define integer to remember the toggle state for relay 3
bool toggleState_4 = LOW;  //Define integer to remember the toggle state for relay 4

#include "BlynkEdgent.h"
int data = 0;

BLYNK_CONNECTED() {
  // Request the latest state from the server
  Blynk.syncVirtual(VPIN_BUTTON_1);
  Blynk.syncVirtual(VPIN_BUTTON_2);
  Blynk.syncVirtual(VPIN_BUTTON_3);
  Blynk.syncVirtual(VPIN_BUTTON_4);
  Blynk.syncVirtual(VPIN_FIRE_DISABLE);
}

// When App button is pushed - switch the state

BLYNK_WRITE(VPIN_BUTTON_1) {
  toggleState_1 = param.asInt();
  if (toggleState_1 == 1) {
    digitalWrite(RelayPin1, LOW);
  } else {
    digitalWrite(RelayPin1, HIGH);
  }
}

BLYNK_WRITE(VPIN_BUTTON_2) {
  toggleState_2 = param.asInt();
  if (toggleState_2 == 1) {
    digitalWrite(RelayPin2, LOW);
  } else {
    digitalWrite(RelayPin2, HIGH);
  }
}

BLYNK_WRITE(VPIN_BUTTON_3) {
  toggleState_3 = param.asInt();
  if (toggleState_3 == 1) {
    digitalWrite(RelayPin3, LOW);
  } else {
    digitalWrite(RelayPin3, HIGH);
  }
}

BLYNK_WRITE(VPIN_BUTTON_4) {
  toggleState_4 = param.asInt();
  if (toggleState_4 == 1) {
    digitalWrite(RelayPin4, LOW);
  } else {
    digitalWrite(RelayPin4, HIGH);
  }
}
BLYNK_WRITE(VPIN_BUTTON_C) {
  all_SwitchOff();
}

void all_SwitchOff() {
  toggleState_1 = 0;
  digitalWrite(RelayPin1, HIGH);
  Blynk.virtualWrite(VPIN_BUTTON_1, toggleState_1);
  delay(100);
  toggleState_2 = 0;
  digitalWrite(RelayPin2, HIGH);
  Blynk.virtualWrite(VPIN_BUTTON_2, toggleState_2);
  delay(100);
  toggleState_3 = 0;
  digitalWrite(RelayPin3, HIGH);
  Blynk.virtualWrite(VPIN_BUTTON_3, toggleState_3);
  delay(100);
  toggleState_4 = 0;
  digitalWrite(RelayPin4, HIGH);
  Blynk.virtualWrite(VPIN_BUTTON_4, toggleState_4);
  delay(100);
  //  Blynk.virtualWrite(VPIN_HUMIDITY, humidity1);
  //  Blynk.virtualWrite(VPIN_TEMPERATURE, temperature1);
}
BLYNK_WRITE(VPIN_FIRE_DISABLE) {
  int disable = param.asInt();
  Serial.printf("diable ::", disable);
  if (disable == 1) {
    int data = digitalRead(SensorPin);
  }
  else{
    Blynk.virtualWrite(VPIN_FIRE,0);
  }
}

void firesensor() {
  
  Serial.println(data);
  Blynk.virtualWrite(VPIN_FIRE, data);
}



void setup() {
  Serial.begin(115200);
  delay(100);

  pinMode(RelayPin1, OUTPUT);
  pinMode(RelayPin2, OUTPUT);
  pinMode(RelayPin3, OUTPUT);
  pinMode(RelayPin4, OUTPUT);

  pinMode(wifiLed, OUTPUT);

  pinMode(SwitchPin1, INPUT_PULLUP);
  pinMode(SwitchPin2, INPUT_PULLUP);
  pinMode(SwitchPin3, INPUT_PULLUP);
  pinMode(SwitchPin4, INPUT_PULLUP);
  pinMode(SensorPin, INPUT);
  //During Starting all Relays should TURN OFF
  digitalWrite(RelayPin1, HIGH);
  digitalWrite(RelayPin2, HIGH);
  digitalWrite(RelayPin3, HIGH);
  digitalWrite(RelayPin4, HIGH);

  digitalWrite(wifiLed, HIGH);

  BlynkEdgent.begin();

  Blynk.virtualWrite(VPIN_BUTTON_1, toggleState_1);
  Blynk.virtualWrite(VPIN_BUTTON_2, toggleState_2);
  Blynk.virtualWrite(VPIN_BUTTON_3, toggleState_3);
  Blynk.virtualWrite(VPIN_BUTTON_4, toggleState_4);
  Blynk.syncVirtual(VPIN_BUTTON_1, VPIN_BUTTON_2, VPIN_BUTTON_3, VPIN_BUTTON_4);
}

void loop() {
  BlynkEdgent.run();
  manual_control();  //Manual Switch Control
//  firesensor();
}
