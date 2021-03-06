#include <FastLED.h>
#define LED_PIN 2
#define LED_PIN2 3
#define LED_PIN3 4
#define LED_PIN4 5
#define LED_PIN5 6
#define LED_PIN6 7
#define LED_PIN7 8
#define LED_PIN8 9

#define NUM_LEDS    17 //make sure this is one below actual value
CRGB leds[NUM_LEDS];
CRGB leds2[NUM_LEDS];
CRGB leds3[NUM_LEDS];
CRGB leds4[NUM_LEDS];
CRGB leds5[NUM_LEDS];
CRGB leds6[NUM_LEDS];
CRGB leds7[NUM_LEDS];
CRGB leds8[NUM_LEDS];
CRGB leds9[NUM_LEDS];

bool ascendState = true;
int colorCeil = 25;
int colorFloor = 0;
int color = colorFloor; //HSV color code
int light = 0; // store the current light value
int light2 = 0;
int light3 = 0;
int light4 = 0;
int light5 = 0;
int light6 = 0;
int light7 = 0;
int light8 = 0;

// these are the values that control each LED strip's brightness
int BrightnessValue = 0;
int BrightnessValue2 = 0;
int BrightnessValue3 = 0;
int BrightnessValue4 = 0;
int BrightnessValue5 = 0;
int BrightnessValue6 = 0;
int BrightnessValue7 = 0;
int BrightnessValue8 = 0;

int delayTime = 100;

//function that relates photoresister input to rgb brightness
int LightToBrightConvert(int lightreading) {
  int x;
  int y;
  int bright;
  if (lightreading > 200) {
    return 50;
  }
  else if (lightreading < 10) {
    return 255;
  }
  x = lightreading;

  //testing out different functions
  y = 0.0095 * pow(x, 2) * 3.0658 * x + 284.7118;
  //y=0.0144*pow(x,2)-4.1105*x+294.6617;
  //y=0.0255*pow(x,2)-6.4441*x+316.8860;
  //y=0.0801*pow(x,2)-17.9035*x+426.0234;
  //y = -0.6273*x+237.3370; //best for dark rooms with small ariation in lighting
  //y = 267.2167 - 1.2388*x + 0.0017*pow(x,2);
  //y = -0.3263158*x+263.1579;
  //y = 516.11*pow(x,-0.3062021);
  bright = y;
  return bright;
}

//Checks to see if the difference in reading is enough to constitute
//a change in lighting brightness
//This is done to smooth out the lighting and prevent it from
//constantly flickering

int isClose(int newReading, int oldReading) {
  //Checks if old reading and new reading are more than a certain number apart
  if (abs(newReading - oldReading) > 2) {
    return newReading;
  }
  else {
    return oldReading;
  }

}



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //configure serial to talk to computer
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.addLeds<WS2812B, LED_PIN2, GRB>(leds2, NUM_LEDS);
  FastLED.addLeds<WS2812B, LED_PIN3, GRB>(leds3, NUM_LEDS);
  FastLED.addLeds<WS2812B, LED_PIN4, GRB>(leds4, NUM_LEDS);
  FastLED.addLeds<WS2812B, LED_PIN5, GRB>(leds5, NUM_LEDS);
  FastLED.addLeds<WS2812B, LED_PIN6, GRB>(leds6, NUM_LEDS);
  FastLED.addLeds<WS2812B, LED_PIN7, GRB>(leds7, NUM_LEDS);
  FastLED.addLeds<WS2812B, LED_PIN8, GRB>(leds8, NUM_LEDS);
}

