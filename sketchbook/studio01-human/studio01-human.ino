#include "Zanshin_BME680.h" // Include the BME680 Sensor library
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

  Serial.println("Time(s)\tTemp\tHumidity\tPressure\t\tUV");

} // of method setup()

const int loop_delay = 1000;
int loop_counter = 0;
void loop()
{

  ////////////////////// Get Data from the BME Board //////////////////////
  float humidity = bmeSensor.readFloatHumidity();
  float pressure = bmeSensor.readFloatPressure();
  float altitude = bmeSensor.readFloatAltitudeFeet();
  float temp = bmeSensor.readTempC();

  long current_time = millis() / 1000;
  Serial.print(current_time); Serial.print("\t");
  Serial.print((float)temp); Serial.print("\t");
  Serial.print((float)humidity); Serial.print("\t\t");
  Serial.print((float)pressure); Serial.print("\t\t");
  Serial.println(uv.index());

  if (loop_counter % 5 == 0)
  {
    Serial.println("\nTime(s)\tTemp\tHumidity\tPressure\t\tUV");
  }


  delay(loop_delay);
  loop_counter++;
  // Wait 1s before repeating*/
} // of method loop()
