void setup() {
  OSCCAL=OSCCAL_BASE_FREQ;
  pinMode(PIN_I2C_POWER,      OUTPUT);
  digitalWrite(PIN_I2C_POWER, HIGH);  // turn on the I2C power to SDA/SCL lines
  delay(20);
  colorStart(1);
  pinMode(WAKEUP_PIN,INPUT_PULLUP);
  digitalWrite(PIN_I2C_POWER, LOW);  // turn on the I2C power to SDA/SCL lines
  delay(10);
  attachInterrupt(digitalPinToInterrupt(WAKEUP_PIN), interruptAction, LOW);
  delay(10);
  pinMode(PIN_LIGHT_WHITE,OUTPUT);
  blinkWhiteTwice(100);
  
  while (sleepMode == 1) {
    LowPower.powerSave(SLEEP_8S, ADC_OFF, BOD_OFF , TIMER2_OFF);
    delay(1);
  }
  detachInterrupt(digitalPinToInterrupt(WAKEUP_PIN));
  startAll();
  colorStart(1);
  blinkUVTwice(100);
  gyroStart(1,1);
  blinkUVTwice(100);
  
  blinkBothLED(120);
  adcBegin();
  Serial.begin(19200);
  BT_restart_update();
  blinkBothLED(50);  
  Wire.setClock(60000L);  // it must be at the very end. Does not work otherwise
}


// LOOP FUNCTION
void loop() {
// wakeUpCheck();
//  
// if (sleepMode!=1) {
  if (gyroAccelCheck()) {
    gyroCounter++;
//    blinkUVTwice(5);
    if (gyroCounter>=NUMBER_POINTS_ACCELL_AVERAGE) {
      delayMicroseconds(100);
      commsPackage1();
      Serial.write(message,MAXIMUM_MESSAGE_LENGTH);  
      delayMicroseconds(100);
      commsPackage2();
      Serial.write(message,MAXIMUM_MESSAGE_LENGTH);  
      gyroCounter=0;
    }
  }
  
  if (gyroMagnetCheck()) {
    magnetCounter++;
    if (magnetCounter>=NUMBER_POINTS_MAGNET_AVERAGE){
      commsPackage3();
      Serial.write(message,MAXIMUM_MESSAGE_LENGTH);  
      magnetCounter=0;      
    }
  }

  if (updateColorData()) {
    commsPackage4();
    Serial.write(message,MAXIMUM_MESSAGE_LENGTH);
    checkReset();  
  }

  if (dataADCready()) {
    commsPackage5();
    Serial.write(message,MAXIMUM_MESSAGE_LENGTH);  
  }

  BT_restart_update();
  adjustOSSCALonTemp();

}


  
