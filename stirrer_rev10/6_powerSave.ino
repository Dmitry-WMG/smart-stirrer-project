// this is run initially to conserve power
void wakeUpCheck() {
  if (wakeUpConditionCheck() > WAKEUP_OPERATION) {
    //change state?
    wakeupTimer = millis(); // resetting the timer
    dataClr=0;  // reset timer!
    if (~sleepMode) { 
      // put into sleep
      
      // set all pins to low
      powerConservation();
      sleepMode=1;
      //delay is vital to reset the interrupt
      blinkBothLED(150);
      delay(1000);
      blinkWhiteTwice(300);
      attachInterrupt(digitalPinToInterrupt(WAKEUP_PIN), interruptAction, LOW);
    }
  } else {
    if (sleepMode) {
      // continue sleeping
//      Serial.println("Sleep mode");
      LowPower.powerSave(SLEEP_8S, ADC_OFF, BOD_OFF , TIMER2_OFF);
    }
  }
}

uint16_t wakeUpConditionCheck() {
  if (sleepMode==1) { return 0;}
  if (dataClr>= CLEAR_INTERRUPT_VALUE) { // checking the condition
    // condition fulfilled
//    Serial.print("wake up condition ");
//    Serial.println(millis() - wakeupTimer);
    return (millis() - wakeupTimer); // duration of the conditon fulfilled
  } else {
    // condition was not fulfilled
    wakeupTimer = millis(); // resetting the timer
    return 0;
  }
return 0;
}

void interruptAction()
{
    // Just a handler for the pin interrupt.
    detachInterrupt(digitalPinToInterrupt(WAKEUP_PIN));
    sleepMode=0;
//    startAll();
}

void adjustOSSCALonTemp() {
  if (millis()>temperatureUpdate) {
    temperatureUpdate=millis()+TEMP_UPDATE_DELAY;
    currEstimatedTemperature=(log(THERMISTOR_CONSTANT_RES*32767.0/adcTemperature-1.0)-THERMISTOR_CALIBR_B)/THERMISTOR_CALIBR_A;
    OSCCAL=OSCCAL_BASE_FREQ-round((currEstimatedTemperature-20.0)/12.0);
  }
}
