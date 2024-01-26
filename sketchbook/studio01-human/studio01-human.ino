#include "Zanshin_BME680.h" // Include the BME680 Sensor library
/*******************************************************************************************************************
** Declare all program constants                                                                                  **
*******************************************************************************************************************/
const uint32_t SERIAL_SPEED = 9600; ///< Set the baud rate for Serial I/O

/*******************************************************************************************************************
** Declare global variables and instantiate classes                                                               **
*******************************************************************************************************************/
BME680_Class BME680; ///< Create an instance of the BME680 class

// Include the SparkFun VEML6075 library.
// Click here to get the library: http://librarymanager/All#SparkFun_VEML6075
#include <SparkFun_VEML6075_Arduino_Library.h>

VEML6075 uv; // Create a VEML6075 object

float altitude(const int32_t press, const float seaLevel = 1013.25); ///< Forward function declaration with default value for sea level
float altitude(const int32_t press, const float seaLevel)
{
  /*!
    @brief     This converts a pressure measurement into a height in meters
    @details   The corrected sea-level pressure can be passed into the function if it is know, otherwise the standard
               atmospheric pressure of 1013.25hPa is used (see https://en.wikipedia.org/wiki/Atmospheric_pressure)
    @param[in] press    Pressure reading from BME680
    @param[in] seaLevel Sea-Level pressure in millibars
    @return    floating point altitude in meters.
  */
  static float Altitude;
  Altitude = 44330.0 * (1.0 - pow(((float)press / 100.0) / seaLevel, 0.1903)); // Convert into altitude in meters
  return (Altitude);
} // of method altitude()

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
  //Serial.print(F("Starting I2CDemo example program for BME680\n"));
  //Serial.print(F("- Initializing BME680 sensor\n"));
  while (!BME680.begin(I2C_STANDARD_MODE)) // Start BME680 using I2C protocol
  {
    Serial.print(F("Unable to communicate with Environmental Sensor. Check Connection.\n"));
    delay(1000);
  } // of loop until device is located
  //Serial.print(F("- Setting 16x oversampling for all sensors\n"));
  BME680.setOversampling(TemperatureSensor, Oversample16); // Use enumerated type values
  BME680.setOversampling(HumiditySensor,   Oversample16); // Use enumerated type values
  BME680.setOversampling(PressureSensor,   Oversample16); // Use enumerated type values
  //Serial.print(F("- Setting IIR filter to a value of 4 samples\n"));
  BME680.setIIRFilter(IIR4); // Use enumerated type values
  //Serial.print(F("- Setting gas measurement to 320\xC2\xB0\x43 for 150ms\n")); // "�C" symbols
  BME680.setGas(320, 150); // 320�c for 150 milliseconds

  if (uv.begin() == false)
  {
    
    while (1)
    {
      Serial.println("Unable to communicate with UV sensor. Check connection.");
      delay(1000);  
    }
  }
  
} // of method setup()

const int loop_delay=1000;

void loop()
{
  /*!
    @brief    Arduino method for the main program loop
    @details  This is the main program for the Arduino IDE, it is an infinite loop and keeps on repeating.
            The "sprintf()" function is to pretty-print the values, since floating point is not supported on the
            Arduino, split the values into those before and those after the decimal point.
    @return   void
  */
  static int32_t  temp, humidity, pressure, gas;                                    // Variable to store readings
  static char     buf[16];                                                          // Text buffer for sprintf
  static float    alt;                                                              // temp variable for altitude
  static uint16_t loopCounter = 0;                                                  // Display iterations
  if (loopCounter % 10 == 0)                                                        // Display header every 25 loops
  { //
    Serial.print(F("\nTime (s)\tTemp\xC2\xB0\x43\tHumid%\tPress(hPa)\tUV_Index\n"));      // Show header plus unicode "�C"
    Serial.print(F("====\t======\t======\t=========\t=======\n")); // and "?" symbols
  } // if-then time to show headers                                                 //
  BME680.getSensorData(temp, humidity, pressure, gas);                              // Get the most recent readings
  alt = altitude(pressure); 

  long current_time = millis() / 1000;
  Serial.print(current_time); Serial.print("\t");
  Serial.print((float)temp/100.0); Serial.print("\t");
  Serial.print((float)humidity/1000.0); Serial.print("\t");
  Serial.print((float)pressure/100.0); Serial.print("\t\t");
  Serial.println(uv.index());
  
  //Serial.println(alt);
  //Serial.println((float)gas/100.0);

  loopCounter++;
  delay(loop_delay);
  /*
  sprintf(buf, "%4d %3d.%02d", ++loopCounter % 9999,                                // Clamp iterations to 9999,
          (int8_t)(temp / 100), (uint8_t)(temp % 100));                             // Temperature in decidegrees
  Serial.print(buf);                                                                //
  sprintf(buf, "%3d.%03d", (int8_t)(humidity / 1000), (uint16_t)(humidity % 1000)); // Humidity in milli-percent
  Serial.print(buf);                                                                //
  sprintf(buf, "%7d.%02d", (int16_t)(pressure / 100), (uint8_t)(pressure % 100));   // Pressure in Pascals
  Serial.print(buf);                                                                //
  alt = altitude(pressure);                                                         // temp variable for altitude
  sprintf(buf, "%5d.%02d", (int16_t)(alt), ((uint8_t)(alt * 100) % 100));           // Altitude in meters
  Serial.print(buf);                                                                //
  sprintf(buf, "%4d.%02d\n", (int16_t)(gas / 100), (uint8_t)(gas % 100));           // Resistance in milliohms
  Serial.print(buf);                                                                //
  delay(1000);                                                                     // Wait 1s before repeating*/
} // of method loop()
