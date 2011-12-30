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

int pos = 0;

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
  if ( change() ) {
    move_servo();
  }
}

/*
 * Listen to serial and return true
 * if something was entered on
 * serial
 */
int change() {
  int   incoming_byte = 0;

  if ( Serial.available() > 0 ) {
    incoming_byte = Serial.read();
    if ( incoming_byte > 0)
      return true;
  }
  return false;
}

/*
 * Moving servo
 */
void move_servo() {
  pos += 10;
  servo_test.write(pos);
  Serial.println(servo_test.read());
  if ( servo_test.read() == 180 )
    pos = 0;
}

/* vim: set ts=2 sw=2 ft=cpp: */
