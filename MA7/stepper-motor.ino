// CODE FROM: https://www.seeedstudio.com/blog/2019/03/04/driving-a-28byj-48-stepper-motor-with-a-uln2003-driver-board-and-arduino/

#include <Stepper.h>

#define STEPS 2038 // the number of steps in one revolution of your motor (28BYJ-48)

Stepper stepper(STEPS, 8, 10, 9, 11);

void setup() {
  Serial.begin(9600);
}

void loop() {
  stepper.setSpeed(1); // 1 rpm
  stepper.step(2038); // do 2038 steps -- corresponds to one revolution in one minute
  delay(1000); // wait for one second
  stepper.setSpeed(6); // 6 rpm
  stepper.step(-2038); // do 2038 steps in the other direction with faster speed -- corresponds to one revolution in 10 seconds
}