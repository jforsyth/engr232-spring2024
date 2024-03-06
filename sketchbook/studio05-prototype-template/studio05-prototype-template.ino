
/*******************************************************************************************************************
** Declare all program constants                                                                                  **
*******************************************************************************************************************/
const uint32_t SERIAL_SPEED = 9600; ///< Set the baud rate for Serial I/O

/*******************************************************************************************************************
** Declare global variables and instantiate classes                                                               **
*******************************************************************************************************************/
//include the libraries for the BME (humdity, pressure, altitude, and temperature)
//and the CCS (CO2 and TVOC) sensors
#include "SparkFunCCS811.h"
#include "SparkFunBME280.h"

//define the default I2C address of the CCS. Is not needed for BME
//as is already in library
#define CCS811_ADDR 0x5B //Default I2C Address

//create handles to the two sensors
BME280 bmeSensor;
CCS811 ccsSensor(CCS811_ADDR);

// Include the SparkFun VEML6075 library.
// Click here to get the library: http://librarymanager/All#SparkFun_VEML6075
#include <SparkFun_VEML6075_Arduino_Library.h>

VEML6075 uv; // Create a VEML6075 object

/**
 * Define a variable for each pin
 */
const int LED1_PIN = 9;
const int LED2_PIN = 10;
const int LED3_PIN = 11;

void setup()
{
  /*!
    @brief    Arduino method called once at startup to initialize the system
    @details  This is an Arduino IDE method which is called first upon boot or restart. It is only called one time
            and then control goes to the main "loop()" method, from which control never returns
    @return   void
  */
  Serial.begin(SERIAL_SPEED); // Start serial port at Baud rate
#ifdef  __AVR_ATmega32U4__  // If this is a 32U4 processor, then wait 3 seconds to initialize USB port
  delay(3000);
#endif

  if (bmeSensor.beginI2C() == false) //Begin communication over I2C
  {
    Serial.println("Could not access the BME sensor. Please check wiring.");
    while (1); //Freeze
  }


  CCS811Core::status returnCode = ccsSensor.begin();
  if (returnCode != CCS811Core::SENSOR_SUCCESS)
  {
    Serial.println("Could not access the CCS sensor. Please check wiring.");
    while (1); //Hang if there was a problem.
  }


  if (uv.begin() == false)
  {

    while (1)
    {
      Serial.println("Unable to communicate with UV sensor. Check connection.");
      delay(1000);
    }
  }

  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);
} // of method setup()

// duration in milliseconds for how long the loop shoudl iterate
const int loop_delay = 1000;

// a counter to track the number of loop iterations
int loop_counter = 0;
void loop()
{


  /**
     Inputs: Each of the inputs identified in the black box model are stored in the following variables:
     temperature: the temperature measured by the SparkFun sensor. Represented as a floating point value in Celsius.
     uv_index: the UltraViolet index measured by the sensor. Represented as a float point value. No units.
     CO2: the carbon dioxide concentration measured by the sensor. Represented as an integer in "equivalent" CO2 parts per million.
  */

  ////////////////////// Get Data from the BME Board //////////////////////
  float temperature = bmeSensor.readTempC();
  float uv_index = uv.index();

  ////////////////////// Get Data from the CCS Board //////////////////////
  int CO2 = -1;
  //check to see if CCS sensor is ready
  if (ccsSensor.dataAvailable())
  {
    //If so, have the sensor read and calculate the results.
    ccsSensor.readAlgorithmResults();

    //request data from the sensor
    CO2 = ccsSensor.getCO2();
  }

  /**
   * Filtering: This would be the next step in our process, however, we are not exploring filtering in this studio :)
   */


  /**
   * State,  Logic, and Command: After acquiring the data, the computer system should make some decisions and then execute some commands.
   * Before making some decisions, the system should establish the warning thresholds first.
   */

  // Create threshold value for each sensor. Replace -1 in each line with the value that was identified as "unsafe".
  float temperature_threshold = -1;
  float uv_index_threshold = -1;
  int co2_threshold = -1;

  // For a single sensor, test whether the current value has exceeded the threshold.
  // If so, turn on the LED. If not, then turn off the LED.
  // An example of an IF-ELSE statement is provided below that turns on the LED connected to pin 9. This should be
  // adapted for the sensor value of interest.
  int dummy_sensor_reading = 10;

  if(dummy_sensor_reading > 20)
  {
    digitalWrite(9,HIGH);
  }
  else
  {
    digitalWrite(9,LOW);
  }

  /**
   * The pattern above should be repeated for all INPUTS and OUTPUTs
   */


} // of method loop()
