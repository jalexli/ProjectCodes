// Wire Slave Sender
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Sends data as an I2C/TWI slave device
// Refer to the "Wire Master Reader" example for use with this

// Created 29 March 2006

// This example code is in the public domain.

/* This code works with MAX30102 + 128x32 OLED i2c + Buzzer and Arduino UNO
   It's displays the Average BPM on the screen, with an animation and a buzzer sound
   everytime a heart pulse is detected
   It's a modified version of the HeartRate library example
   Refer to www.surtrtech.com for more details or SurtrTech YouTube channel
*/

#include <Wire.h>
//-----------------------------------------------------------------------
#include "MAX30105.h" //max3010x library
#include "heartRate.h" //heart rate calculating aglorithm
MAX30105 particleSensor;

const byte RATE_SIZE = 6; //Increase this for more averaging. 4 is good.
byte rates[RATE_SIZE]; //Array of heart rates
byte rateSpot = 0;
long lastBeat = 0; //Time at which the last beat occurred
int beatsPerMinute;
int beatAvg;

//-----------------------------------------------------------------------

unsigned long previousTime = 0;
unsigned long previousTime1 = 0;

void setup() {
  Serial.begin(9600);
  // Initialize sensor
  particleSensor.begin(Wire, 9600); //Use default I2C port, 400kHz speed
  particleSensor.setup(); //Configure sensor with default settings
  particleSensor.setPulseAmplitudeRed(0x0A); //Turn Red LED to low to indicate sensor is running

  //initialize master and slave
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event
}


void loop() {
  //hear rate sensor code
  long irValue = particleSensor.getIR();    //Reading the IR value it will permit us to know if there's a finger on the sensor or not
  //Also detecting a heartbeat
  if (checkForBeat(irValue) == true)                        //If a heart beat is detected
  {
    tone(3, 1000);                                       //And tone the buzzer for a 100ms you can reduce it it will be better
    delay(100);
    noTone(3);                                          //Deactivate the buzzer to have the effect of a "bip"
    //We sensed a beat!
    long delta = millis() - lastBeat;                   //Measure duration between two beats
    lastBeat = millis();
    beatsPerMinute = 60 / (delta / 1000.0);           //Calculating the BPM
  }
  if (beatsPerMinute < 255 && beatsPerMinute > 20)               //To calculate the average we strore some values (4) then do some math to calculate the average
  {
    rates[rateSpot++] = (byte)beatsPerMinute; //Store this reading in the array
    rateSpot %= RATE_SIZE; //Wrap variable

    //Take average of readings
    beatAvg = 0;
    for (byte x = 0 ; x < RATE_SIZE ; x++)
      beatAvg += rates[x];
    beatAvg /= RATE_SIZE;
  }
  if (irValue < 7000) {      //If no finger is detected it inform the user and put the average BPM to 0 or it will be stored for the next measure
    beatAvg = 0;
    noTone(3);
  }
}


//sends state of user to master controller
// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  String   stringAvg = String(beatsPerMinute);
  Wire.write(stringAvg.c_str());
}
