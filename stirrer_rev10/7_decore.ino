// the functions simply provide some basic decore
void blinkBothLED(uint16_t duration) {
  for (byte i=0;i<=10;i++) {
    digitalWrite(PIN_LIGHT_WHITE, HIGH);
    digitalWrite(PIN_LIGHT_UV,LOW);
    delay(duration);
    digitalWrite(PIN_LIGHT_WHITE, LOW);
    digitalWrite(PIN_LIGHT_UV, HIGH);
    delay(duration);
  }
  digitalWrite(PIN_LIGHT_WHITE, LOW);
  digitalWrite(PIN_LIGHT_UV, LOW);
}

void blinkWhiteTwice(uint16_t duration) {
  for (byte i=1;i<=2;i++) {
    digitalWrite(PIN_LIGHT_WHITE, HIGH);
    delay(duration);
    digitalWrite(PIN_LIGHT_WHITE, LOW);
    delay(duration);
  }
  digitalWrite(PIN_LIGHT_WHITE, LOW);
}

void blinkUVTwice(uint16_t duration) {
  for (byte i=1;i<=2;i++) {
    digitalWrite(PIN_LIGHT_UV,HIGH);
    delay(duration);
    digitalWrite(PIN_LIGHT_UV, LOW);
    delay(duration);
  }
  digitalWrite(PIN_LIGHT_UV, LOW);
}
