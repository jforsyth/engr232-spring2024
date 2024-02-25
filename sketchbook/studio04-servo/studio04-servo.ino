#include <Servo.h>

// create servo object to control a servo
Servo myservo;  

// define which pin will be used
const int SERVO_PIN = 9;


void setup() {

  // set the serial port to 9600 baud
  Serial.begin(9600);

  // attach the servo object to the pin
  myservo.attach(SERVO_PIN); 

  // initialize the servo to 0 degrees
  myservo.write(0);
}

void loop() {

  // set the servo to 0 degrees
  myservo.write(0);

  // wait 1s
  delay(1000);

  // set the servo to 90 degrees
  myservo.write(90);

  // wait 1s
  delay(1000);

  // set the servo to 180 degrees
  myservo.write(180);

  // wait 1s
  delay(1000);

}
