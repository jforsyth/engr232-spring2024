// set which pin will drive the pump
const int TRIGGER_PIN = 7;
void setup() {

  // set this pin as output
  pinMode(TRIGGER_PIN,OUTPUT);

}

void loop() 
{
  // turn on Pump for 2s
  digitalWrite(TRIGGER_PIN, HIGH);
  delay(2000);

  // let it rest for 10s
  digitalWrite(TRIGGER_PIN, LOW);
  delay(10000);

}
