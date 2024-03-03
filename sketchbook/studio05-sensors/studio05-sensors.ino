
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

} // of method setup()

// duration in milliseconds for how long the loop shoudl iterate
const int loop_delay = 1000;

// a counter to track the number of loop iterations
int loop_counter = 0;
void loop()
{

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
  
  ////////////////////// Get the Current Time //////////////////////
  long current_time = millis() / 1000;
 

  if (loop_counter % 5 == 0)
  {
    Serial.println("\nTime(s)\tTemp\tUV\tCO2");
  }

  Serial.print(current_time); Serial.print("\t");
  Serial.print(temperature); Serial.print("\t");
  Serial.print(uv_index); Serial.print("\t");
  Serial.println(CO2);


  delay(loop_delay);
  loop_counter++;
  
} // of method loop()
