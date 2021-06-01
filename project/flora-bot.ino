#include <AccelStepper.h>

// Box
#define XBoxLength 800
#define YBoxLength 500

// Green
#define stepPinX 3
#define dirPinX 4

// Purple
#define stepPinY 5
#define dirPinY 6

#define motorInterfaceType 1

/*
The encoded positions in the box. 0 is the neutral position, with row and column equal to 0.
|01 11 21|
|00 10 20|
*/
#define y0 (YBoxLength / 4) * 1
#define y1 (YBoxLength / 4) * 3
#define x0 (-XBoxLength / 6) * 1
#define x1 (-XBoxLength / 6) * 3
#define x2 (-XBoxLength / 6) * 5

// Define some steppers and the pins the will use
AccelStepper stepperX = AccelStepper(motorInterfaceType, stepPinX, dirPinX);
AccelStepper stepperY = AccelStepper(motorInterfaceType, stepPinY, dirPinY);

void setup()
{  
    stepperX.setMaxSpeed(1000);
    stepperX.setAcceleration(200.0);
    stepperX.setCurrentPosition(0);
    
    stepperY.setMaxSpeed(1000);
    stepperY.setAcceleration(200.0);
    stepperY.setCurrentPosition(0);
}

void moveToXY(int x, int y) {
  moveToX(x);
  moveToY(y);
}

void moveToX(int x) {
  stepperX.moveTo(x);
  stepperY.moveTo(x);

  boolean stop = false;

  while(!stop) {
    stepperX.run();
    stepperY.run();

    if (stepperX.distanceToGo() == 0 
      && stepperY.distanceToGo() == 0) {
        stop = true;
    }
  }
}

void moveToY(int y) {
  stepperY.moveTo(y);
  
  boolean stop = false;

  while(!stop) {
    stepperY.run();

    if (stepperY.distanceToGo() == 0) {
        stop = true;
    }
  }
}

void loop()
{  
  delay(5000);
  moveToXY(x0, y0);
  moveToXY(0, 0);
  moveToXY(x0, y1);
  moveToXY(0, 0);
  moveToXY(x1, y0);
  moveToXY(0, 0);
  moveToXY(x1, y1);
  moveToXY(0, 0);
  moveToXY(x2, y0);
  moveToXY(0, 0);
  moveToXY(x2, y1);
  moveToXY(0, 0);
}