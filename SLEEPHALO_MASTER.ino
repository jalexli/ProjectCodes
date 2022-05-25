// Wire Master Reader
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Reads data from an I2C/TWI slave device
// Refer to the "Wire Slave Sender" example for use with this

// Created 29 March 2006

// This example code is in the public domain.

#include <FastLED.h>
#include <Wire.h>

// Global Variables
#define NUM_LEDS 600
#define LED_PIN 6
#define LED_TYPE WS2811
#define BRIGHTNESS 1

//LED variables

CRGB leds[NUM_LEDS];

int HueVal = 190;
int HueVal2 = 30;
int delay_time = 500;
uint8_t hue = 192;

// different states
// state where try to make user wake up ie. morning
bool wakeupstate = false;
//state where try to make user sleep ie. night
bool sleepstate = true;
bool asleep = true;
bool awake = false;
unsigned long previousTime1 = 0;
unsigned long previousTime = 0;
int heartRate = 70;

// multiply/divide heartrate by this number to get slightly slower/faster rhythm of 
//animation than heartrate to induce awake or sleep state
int multiplier = 1.2;

void setup() {
  //LED setup
  FastLED.addLeds<WS2811, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(50);
  
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
}

void loop() {

  unsigned long currentTime1 = millis();
  // after 8 hours changes from sleep routine to wake up routine. Changes from trying to make user
  //fall asleep to making user wake up
  if (currentTime1 - previousTime1 >= 28800000){
    if(wakeupstate == true){
      wakeupstate=false;
      sleepstate=true;
    }
    else if(wakeupstate == false){
      wakeupstate=true;
      sleepstate=false;
    }
  previousTime1 = currentTime1;
  }


  //animation for inducing sleep while awake, there is not multiplier in this scenario 
  //try to maintain the users sleep state
  if (sleepstate = true and awake == true){
  //converts heartrate to milliseconds per beat
  int delay_time = (heartRate/60 * 1000);
  for (int i = 297+46+30; i < 297 + 46+30+20; i++) {
    leds[i] = CHSV(HueVal, 255, 255);
  }
  FastLED.show();
  delay(delay_time);

  for (int i = 297+46; i < 297 + 46+30; i++) {
    leds[i] = CHSV(HueVal, 255, 255);
  }
  FastLED.show();
  delay(delay_time);
  
  for (int i = 297; i < 297 + 46; i++) {
    leds[i] = CHSV(HueVal, 255, 255);
  }
  FastLED.show();
  delay(delay_time);

  for (int i = 232; i < 232 + 65; i++) {
    leds[i] = CHSV(HueVal, 255, 255);
  }
  FastLED.show();
  delay(delay_time);

  for (int i = 136; i < 232; i++) {
    leds[i] = CHSV(HueVal, 255, 255);
  }
  FastLED.show();
  delay(delay_time);
  

  for (int i = 0; i < 136; i++) {
    leds[i] = CHSV(HueVal, 255, 255);
  }
  FastLED.show();
  delay(delay_time);
 
  HueVal += 10;
  if (HueVal>250){
    HueVal=190;
  }
  }

  //keeping sleep state while asleep
  if (sleepstate = true and asleep == true){
  //converts heartrate to milliseconds per beat and applies a multiplier
  int delay_time = (heartRate/60 * 1000)*multiplier;
  for (int i = 297+46+30; i < 297 + 46+30+20; i++) {
    leds[i] = CHSV(HueVal, 255, 255);
  }
  FastLED.show();
  delay(delay_time);

  for (int i = 297+46; i < 297 + 46+30; i++) {
    leds[i] = CHSV(HueVal, 255, 255);
  }
  FastLED.show();
  delay(delay_time);
  
  for (int i = 297; i < 297 + 46; i++) {
    leds[i] = CHSV(HueVal, 255, 255);
  }
  FastLED.show();
  delay(delay_time);

  for (int i = 232; i < 232 + 65; i++) {
    leds[i] = CHSV(HueVal, 255, 255);
  }
  FastLED.show();
  delay(delay_time);

  for (int i = 136; i < 232; i++) {
    leds[i] = CHSV(HueVal, 255, 255);
  }
  FastLED.show();
  delay(delay_time);
  

  for (int i = 0; i < 136; i++) {
    leds[i] = CHSV(HueVal, 255, 255);
  }
  FastLED.show();
  delay(delay_time);
 
  HueVal += 10;
  if (HueVal>250){
    HueVal=190;
  }
  }

  //wakes user up in morning
  if (wakeupstate=true){
  //converts heartrate to milliseconds per beat and applies a multiplier
  //animation rhythm faster than heartrate
  int delay_time = (heartRate/60 * 1000)/multiplier;
  for (int i = 297+46+30; i < 297 + 46+30+20; i++) {
    leds[i] = CHSV(HueVal2, 255, 255);
  }
  FastLED.show();
  delay(delay_time);

  for (int i = 297+46; i < 297 + 46+30; i++) {
    leds[i] = CHSV(HueVal2, 255, 255);
  }
  FastLED.show();
  delay(delay_time);
  
  for (int i = 297; i < 297 + 46; i++) {
    leds[i] = CHSV(HueVal2, 255, 255);
  }
  FastLED.show();
  delay(delay_time);

  for (int i = 232; i < 232 + 65; i++) {
    leds[i] = CHSV(HueVal2, 255, 255);
  }
  FastLED.show();
  delay(delay_time);

  for (int i = 136; i < 232; i++) {
    leds[i] = CHSV(HueVal2, 255, 255);
  }
  FastLED.show();
  delay(delay_time);
  

  for (int i = 0; i < 136; i++) {
    leds[i] = CHSV(HueVal2, 255, 255);
  }
  FastLED.show();
  delay(delay_time);
 
  HueVal += 10;
  if (HueVal>60){
    HueVal=30;
  }
  }

// Requests heart rate metrics from slave controller every 10 minutes and sets user state
  unsigned long currentTime = millis();
  if(currentTime-previousTime == 600000){
  Wire.requestFrom(8, 2);    // request 2 bytes from slave device #8\
  while (Wire.available()) { // slave may send less than requested
    int c = Wire.read(); // receive a byte as character
    //revieves and saves heart rate metric
    heartRate = c;
  if(heartRate >= 55){
    awake = true;
    asleep = false;
  }
  else{
    awake = false;
    asleep = true;
  }
}
}
