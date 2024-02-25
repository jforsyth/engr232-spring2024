// define the analog input pin to be used
const int ANALOG_PIN = A0;

void setup() {

  // turn on the Serial port to 9600 Baud
  Serial.begin(9600);

  // configure the analog pin as an input
  pinMode(ANALOG_PIN,INPUT);

}


void loop() 
{
  
  // Read from the input pin and print the value
  int value = analogRead(ANALOG_PIN);

  // Print out the value to the serial monitor
  Serial.print("Analog Reading is: "); Serial.println(value);

  // delay 200ms so the program doesn't spam the terminal
  delay(200);

}
