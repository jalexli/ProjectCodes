#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

char prevChrState = 'm'; //determines direciton "eyes" look
// 'r' for right, 'l' for left, 'm' for middle
//this is used to give instrucitons to servo motors
char chrState;

// proximity sensor parameters
int trigPin = 3;
int echoPin = 2;
int trigPin2 = 6;
int echoPin2 = 5;
int distance;
int distance2;
int duration;
int duration2;
int prevDist;
int handDistance;
int handDistance2;

const int buttonPin = 10; //button pin

void setup() {
  Serial.begin(57600);
  Serial.println('Ready');

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  pinMode(buttonPin, INPUT);

  // put your setup code here, to run once:
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever

  }
}

void loop() {

  if (digitalRead(buttonPin) == HIGH) {
    Serial.write('m');
    display.clearDisplay();
    display.fillRoundRect(16, 0, 96, 96, 16, WHITE);
    display.display();
    delay(100);
    display.clearDisplay();

    display.fillRoundRect(16, 12, 96, 96, 16, WHITE);
    display.display();
    delay(100);
    display.clearDisplay();

    display.fillRoundRect(16, 24, 96, 96, 16, WHITE);
    display.display();

    delay(100);
    display.clearDisplay();

    display.fillRoundRect(16, 36, 96, 96, 16, WHITE);
    display.display();
    delay(100);
    display.clearDisplay();

    display.fillRoundRect(16, 48, 96, 96, 16, WHITE);
    display.display();
    delay(100);
    display.clearDisplay();

    display.fillRoundRect(16, 60, 96, 96, 16, WHITE);
    display.display();
    delay(100);
    display.clearDisplay();
    display.display();
    delay(5000);
  }

  handDistance = calculateDist();
  handDistance2 = calculateDist2();
  //Serial.println(handDistance);
  //Serial.println(handDistance2);

  if (handDistance <= 10 and handDistance2 <= 10) {
    display.clearDisplay();
    display.drawRoundRect(24, 0 , 80, 80, 16, WHITE);
    display.display();
    Serial.write('m');
  }
  else if ( handDistance <= 10 and handDistance2 > 10) {
    display.clearDisplay();
    display.fillRoundRect(0, 0, 80, 80, 16, WHITE);
    display.display();
    Serial.write('l');
  }
  else if (handDistance > 10 and handDistance2 <= 10) {
    display.clearDisplay();
    display.fillRoundRect(48, 0, 80, 80, 16, WHITE);
    display.display();
    Serial.write('r');
  }
  else {
    display.clearDisplay();
    display.fillRoundRect(16, 0, 96, 96, 16, WHITE);
    display.display();
    Serial.write('m');
  }
}

char receiveChar() {
  if (Serial.available() > 0) {
    char receivedChar = Serial.read();
    return receivedChar;
  }
}

int calculateDist()
{

  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)

  return distance;

}

int calculateDist2()
{

  // Clears the trigPin condition
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration2 = pulseIn(echoPin2, HIGH);
  // Calculating the distance
  distance2 = duration2 * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  return distance2;

}
