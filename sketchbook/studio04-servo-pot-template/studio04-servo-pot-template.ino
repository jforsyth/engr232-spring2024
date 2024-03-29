#include <Servo.h>

// create servo object to control a servo
Servo myservo;

// define which pin will be used
const int SERVO_PIN = 9;

// define the analog input pin to be used
const int ANALOG_PIN = A0;

// define the pin to control the LED
const int LED_PIN = 11;

void setup()
{
  // set the serial port to 9600 baud
  Serial.begin(9600);

  // attach the servo object to the pin
  myservo.attach(SERVO_PIN);

  // set the LED_PIN to an output
  pinMode(LED_PIN, OUTPUT);

}

void loop()
{
  // Step 1: Read from the input pin and print the value
  int analog_value = // your code here

  
  //Step 2: Map the potentiometer value to a "servo" value
  int mapped = // your code here

  // Print out the conversion...
  Serial.print("Analog Value: "); Serial.print(analog_value);
  Serial.print("Servo Value: "); Serial.println(mapped);

  // Step 3: write the new "mapped" value to the servo
  // your code here

  // Step 4: read the servo position
  //int servo_pos= // your code here

  // Step 5: use an IF-ELSE statement to turn on the LED when the servo
  // is at its maximum limit of either 0 or 180 degrees. Otherwise, turn it OFF.

  // your code here
  
}
