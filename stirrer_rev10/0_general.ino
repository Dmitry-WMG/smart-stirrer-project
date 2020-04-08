// general startup procedure
void startAll() {
  pinMode(WAKEUP_PIN,INPUT_PULLUP);
  pinMode(PIN_LIGHT_WHITE,OUTPUT);
  pinMode(PIN_LIGHT_UV,OUTPUT);
  pinMode(BT_POWER,OUTPUT);
  digitalWrite(PIN_LIGHT_WHITE, LOW);
  digitalWrite(PIN_LIGHT_UV,LOW);
  pinMode(PIN_MULTIPLEX_TEMP,OUTPUT);
  pinMode(PIN_ADC_IN,OUTPUT);
  digitalWrite(PIN_ADC_IN,LOW);
  pinMode(PIN_I2C_POWER,      OUTPUT);
  digitalWrite(PIN_I2C_POWER, HIGH);  // turn on the I2C power to SDA/SCL lines
  pinMode(PIN_MULTIPLEX_TEMP, OUTPUT);
//  LowPower.idle(SLEEP_8S, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, 
//                SPI_OFF, USART0_OFF, TWI_OFF);
}

void powerConservation () {
  digitalWrite(PIN_I2C_POWER, LOW);  // turn off the I2C power to SDA/SCL lines
  digitalWrite(PIN_LIGHT_WHITE, LOW);
  digitalWrite(PIN_LIGHT_UV,LOW);
  digitalWrite(PIN_MULTIPLEX_TEMP,LOW);
  digitalWrite(PIN_ADC_IN,LOW);
  digitalWrite(BT_POWER,LOW);
  
//  LowPower.powerSave(SLEEP_8S, ADC_OFF, BOD_OFF , TIMER2_OFF);
}

void powerActivation() {
  
}

void hardReset() {
  pinMode(PIN_AX3_RESET,OUTPUT);
  digitalWrite(PIN_AX3_RESET,LOW);  
}
