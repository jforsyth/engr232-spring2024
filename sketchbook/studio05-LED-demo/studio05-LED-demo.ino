

void setup() 
{

  /**
   * Set each pin as an OUTPUT so it can drive
   * the LED
   */
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);

}

void loop() 
{
  /**
   * Turn on each LED 
   */
  digitalWrite(9,HIGH);
  digitalWrite(10,HIGH);
  digitalWrite(11,HIGH);

  // wait 1s
  delay(1000);

  /**
   * Turn off each LED
   */
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);

  // wait 1s
  delay(1000);

}
