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

/*
 * Setup phase
 */
void setup() {
  servo_test.attach(9);
  Serial.begin(9600);
  Serial.println("OK");
}

/*
 * Main
 */
void loop() {
  int s = 90;
  s = change();
  if ( s != 0 ) {
    move_servo(s);
  }
}

/*
 * Listen to serial and return true
 * if something was entered on
 * serial
 */
int change() {
  while ( Serial.available() > 0 ) {
    int d = Serial.parseInt();

    if (Serial.read() == '\n')
      return d;
  }
}

/*
 * Moving servo
 */
void move_servo(int pos) {
  if ( pos > 180 )
    pos = 180;

  servo_test.write(pos);
  Serial.println(servo_test.read());
}

/* vim: set ts=2 sw=2 ft=cpp: */
