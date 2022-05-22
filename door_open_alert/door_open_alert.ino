#include <Arduino.h>
#include <WiFi.h>
// Set GPIOs for LED and reedswitch
const int reedSwitch = 13;
const int led = 2; //optional

// Detects whenever the door changed state
bool changeState = false;

// Holds reedswitch state (1=opened, 0=close)
bool state;
String doorState;

// Auxiliary variables (it will only detect changes that are 1500 milliseconds apart)
unsigned long previousMillis = 0; 
const long interval = 1500;

const char* host = "maker.ifttt.com";
const char* apiKey = "ikOgwLc8dw_eIpH18MD-jF79rUL5GHYSqtFodg5Tilf";

// Runs whenever the reedswitch changes state
ICACHE_RAM_ATTR void changeDoorStatus() {
  Serial.println("State changed");
  changeState = true;
}

void setup() {

  pinMode(reedSwitch, INPUT_PULLUP);
  state = digitalRead(reedSwitch);

  // Set LED state to match door state
  pinMode(led, OUTPUT);
  digitalWrite(led, !state);
  
  // Set the reedswitch pin as interrupt, assign interrupt function and set CHANGE mode
  attachInterrupt(digitalPinToInterrupt(reedSwitch), changeDoorStatus, CHANGE);

  Serial.begin(115200);
  WiFi.begin("Bajwa residence", "70315o9b");

}


void loop() {
  if (changeState){
    unsigned long currentMillis = millis();
    if(currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      // If a state has occured, invert the current door state   
      state = !state;
      if(state) {
        doorState = "closed";
      }
      else{
        doorState = "open";
      }
      digitalWrite(led, !state);
      changeState = false;
      Serial.println(state);
      Serial.println(doorState);

    }  
  }
}