void loop() {
  // put your main code here, to run repeatedly:

  //read photoresistor analog data and checks to see how
  //close it is to old data

  light = isClose(analogRead(A3), light); // read and save value from PR
  light2 = isClose(analogRead(A1), light2); // read and save value from PR
  light3 = isClose(analogRead(A8), light3) - 20; // read and save value from PR
  light4 = isClose(analogRead(A7), light4); // read and save value from PR
  light5 = isClose(analogRead(A6), light5); // read and save value from PR
  light6 = isClose(analogRead(A5), light6); // read and save value from PR
  light7 = isClose(analogRead(A4), light7); // read and save value from PR
  light8 = isClose(analogRead(A2), light8); // read and save value from PR

  //test print code for photoresistors

  /*Serial.println("light 1");
    Serial.println(light);
    Serial.println("light 2");
    Serial.println(light2);
    Serial.println("light 3");
    Serial.println(light3);
    Serial.println("light 4");
    Serial.println(light4);
    Serial.println("light 5");
    Serial.println(light5);
    Serial.println("light 6");
    Serial.println(light6);
    Serial.println("light 7");
    Serial.println(light7);
    Serial.println("light 8");
    Serial.println(light8);*/

  //This is where light reading values are given a corresponding brightness value using a Linear Relationship
  BrightnessValue =  LightToBrightConvert(light);
  BrightnessValue2 =  LightToBrightConvert(light2);
  BrightnessValue3 =  LightToBrightConvert(light3);
  BrightnessValue4 =  LightToBrightConvert(light4);
  BrightnessValue5 =  LightToBrightConvert(light5);
  BrightnessValue6 =  LightToBrightConvert(light6);
  BrightnessValue7 =  LightToBrightConvert(light7);
  BrightnessValue8 =  LightToBrightConvert(light8);

  //light 5
  //fill_solid( leds, NUM_LEDS, CHSV(color,BrightnessValue5,BrightnessValue5));
  for (int i = 1; i <= NUM_LEDS; i++) {
    leds[i] = CHSV(color + i, BrightnessValue5, BrightnessValue5);
  }
  //light 7
  //fill_solid( leds2, NUM_LEDS, CHSV(color,BrightnessValue7,BrightnessValue7));
  for (int i = 1; i <= NUM_LEDS; i++) {
    leds2[i] = CHSV(color + i, BrightnessValue7, BrightnessValue7);
  }
  //light 3??
  //fill_solid( leds3, NUM_LEDS, CHSV(color,BrightnessValue3,BrightnessValue3));
  for (int i = 1; i <= NUM_LEDS; i++) {
    leds3[i] = CHSV(color + i, BrightnessValue3, BrightnessValue3);
  }
  //light 1
  //fill_solid( leds4, NUM_LEDS, CHSV(color,BrightnessValue,BrightnessValue));
  for (int i = 1; i <= NUM_LEDS; i++) {
    leds4[i] = CHSV(color + i, BrightnessValue, BrightnessValue);
  }
  //light 2
  //fill_solid( leds5, NUM_LEDS, CHSV(color,BrightnessValue2,BrightnessValue2));
  for (int i = 1; i <= NUM_LEDS; i++) {
    leds5[i] = CHSV(color + i, BrightnessValue2, BrightnessValue2);
  }
  //light 6
  //fill_solid( leds6, NUM_LEDS, CHSV(color,BrightnessValue6,BrightnessValue6));
  for (int i = 1; i <= NUM_LEDS; i++) {
    leds6[i] = CHSV(color + i, BrightnessValue6, BrightnessValue6);
  }
  //light 8
  //fill_solid( leds7, NUM_LEDS, CHSV(color,BrightnessValue8,BrightnessValue8));
  for (int i = 1; i <= NUM_LEDS; i++) {
    leds7[i] = CHSV(color + i, BrightnessValue8, BrightnessValue8);
  }
  //light 4
  //fill_solid( leds8, NUM_LEDS, CHSV(color,BrightnessValue4,BrightnessValue4));
  for (int i = 1; i <= NUM_LEDS; i++) {
    leds8[i] = CHSV(color + i, BrightnessValue4, BrightnessValue4);
  }

  FastLED.show();

  //code that changes the color of the light
  if (ascendState) {
    color = color + 1;
    if (color >= colorCeil) {
      ascendState = false;
    }
  }
  else {
    color = color - 1;
    if (color <= colorFloor) {
      ascendState = true;
    }
  }

  delay(delayTime); // make less abrupt
}
