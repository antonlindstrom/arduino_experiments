/*
 * Move a servo by sending
 * data to the Arduino via the serial
 * interface.
 *
 * Author:  Anton Lindstrom
 * Contact: http://antonlindstrom.com
 */

#include <Servo.h>

Servo servo_test;

int aPin = 1;

/*
 * Setup phase
 */
void setup() {
  servo_test.attach(9);
  Serial.begin(9600);
}

/*
 * Main
 */
void loop() {
  int pos = 0;
  pos = sensor_input();
  move_servo(levels(pos));
  delay(10);
}

/*
 * Sensor
 */
int sensor_input() {
  int aVal = 0;
  aVal = analogRead(aPin);
  return aVal;
}

/*
 * Sensor levels
 */
int levels(int i) {
  if ( i < 290)
    return 0;
  else if ( i < 360 )
    return 30;
  else if ( i < 420 )
    return 60;
  else if ( i < 480 )
    return 120;
  else
    return 180;
}

/*
 * Moving servo
 */
void move_servo(int pos) {
  servo_test.write(pos);
}

/* vim: set ts=2 sw=2 ft=cpp: */
