#include <AccelStepper.h>

// Green
#define stepPinX 3
#define dirPinX 4

// Purple
#define stepPinY 5
#define dirPinY 6

#define motorInterfaceType 1
AccelStepper stepperX = AccelStepper(motorInterfaceType, stepPinX, dirPinX);
AccelStepper stepperY = AccelStepper(motorInterfaceType, stepPinY, dirPinY);

// Box
#define XBoxLength 800
#define YBoxLength 500

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

// soil moisture sensor
const int sensor11Pin = A0;  
const int limit = 300; 

void setup()
{  
    Serial.begin(9600);

    stepperX.setMaxSpeed(1000);
    stepperX.setAcceleration(200.0);
    
    stepperY.setMaxSpeed(1000);
    stepperY.setAcceleration(200.0);

    // TODO setup partitioning of box and appertaining sensors
}

void moveToXY(int x, int y) {
  moveToX(x);
  moveToY(y);
}

void moveToX(int x) {
  stepperX.move(x);
  stepperY.move(x);

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
  stepperY.move(y);
  
  boolean stop = false;

  while(!stop) {
    stepperY.run();

    if (stepperY.distanceToGo() == 0) {
        stop = true;
    }
  }
}

boolean readMoistSensors(int pin) {
  int sensorValue = analogRead(pin); 

  Serial.println("Analog Value: ");
  Serial.println(sensorValue);

  boolean needWater = true;

  if (sensorValue > limit) {
    return needWater; 
  } else {
    return !needWater; 
  }
}

void loop()
{ 
  delay(1000); 
  boolean needWater = readMoistSensors(sensor11Pin);
  Serial.println(needWater);
  
  if (false) {
    moveToXY(x1, y1);
    delay(1000);
    moveToXY(-x1, -y1);
  }
}