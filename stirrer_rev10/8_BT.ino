// this works with the BT module restarting it once in a while to maintain stability
void BT_restart_update() {
  uint32_t currentMillis=millis();
  if (currentMillis>bluetoothStarted)  { // time to chenge its state?
    byte bt_state=digitalRead(BT_POWER);
    if (bt_state) { // is the BT power on ?
      digitalWrite(BT_POWER,LOW);
      bluetoothStarted=currentMillis+BT_OFF_PERIOD;
    } else {        // is the BT power off ?
      digitalWrite(BT_POWER,HIGH);
      bluetoothStarted=currentMillis+BT_REBOOT_PERIOD;
    }
  }
  
}
