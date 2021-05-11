// #include <Arduino.h>
// #include <Servo.h>

// int SERVO_PIN = 9;
// int POT = A5;
// int angle = 0;
// int readValue = 0;
// Servo servo;

// void setup() {
//   pinMode(POT, INPUT);
//   servo.attach(SERVO_PIN);
// }

// void loop() {
//   readValue = analogRead(POT);
//   angle = map(readValue, 0, 1023, 0, 180);
//   servo.write(angle);
//   delay(100);
// }