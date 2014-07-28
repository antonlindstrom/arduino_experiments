/*
 * Move a servo by sending
 * data to the Arduino via the pololu
 * serial servo controller.
 */

#include <SoftwareSerial.h>
 
// Define pins you're using for serial communication
// Don't need to use pins 0 and 1
#define RXPIN 3
#define TXPIN 4

// Reset pin on pololu
#define RSTPIN 11
 
// Set up the new serial port to transmit data
SoftwareSerial softSerial(RXPIN, TXPIN);

/*
 * Setup phase
 */
void setup() {
  // define pin modes for tx, rx:
  pinMode(RXPIN, INPUT);
  pinMode(TXPIN, OUTPUT);

  // Reset the servo controller
  pinMode(RSTPIN, OUTPUT);
  digitalWrite(RSTPIN, LOW);
  delay(50);
  digitalWrite(RSTPIN, HIGH);

  Serial.begin(9600);

  // set the data rate for the SoftwareSerial port
  softSerial.begin(9600);
}

/*
 * Main
 */
void loop() {

  if (move_servo(1, 500) < 0)
    Serial.println("Failed to set position to servo");

  delay(1000);

  if (move_servo(1, 5000) < 0)
    Serial.println("Failed to set position to servo");

  delay(1000);

}

/*
 * Move Servo
 */
int move_servo(int servo, int position) {
  unsigned char buff[6];

  unsigned int temp;
  byte pos_hi = 0;
  byte pos_low = 0;

  // Only 8 channels
  if ( servo < 0 || servo > 8 )
    return -1;

  // Positions for HS-422 should be 500-5500
  if ( position < 500 || position > 5500 )
    return -1;

  pos_hi = position >> 7;
  pos_low = position & 0x7f;

  buff[0] = 0x80;    //start byte
  buff[1] = 0x01;    //device id
  buff[2] = 0x04;    //command number
  buff[3] = servo;   //servo number
  buff[4] = pos_hi;  //high position
  buff[5] = pos_low; //low position

  for(int i = 0; i < 6; i++){
    softSerial.write(buff[i]);
  }

  return 0;
}
