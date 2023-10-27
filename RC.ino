//  Rally Controller for ESP32
//    Thomas Styles
//    Based on work by NordicRally

// Include Libraries
#include "esp_bt_main.h"
#include "esp_bt_device.h"
#include "esp_gap_bt_api.h"
#include <BleKeyboard.h>                                       // bleKeyboard
#include <Bounce2.h>                                           // Bounce

// Set Bluetooth Device Name
#define DeviceName "RCntrl P.1"
#define DeviceManufacturer "S.R.I."
#define BatteryLevel 69
BleKeyboard bleKeyboard(DeviceName, DeviceManufacturer, BatteryLevel);

/*
  BleKeyboard bleKeyboard("Bluetooth Device Name", "Bluetooth Device Manufacturer", 100);
  BleKeyboard bleKeyboard("RControl v0.1", "S.R.I. NZ", 69);
  BleKeyboard bleKeyboard("BarButtons", "", 69);
  BleKeyboard bleKeyboard("CICTRL", "", 69);
  BleKeyboard bleKeyboard("DMD2 CTL 4K", ".", 100);
*/

// Pinouts

/*
  //NodeMCU-32S
  int Button1 = 17;
  int Button2 = 16;
  int Button3 = 25;
  int Button4 = 26;
*/

// ESP32 DEVKITV1
int Button1 = 18;
int Button2 = 19;
int Button3 = 25;
int Button4 = 26;

/*
  // MH-ET LIVE MiniKit for ESP32
  int Button1 = 27;
  int Button2 = 32;
  int Button3 = 33;
  int Button4 = 35;
*/

// 0 to view all bonded devices addresses, 1 to remove
#define REMOVE_BONDED_DEVICES 0
// default 3, max 9
#define PAIR_MAX_DEVICES 9
// Buttons and position {0, 1, 2, 3}
#define NUM_BUTTONS 4
const uint8_t BUTTON_PINS[NUM_BUTTONS] = {Button1, Button2, Button3, Button4};

// BT Initialisation
bool initBluetooth() {
  if (!btStart()) {
    Serial.println("! Failed to initialise btStart !");
    return false;
  }

  if (esp_bluedroid_init() != ESP_OK) {
    Serial.println("! Failed to initialise bluedroid !");
    return false;
  }

  if (esp_bluedroid_enable() != ESP_OK) {
    Serial.println("! Failed to enable bluedroid !");
    return false;
  }
  return true;
}

// Toggle Mode
BLEServer* pServer = NULL;
bool toggle_mode = false;

void Toggle_Name() {
  if (toggle_mode == 1) {
    esp_ble_gap_set_device_name("RCntrl P.2");
    pServer->startAdvertising();
    Serial.println("* Toggle Name Change to Profile 2 *");
  } else {
    esp_ble_gap_set_device_name("RCntrl P.1");
    pServer->startAdvertising();
    Serial.println("* Toggle Name Change to Profile 1 *");
  }
}

// Format BT Device Addresses
uint8_t pairedDeviceBtAddr[PAIR_MAX_DEVICES][6];
char bda_str[18];
char *bda2str(const uint8_t* bda, char *str, size_t size) {
  if (bda == NULL || str == NULL || size < 18) {
    return NULL;
  }
  sprintf(str, "%02x:%02x:%02x:%02x:%02x:%02x",
          bda[0], bda[1], bda[2], bda[3], bda[4], bda[5]);
  return str;
}

// Bounce config
Bounce * buttons = new Bounce[NUM_BUTTONS];

// Setup, runs once
void setup() {
  // Serial
  Serial.begin(115200);
  Serial.println("<! Starting Rally Controller !>");
  // bleKeyboard
  bleKeyboard.begin();
  Serial.println("< bleKeyboard Started >");
  // Set pullup mode and bounce interval in ms
  for (int i = 0; i < NUM_BUTTONS; i++) {
    buttons[i].attach( BUTTON_PINS[i] , INPUT_PULLUP  );
    buttons[i].interval(100);
  }
  Serial.println("<! Rally Controller Started !>");
  esp_ble_gap_set_device_name("RCntrl P.1");
  pServer->startAdvertising();
}

// Loop, runs constantly
void loop() {
  if ( (digitalRead(18) == LOW) && (digitalRead(26) == LOW) ) {
    delay(5000);
    if ( (digitalRead(18) == LOW) && (digitalRead(26) == LOW) ) {
      toggle_mode = !toggle_mode;
      Serial.println("* Toggle Mode Status - " + (String)toggle_mode + " *");
      Toggle_Name();
    }
  }

  // Update the Bounce instance
  for (int i = 0; i < NUM_BUTTONS; i++)  {
    buttons[i].update();
  }

  // bleKeyboard hold functions

  // Button 1
  if ((buttons[0].read() == LOW) && (toggle_mode == false) && (bleKeyboard.isConnected())) {
    Serial.println("+ - Profile 1");
    bleKeyboard.write('=');
    delay(500);
  } else {
    if ((buttons[0].read() == LOW) && (toggle_mode == true) && (bleKeyboard.isConnected())) {
      Serial.println("KEY_MEDIA_PREVIOUS_TRACK - Profile 2");
      bleKeyboard.write(KEY_MEDIA_PREVIOUS_TRACK);
      delay(500);
    }
  }

  // Button 2
  if ((buttons[1].read() == LOW) && (toggle_mode == false) && (bleKeyboard.isConnected())) {
    Serial.println("- - Profile 1");
    bleKeyboard.write('-');
    delay(500);
  } else {
    if ((buttons[1].read() == LOW) && (toggle_mode == true) && (bleKeyboard.isConnected())) {
      Serial.println("KEY_MEDIA_NEXT_TRACK - Profile 2");
      bleKeyboard.write(KEY_MEDIA_NEXT_TRACK);
      delay(500);
    }
  }

  // Button 3
  if ((buttons[2].fell()) && (toggle_mode == false) && (bleKeyboard.isConnected())) {
    Serial.println("R - Profile 1");
    bleKeyboard.write('r');
    delay(500);
  } else {
    if ((buttons[2].fell)() && (toggle_mode == true) && (bleKeyboard.isConnected())) {
      Serial.println("KEY_MEDIA_VOLUME_DOWN - Profile 2");
      bleKeyboard.write(KEY_MEDIA_VOLUME_DOWN);
      delay(500);
    }
  }

  // Button 4
  if ((buttons[3].fell()) && (toggle_mode == false) && (bleKeyboard.isConnected())) {
    Serial.println("C - Profile 1");
    bleKeyboard.write('c');
    delay(500);
  } else {
    if ((buttons[3].fell()) && (toggle_mode == true) && (bleKeyboard.isConnected())) {
      Serial.println("KEY_MEDIA_VOLUME_UP - Profile 2");
      bleKeyboard.write(KEY_MEDIA_VOLUME_UP);
      delay(500);
    }
  }
}
