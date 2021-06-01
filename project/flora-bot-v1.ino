#include <AccelStepper.h>

#define dirPin 2
#define stepPin 3
#define dirPinCol 4
#define stepPinCol 5
#define motorInterfaceType 1

#define boxWidth 600
#define boxLength 1000 // This should be experimented with
#define stepsPrSec 50

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

  Serial.begin(9600);

  Serial.println("Add power!");
  
  delay(5000);
  
  stepperRow.setMaxSpeed(1000);
  stepperRow.setCurrentPosition(0);
  
  stepperCol.setMaxSpeed(1000);
  stepperCol.setCurrentPosition(0);

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

  Serial.println("r0, c0 begun...");
  moveToPos(r0, c0);
  Serial.println("r0, c0 finished...");
}

void moveToPos(int r, int c) {
  // move to desired row
  stepToRow(true, r);

  // move to desired column
  stepToColumn(true, c);

  stepperRow.setCurrentPosition(0);
  stepperCol.setCurrentPosition(0);

  // THE DELAY IMPLIES THE HOSE WATERING
  delay(3000);

  // move back to origo for row
  stepToRow(false, r);

  // move back to origo for column
  stepToColumn(false, c);

  delay(3000);  

  stepperRow.setCurrentPosition(0);
  stepperCol.setCurrentPosition(0);
}

void stepToRow(boolean isForward, int posVar) {
  if (isForward) {
    while(stepperRow.currentPosition() != -posVar)
    {
      stepperRow.setSpeed(-stepsPrSec);
      stepperRow.runSpeed();
    }
  } else {
    while(stepperRow.currentPosition() != posVar)
    {
      stepperRow.setSpeed(stepsPrSec);
      stepperRow.runSpeed();
    }
  }
}

void stepToColumn(boolean isForward, int posVar) {
  if (isForward) {
    while(stepperCol.currentPosition() != -posVar)
    {
      stepperCol.setSpeed(-stepsPrSec);
      stepperCol.runSpeed();
      stepperRow.setSpeed(-stepsPrSec);
      stepperRow.runSpeed();
    }
  } else {
    while(stepperCol.currentPosition() != posVar)
    {
      stepperCol.setSpeed(stepsPrSec);
      stepperCol.runSpeed();
      stepperRow.setSpeed(stepsPrSec);
      stepperRow.runSpeed();
    }
  }
}