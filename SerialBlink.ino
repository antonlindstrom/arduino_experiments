/*
 * Turn a LED on and off by sending
 * data to the Arduino via the serial
 * interface.
 *
 * Author:  Anton Lindstrom
 * Contact: http://antonlindstrom.com
 */

int pin = 13;

volatile int state = LOW;

/*
 * Setup phase
 */
void setup() {
  pinMode(pin, OUTPUT);
  pinMode(receiver, INPUT);
  Serial.begin(9600);
}

/*
 * Main
 */
void loop() {
  if ( change() ) {
    shift();
    digitalWrite(pin, state);
    print_state();
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
 * Shift state from LOW to HIGH
 */
void shift() {
  if ( state == LOW )
    state = HIGH;
  else
    state = LOW;
}

/*
 * Print int state on serial
 */
void print_state() {
  Serial.print("State of LED: ");
  Serial.println(state);
}
