/**
 * Define a variable for each pin
 */
const int LED1_PIN = 9;
const int LED2_PIN = 10;
const int LED3_PIN = 11;

void setup() 
{

  /**
   * Set each pin as an OUTPUT so it can drive
   * the LED
   */
  pinMode(LED1_PIN,OUTPUT);
  pinMode(LED2_PIN,OUTPUT);
  pinMode(LED3_PIN,OUTPUT);

}

void loop() 
{
  /**
   * Turn on each LED 
   */
  digitalWrite(LED1_PIN,HIGH);
  digitalWrite(LED2_PIN,HIGH);
  digitalWrite(LED3_PIN,HIGH);

  // wait 1s
  delay(1000);

  /**
   * Turn off each LED
   */
  digitalWrite(LED1_PIN,LOW);
  digitalWrite(LED2_PIN,LOW);
  digitalWrite(LED3_PIN,LOW);

  // wait 1s
  delay(1000);

}
