// ADC setup
void adcBegin() {
  pinMode(PIN_MULTIPLEX_TEMP,OUTPUT);
  pinMode(PIN_ADC_IN,OUTPUT);
  analogReference(INTERNAL);
  adc.begin();
  adc.configure(ADS1100_CONVERSION_SINGLE,ADS1100_DATA_RATE_8SPS,ADS1100_GAIN_1X);
}

uint8_t dataADCready(void) {
  uint8_t temporaryAnswer=0;
  switch (adcCounter) {
    case 0: // read conductivity first to avoid polarisation
      if (adcReadValue(1)) {
        adcTemperature=adc.value;
        adcCounter++;
      }
      break;
    case 1: // read temperature
      if (adcReadValue(0)) {
        adcConductivity=adc.value;
        adcCounter++;
        timerADCdelay=millis()+ADC_DELAY_TIME_MS;
      }
      break;
    case 2: // just a delay in ADC to de-polarise electrodes
      if (millis()>timerADCdelay) {
        adcCounter++;
      }
    break;
    default: // read internal battery
      readBatteryLevel();
      adcCounter=0;
      temporaryAnswer=1;
      break;
  }
  return (temporaryAnswer);
}

// battery level reading
void readBatteryLevel() {
  adcbatteryLevel=((uint16_t) analogRead(PIN_BATTERY))*INTERNAL_REFERENCE_MULTIPLIER;
}

// ADS1100 and multiplex

uint8_t adcReadValue(uint8_t multiplexState) { // switch the multiplex to the correct position
  if (adcConversionFlag) {  // is it the first time ADC is read
    digitalWrite(PIN_MULTIPLEX_TEMP,multiplexState); 
    digitalWrite(PIN_ADC_IN,HIGH);    // powering up the sensors
    adcConversionFlag=0;
    adc.startSingleConversion();
    timerADC=millis()+ADC_READ_TIME_MS;
  } 
  else {
   if (adcReadingCompleted())
      {
        digitalWrite(PIN_ADC_IN,LOW); // power down the sensor
        adcConversionFlag=1;
        return 1;  
      } 
  }
return 0;
}

uint8_t adcGenerate() {
  internalADCcounter=(internalADCcounter+1) % 2;
}

uint8_t adcReadingCompleted() {
  if (millis()>timerADC) {
    if (adc.conversionDone()) {
      return 1;
    }
  }
  return 0;
}


//
//uint8_t multiplexReady(uint8_t multiplexState)  { //checks if the multiplex delay elapsed
//  if (digitalRead(PIN_MULTIPLEX_TEMP)==multiplexState)  {
//    if (millis()>timerMultiplex)  {
//      return 1;
//    } else {
//      return 0; 
//    }
//  } else {  // time to change the position and start waiting
//    timerMultiplex=millis()+MULTIPLEX_DELAY_MS; // next timer to consider position changed
//    digitalWrite(PIN_MULTIPLEX_TEMP,multiplexState); 
////    Serial.print("multiplex= ");
////    Serial.println(   multiplexState);
//  }
//}
