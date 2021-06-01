#include <AccelStepper.h>

#define dirPin 2
#define stepPin 3
#define dirPinCol 4
#define stepPinCol 5
#define motorInterfaceType 1

#define boxWidth 600
#define boxLength 1000 // This should be experimented with
#define max_speed 1000

/*
The encoded positions in the box. 0 is the neutral position, with row and column equal to 0.
|01 11 12|
|00 01 02|
*/
#define r0 250
#define r1 500
#define c0 300
#define c1 500
#define c2 700

AccelStepper stepperRow = AccelStepper(motorInterfaceType, stepPin, dirPin);
AccelStepper stepperCol = AccelStepper(motorInterfaceType, stepPinCol, dirPinCol);

void setup() {
  stepperRow.setCurrentPosition(0);
  stepperCol.setCurrentPosition(0);
  
  Serial.begin(9600);
  
  Serial.println("Flora is about to begin...");
  
  stepperRow.setMaxSpeed(max_speed);
  stepperRow.setAcceleration(200.0);

  stepperCol.setMaxSpeed(max_speed);
  stepperCol.setAcceleration(200.0);

  stepperRow.move(-r0);
  stepperRow.runToPosition();

  // ---
  stepperCol.move(-c0);
  stepperRow.move(-c0);
  while (stepperRow.distanceToGo() == 0 
          && stepperCol.distanceToGo() == 0) {
      stepperRow.run();
      stepperCol.run();
  }
  
  //stepper
}

void loop() {
  // BASED ON SIGNAL FROM MOISTURIZING SENSORS WE SHOULD KNOW WHERE TO MOVE.
  // WE HAVE HARDCODED IT FOR THE MVP.

  /*int r = 0;
  int c = 1;
  
  // Position 00
  if (r == 0 && c == 1) moveToPos(r0, c1);
  
  // Position 00
  if (r == 0 && c == 2) moveToPos(r0, c2);
  
  // Position 00
  if (r == 1 && c == 0) moveToPos(r1, c0);
  
  // Position 00
  if (r == 1 && c == 1) moveToPos(r1, c1);
  
  // Position 00 
  if (r == 1 && c == 2) moveToPos(r1, c2);*/

  // bool stop = false;
  // while(!stop) {
  //   stepperCol.move(-r0);
  //   stepperCol.runSpeedToPosition();
  //   delay(2000);
  //   stop = true;
  //   Serial.println("Flora is done...");
  // }


  //moveToPos(r0, c0);
}

void moveToPos(int r, int c) {
  // move to desired row
  stepToRow(true, r);

  // move to desired column
  stepToColumn(true, c);

  // THE DELAY IMPLIES THE HOSE WATERING
  delay(3000);

  // move back to origo for row
  stepToRow(false, r);

  // move back to origo for column
  stepToColumn(false, c);
}

void stepToRow(boolean isForward, int posVar) {
  int pos = posVar;
  if (isForward) {
    pos = -posVar;
  } 
  stepperRow.move(pos);
  stepperRow.runSpeedToPosition();
}

void stepToColumn(boolean isForward, int posVar) {
  int pos = posVar;
  if (isForward) {
    pos = -posVar;
  }
  
  stepperCol.move(pos);
  stepperCol.runSpeedToPosition();
  stepperRow.move(pos);
  stepperRow.runSpeedToPosition();
  
  delay(2000);
}