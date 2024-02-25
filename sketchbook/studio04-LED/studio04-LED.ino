// define the pin to control the LED
const int LED_PIN = 11;

void setup() {

  // set the serial port to 9600 baud
  Serial.begin(9600);

  // set the LED_PIN to an output
  pinMode(LED_PIN,OUTPUT);

}

void loop() 
{
  // turn on the LED_PIN
  digitalWrite(LED_PIN, HIGH);

  // wait 1s
  delay(1000);

  // turn off the LED_PIN
  digitalWrite(LED_PIN, LOW);

  // wait 1s
  delay(1000);

}
