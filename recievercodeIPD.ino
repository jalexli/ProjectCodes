#include <Servo.h>;
Servo servo;
int currPos = 0; // stores position of servo
char prevRead ; //stores previous Serial read so that it can be compared
//with current read to know when a reading first changes
char Read;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(57600);
  servo.attach(9);
  servo.write(90);
  currPos = 90;
}

void loop() {
  // put your main code here, to run repeatedly:
  Read = fetchInstructions();
  if (Read == 'm'){
    moveServo(90);
    
  }
  else if(Read == 'l'){
    //if eyes and hand are left, servo moves right
    moveServo(60);
    
  }
  else if(Read == 'r'){
    //if eyes and hand are right, servo moves left
    moveServo(120);
    
  }

}

//returns instructions from other arduino, if none available, defaults
//to previous instructions

char fetchInstructions() {
  if (Serial.available() > 0) {
    char chr = Serial.read();
    return chr;
  }
  else {
    return prevRead;
  }
}

void moveServo(int b) {
  int a = currPos;
  if (a < b) {
    for (int i = a; i <= b; i++) {
      servo.write(i);
      delay(10);

    }
  }
  else if (a > b) {
    for (int i = a; i >= b; i--) {
      servo.write(i);
      delay(10);
    }
  }
  else {

  }
  currPos = b;
}
