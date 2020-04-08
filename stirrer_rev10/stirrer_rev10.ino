// declarations of the main variables
#include <Wire.h>

// pins and power
#define OSCCAL_BASE_FREQ                0xAC                  // the value must be determined for every microcontroller
#define INTERNAL_REFERENCE_MULTIPLIER   1  // the multiplier converts arduino ADC readings (1023 max) into uint16_t
                                            // the value is different for every microcontroller
#define PIN_AX3_RESET                   9   // pin that resets the whole Arduino                                            

#define PIN_I2C_POWER               A3                    // pin og the I2C power

// 1 gyroscope
#define NUMBER_POINTS_ACCELL_AVERAGE 24   // average this number of points in accelerometer
#define NUMBER_POINTS_MAGNET_AVERAGE 8    // average this number of points in magnetometer
#define EXPECTED_ACCEL_DELAY         4    // 1 ms before updating the accelerometer 
#define EXPECTED_MAGNE_DELAY         12   // 12 ms before updating the magnetometer
#define debugGYRO                    1    // debugging of accelerometer
#include <SparkFunLSM9DS1.h>  // gyroscope library
uint32_t  timerAccel=0;    // millis timer to read the accelerometer
uint32_t  timerMagnet=0;   // millis timer to read magnetometer
uint8_t   gyroCounter=0;   // counter since sending the data for accelerometer
uint8_t   magnetCounter=0; // counter since sending the data for magnetometer
LSM9DS1 gyroscope;
#include <UIntStatistics.h>   // library for signed int16_t statistics
UIntStatistics dataAccelX(NUMBER_POINTS_ACCELL_AVERAGE);
UIntStatistics dataAccelY(NUMBER_POINTS_ACCELL_AVERAGE);
UIntStatistics dataAccelZ(NUMBER_POINTS_ACCELL_AVERAGE);
UIntStatistics dataGyroX(NUMBER_POINTS_ACCELL_AVERAGE);
UIntStatistics dataGyroY(NUMBER_POINTS_ACCELL_AVERAGE);
UIntStatistics dataGyroZ(NUMBER_POINTS_ACCELL_AVERAGE);
UIntStatistics dataMagX(NUMBER_POINTS_MAGNET_AVERAGE);
UIntStatistics dataMagY(NUMBER_POINTS_MAGNET_AVERAGE);
UIntStatistics dataMagZ(NUMBER_POINTS_MAGNET_AVERAGE);

// 2 color
#define PIN_LIGHT_WHITE               A2    // pin of the LED light. A2 - white, A0 - UV
#define PIN_LIGHT_UV                  A0    // pin of the LED light. A2 - white, A0 - UV
#define COLOR_SENSOR_UPDATE_DELAY_MS  230   // expected update of the color sensor readings
#define CLEAR_INTERRUPT_VALUE         0xFFFE  // reading of the red channel to enable interrupt
#define RESET_THRESHOLD_COUNTER       16    // how many counts shall be exceeded to reset the module
#include <BH1745NUC.h>                      //color sensor
BH1745NUC colorSensor;                        
uint32_t  timerColor=0;                     // millis timer to read the color sensor
uint16_t  dataRed=0;                        // reading of the red color sensor
uint16_t  dataGrn=0;                        // reading of the green color sensor
uint16_t  dataBlu=0;                        // reading of the blue color sensor
uint16_t  dataClr=0;                        // reading of the clear color sensor
uint16_t  dataLed=0;                        // status of the LED during the last operation

uint8_t   overloadCounter=0;                // how many recent reading the clear color overloaded
uint8_t   internalLEDcounter=0;             // the variable is used to generate the desired LED state

// 3 ADC and battery
uint16_t adcbatteryLevel;                     // level of battery in 100*uV
int16_t adcConductivity;
int16_t adcTemperature;
#include "ADS1100.h"
#define ADC_ADRESS 0x48   
#define PIN_BATTERY               A1
#define PIN_ADC_IN                4         // PIN that powers on the thermistor and conductivity
#define PIN_MULTIPLEX_TEMP        3         // MULTIPLEX if HIGH TURN TO TEMP
#define MULTIPLEX_DELAY_MS        50        // delay before reading ADC after switching the multiplex in ms
#define ADC_READ_TIME_MS          125       // duration of a single ADC measurement
#define ADC_DELAY_TIME_MS         250       // delay to de-polarise the external electrodes
ADS1100 adc=ADS1100(ADC_ADRESS);
uint32_t  timerADC=0;                       // when to read the ADC
uint32_t  timerMultiplex=0; 
uint32_t  timerADCdelay=0;
uint8_t   adcConversionFlag=1;
uint8_t   adcCounter=0;          
uint8_t   internalADCcounter=0;             // the variable is used to generate the desired ADC state




//// 6 microcontroller and power
#include  "LowPower.h"
#define   WAKEUP_PIN                    2
uint8_t   sleepMode=1;                          // sleep mode active
uint32_t  wakeupTimer=0;                        // timer of the previous wakeup/sleep call
uint32_t  wakeupTimerDuration=0;  // duration of the wakeup condition fulfilled
#define   WAKEUP_THRESHOLD            60000L   // time between active calls to activate sleep of wakeup
#define   WAKEUP_OPERATION            3000    // how much time (ms) the pin to be active before enacting change
#define   THERMISTOR_CONSTANT_RES     10.0       // 110k is the constant resistor
#define   THERMISTOR_CALIBR_A         -4.07e-2   // value a in ln(R) = a*T+b. 
#define   THERMISTOR_CALIBR_B         5.716      // value a in ln(R) = a*T+b. 
uint32_t  temperatureUpdate=0;                  // timer when to update temperature
#define   TEMP_UPDATE_DELAY           30000     // how often to update the temperature in ms
float     currEstimatedTemperature=20.0;        // current temperature estimation required for OSCCAL shift         

// 9 communications
#define BT_POWER                      10    // pin of the BT power pin
#define BT_REBOOT_PERIOD              30000 // BT module will be turned off after this period
#define BT_OFF_PERIOD                 50    // period of time BT module is off
#include <uCRC16Lib.h>                      // CRC 16 library
#define MAXIMUM_MESSAGE_LENGTH    16        // maximum message length in byte
#define TERMINATOR1               0xFA      // first terminator character
#define TERMINATOR2               0x0D    // second terminator character
uint8_t message[MAXIMUM_MESSAGE_LENGTH];
uint32_t  bluetoothStarted=0;           // millis when bluetooth module was started

//debugging code
//#define DEBUG_COLOR 1
