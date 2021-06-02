#include <AccelStepper.h>

// Green Motor Driver
#define stepPinX 3
#define dirPinX 4

// Purple Motor Driver
#define stepPinY 5
#define dirPinY 6

// Stepper Moters
#define MotorInterfaceType 1

AccelStepper stepperX = AccelStepper(MotorInterfaceType, stepPinX, dirPinX);
AccelStepper stepperY = AccelStepper(MotorInterfaceType, stepPinY, dirPinY);

#define STEPPER_MOTOR_MAX_SPEED 1000.0
#define STEPPER_MOTOR_ACCELERATION 200.0

// Box Dimensions
#define X -850
#define Y 550

/*
The encoded positions in the box. 
0 is the neutral position, with row and column equal to 0.

|01 11 21|
|00 10 20|
*/
#define XS 3
#define YS 2

const int ys[YS] = {(Y / 4) * 1, (Y / 4) * 3};
const int xs[XS] = {(X / 6) * 1, (X / 6) * 3, (X / 6) * 5};

// Moisture sensors
// We only have one moisture sensor
int moistureSensor11 = A0;

// Air: ~680
// Water: ~290
const int moistLimit = 500;
boolean goTest = true;

void setup()
{
  // Setup stepper motors
  stepperX.setMaxSpeed(STEPPER_MOTOR_MAX_SPEED);
  stepperX.setAcceleration(STEPPER_MOTOR_ACCELERATION);

  stepperY.setMaxSpeed(STEPPER_MOTOR_MAX_SPEED);
  stepperY.setAcceleration(STEPPER_MOTOR_ACCELERATION);
}

// MARK: - Move functions
void moveToXY(int x, int y)
{
  moveToX(x);
  moveToY(y);
}

void moveToX(int x)
{
  stepperX.move(x);
  stepperY.move(x);

  boolean stop = false;

  while (!stop)
  {
    stepperX.run();
    stepperY.run();

    if (stepperX.distanceToGo() == 0 && stepperY.distanceToGo() == 0)
    {
      stop = true;
    }
  }
}

void moveToY(int y)
{
  stepperY.move(y);

  boolean stop = false;

  while (!stop)
  {
    stepperY.run();

    if (stepperY.distanceToGo() == 0)
    {
      stop = true;
    }
  }
}

boolean needWater(int pin)
{
  int moistValue = analogRead(pin);

  if (moistValue > moistLimit)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void visitEveryZone()
{
  for (long i = 0; i < XS; i++)
  {
    for (long j = 0; j < YS; j++)
    {
      moveToXY(xs[i], ys[j]);
      moveToXY(-xs[i], -ys[j]);
    }
  }
}

void loop()
{
  monitorNeedWater();
}

void monitorNeedWater()
{
  delay(1000); // Simulate a day passing

  if (needWater(moistureSensor11))
  {
    moveToXY(xs[1], ys[1]);

    delay(3000); // Simulate that it is watering

    moveToXY(-xs[1], -ys[1]);
  }
}

// MARK: - tests

void testLoop()
{
  delay(5000); // We need time to react

  if (goTest)
  {
    // Include tests here:
    // testBoxX(5);
    // testBoxX(10);
    // testBoxY(5);
    // testBoxY(10);
    testVisitEveryZone(5);
  }

  goTest = false;
}

void testBoxX(int testRuns)
{
  for (int i = 0; i < testRuns; i++)
  {
    moveToX(X);
    delay(3000);
    moveToX(-X);
    delay(3000);
  }
}

void testBoxY(int testRuns)
{
  for (int i = 0; i < testRuns; i++)
  {
    moveToY(Y);
    delay(3000);
    moveToY(-Y);
    delay(3000);
  }
}

void testBoxXY(int testRuns)
{
  for (int i = 0; i < testRuns; i++)
  {
    moveToXY(X, Y);
    moveToXY(-X, -Y);
  }
}

void testVisitEveryZone(int testRuns)
{
  for (int i = 0; i < testRuns; i++)
  {
    visitEveryZone();
  }
}