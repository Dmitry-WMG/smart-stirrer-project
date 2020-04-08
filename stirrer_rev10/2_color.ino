void colorStart(uint8_t address_bit_high) {
  if (address_bit_high) {
    colorSensor.getAddr_BH1745NUC(BH1745NUC_ADDRESS_HIGH);       // 0x39, 0111001
  } else {
    colorSensor.getAddr_BH1745NUC(BH1745NUC_DEFAULT_ADDRESS);    // 0x38, 0111000  
  }
  colorSensor.setSWReset(SW_RESET_NOT_START);                  // Initial reset is not started
  // colorSensor.setSWReset(SW_RESET_START);                   // Initial reset is started
  colorSensor.setMeasTime(MEAS_TIME_160);                      // 000 : 160 msec
  colorSensor.setRGBCValid(RGBC_VALID_UPDATE);                 // RGBC data is updated after last writing MODE_CONTROL1,2 register or last reading MODE_CONTROL2 register
  // colorSensor.setRGBCValid(RGBC_VALID_NOT_UPDATE);          // RGBC data is not updated after last writing MODE_CONTROL1,2 register or last reading MODE_CONTROL2 register
  colorSensor.setRGBCEnable(RGBC_EN_ACTIVE);                   // RGBC measurement is active
  // colorSensor.setRGBCEnable(RGBC_EN_INACTIVE);              // RGBC measurement is inactive and becomes power down
  colorSensor.setADCGain(ADC_GAIN_16X);                        // 00 : 16X
  // colorSensor.setADCGain(ADC_GAIN_1X);                      // 00 : 1X
  colorSensor.setINTStatus(STATUS_ACTIVE);                     // Interrupt signal is inactive
  colorSensor.setINTLatch(INT_LATCH_LATCHED);                  // INTERRUPT pin is latched until INTERRUPT register is read or initialized
  colorSensor.setINTLatch(INT_LATCH_UPDATED);                  // INTERRUPT pin is latched until INTERRUPT register is read or initialized
  colorSensor.setINTEnable(INT_ENABLE_ENABLE);                 // INTERRUPT pin disable
  colorSensor.setPersistance(BH1745NUC_PERSISTENCE_UPDATED_8); // Interrupt status is updated if 4 consecutive threshold judgments are the same
  colorSensor.setINTSource(BH1745NUC_INTR_INT_SOURCE_CLEAR);   // Red channel is a source of interrupt
  colorSensor.setTHLimitHigh((CLEAR_INTERRUPT_VALUE & 0xFF00) >> 8);  // the first bit of the interrupt value
  colorSensor.setTHLimitLow((CLEAR_INTERRUPT_VALUE & 0xFF));          // the last bit of the interrupt value
  colorSensor.setTLLimitLow(0);                                // putting values of LOWER interrupt  
  colorSensor.setTLLimitHigh(0);
  colorSensor.Initialize();                                    // Initialize the sensor for the color measurements
  colorSensor.begin();
}


uint8_t updateColorData()  {
  // the sensor is updated one by one R -> G -> B -> C -> R etc
  unsigned long currentTime = millis();
  if (currentTime >= timerColor)  // timeout done
  {
    dataLed=  digitalRead(PIN_LIGHT_WHITE)*2 + digitalRead(PIN_LIGHT_UV);  
    dataRed=  colorSensor.getRedColor(); 
    dataGrn=  colorSensor.getGreenColor();
    dataBlu=  colorSensor.getBlueColor();
    dataClr=  colorSensor.getClearColor();
    timerColor=currentTime+COLOR_SENSOR_UPDATE_DELAY_MS;   // retry later

    uint8_t ledNext=generateLEDstate();
    if (ledNext>1) {
      digitalWrite(PIN_LIGHT_WHITE,   HIGH);
      digitalWrite(PIN_LIGHT_UV,      LOW);
    } else {
      if (ledNext) {
        digitalWrite(PIN_LIGHT_WHITE, LOW);
        digitalWrite(PIN_LIGHT_UV,    HIGH);
      } else {
        digitalWrite(PIN_LIGHT_UV,    LOW);
        digitalWrite(PIN_LIGHT_WHITE, LOW);
      }
    }
    return 1;
  } else {return 0;}
}

uint8_t generateLEDstate() {  // the function generates the UV/White/none LED status as desired
  internalLEDcounter=(internalLEDcounter+1) % 45;
  switch (internalLEDcounter) {
    case 15:
    case 16:
    case 17:
      return 1; // return UV LED
      break;
    case 30:
    case 31:
    case 32:
      return 2; // return WHITE LED
      break;
    default:
      return 0; // return no LED
      break;  
  } 
}

void checkReset() {     // the function resets the whole unit if required
  if (dataClr>=CLEAR_INTERRUPT_VALUE) {
    overloadCounter++;
    if (overloadCounter>RESET_THRESHOLD_COUNTER) {
      blinkBothLED(100);
      delay(500);
      blinkBothLED(100);
      hardReset();
    }
  } else {
    overloadCounter=0;
  }
}
