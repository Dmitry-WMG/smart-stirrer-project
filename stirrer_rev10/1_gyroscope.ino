void gyroStart(byte gyro_address_bit_high,byte magnet_address_bit_high) {
    gyroscope.settings.device.commInterface = IMU_MODE_I2C;
    // [mAddress] sets the I2C address or SPI CS pin of the
    // LSM9DS1's magnetometer.
    if (magnet_address_bit_high) {
      gyroscope.settings.device.mAddress = 0x1E;         // Use I2C addres 0x1E
    } else { gyroscope.settings.device.mAddress = 0x1C; }  // Use I2C addres 0x1E 
    if (gyro_address_bit_high) { //0x6B if high, would be 0x6A if SDO_AG is LOW
      gyroscope.settings.device.agAddress =0x6B;
    } else {gyroscope.settings.device.agAddress =0x6A;}

    // Setting up gyroscope
    // [enabled] turns the gyro on or off.
    gyroscope.settings.gyro.enabled = true;  // Enable the gyro
    // [scale] sets the full-scale range of the gyroscope.
    // scale can be set to either 245, 500, or 2000
    gyroscope.settings.gyro.scale = 2000; // Set scale to +/-245dps
    // [sampleRate] sets the output data rate (ODR) of the gyro
    // sampleRate can be set between 1-6
    // 1 = 14.9    4 = 238
    // 2 = 59.5    5 = 476
    // 3 = 119     6 = 952
    gyroscope.settings.gyro.sampleRate = 4; // 59.5Hz ODR
    // [bandwidth] can set the cutoff frequency of the gyro.
    // Allowed values: 0-3. Actual value of cutoff frequency
    // depends on the sample rate. (Datasheet section 7.12)
    gyroscope.settings.gyro.bandwidth = 0;
    // [lowPowerEnable] turns low-power mode on or off.
    gyroscope.settings.gyro.lowPowerEnable = false; // LP mode off
    // [HPFEnable] enables or disables the high-pass filter
    gyroscope.settings.gyro.HPFEnable = true; // HPF disabled
    // [HPFCutoff] sets the HPF cutoff frequency (if enabled)
    // Allowable values are 0-9. Value depends on ODR.
    // (Datasheet section 7.14)
    gyroscope.settings.gyro.HPFCutoff = 1; // HPF cutoff = 4Hz
    // [flipX], [flipY], and [flipZ] are booleans that can
    // automatically switch the positive/negative orientation
    // of the three gyro axes.
    gyroscope.settings.gyro.flipX = false; // Don't flip X
    gyroscope.settings.gyro.flipY = false; // Don't flip Y
    gyroscope.settings.gyro.flipZ = false; // Don't flip Z

    // setting the accelerometer 
    // [enabled] turns the acclerometer on or off.
    gyroscope.settings.accel.enabled = true; // Enable accelerometer
    // [enableX], [enableY], and [enableZ] can turn on or off
    // select axes of the acclerometer.
    gyroscope.settings.accel.enableX = true; // Enable X
    gyroscope.settings.accel.enableY = true; // Enable Y
    gyroscope.settings.accel.enableZ = true; // Enable Z
    // [scale] sets the full-scale range of the accelerometer.
    // accel scale can be 2, 4, 8, or 16
    gyroscope.settings.accel.scale = 16; // Set accel scale to +/-8g.
    // [sampleRate] sets the output data rate (ODR) of the
    // accelerometer. ONLY APPLICABLE WHEN THE GYROSCOPE IS
    // DISABLED! Otherwise accel sample rate = gyro sample rate.
    // accel sample rate can be 1-6
    // 1 = 10 Hz    4 = 238 Hz
    // 2 = 50 Hz    5 = 476 Hz
    // 3 = 119 Hz   6 = 952 Hz
    gyroscope.settings.accel.sampleRate = 4; // Set accel to 10Hz.
    // [bandwidth] sets the anti-aliasing filter bandwidth.
    // Accel cutoff freqeuncy can be any value between -1 - 3. 
    // -1 = bandwidth determined by sample rate
    // 0 = 408 Hz   2 = 105 Hz
    // 1 = 211 Hz   3 = 50 Hz
    gyroscope.settings.accel.bandwidth = 0; // BW = 408Hz
    // [highResEnable] enables or disables high resolution 
    // mode for the acclerometer.
    gyroscope.settings.accel.highResEnable = false; // Disable HR
    // [highResBandwidth] sets the LP cutoff frequency of
    // the accelerometer if it's in high-res mode.
    // can be any value between 0-3
    // LP cutoff is set to a factor of sample rate
    // 0 = ODR/50    2 = ODR/9
    // 1 = ODR/100   3 = ODR/400
    gyroscope.settings.accel.highResBandwidth = 0; 

    // setting the magnetometer
    // [enabled] turns the magnetometer on or off.
    gyroscope.settings.mag.enabled = true; // Enable magnetometer
    // [scale] sets the full-scale range of the magnetometer
    // mag scale can be 4, 8, 12, or 16
    gyroscope.settings.mag.scale = 16; // Set mag scale to +/-12 Gs
    // [sampleRate] sets the output data rate (ODR) of the
    // magnetometer.
    // mag data rate can be 0-7:
    // 0 = 0.625 Hz  4 = 10 Hz
    // 1 = 1.25 Hz   5 = 20 Hz
    // 2 = 2.5 Hz    6 = 40 Hz
    // 3 = 5 Hz      7 = 80 Hz
    gyroscope.settings.mag.sampleRate = 7; // Set OD rate to 20Hz
    // [tempCompensationEnable] enables or disables 
    // temperature compensation of the magnetometer.
    gyroscope.settings.mag.tempCompensationEnable = false;
    // [XYPerformance] sets the x and y-axis performance of the
    // magnetometer to either:
    // 0 = Low power mode      2 = high performance
    // 1 = medium performance  3 = ultra-high performance
    gyroscope.settings.mag.XYPerformance = 3; // Ultra-high perform.
    // [ZPerformance] does the same thing, but only for the z
    gyroscope.settings.mag.ZPerformance = 3; // Ultra-high perform.
    // [lowPowerEnable] enables or disables low power mode in
    // the magnetometer.
    gyroscope.settings.mag.lowPowerEnable = false;
    // [operatingMode] sets the operating mode of the
    // magnetometer. operatingMode can be 0-2:
    // 0 = continuous conversion
    // 1 = single-conversion
    // 2 = power down
    gyroscope.settings.mag.operatingMode = 0; // Continuous mode
    gyroscope.begin();
  
  gyroCounter=0;
  magnetCounter=0;
}
  
void gyroStop() {
  gyroscope.settings.gyro.enabled = false;  
  gyroscope.settings.accel.enabled = false; 
  gyroscope.settings.mag.enabled = false; 
}

byte gyroAccelCheck() {
  uint32_t timer=millis();
  if (timer>=timerAccel) {
    if ( gyroscope.accelAvailable() ) {
      gyroscope.readAccel();  // assume the same data rate, hence both are avaliable  
      dataAccelX.addData(gyroscope.ax);
      dataAccelY.addData(gyroscope.ay);
      dataAccelZ.addData(gyroscope.az);
      gyroscope.readGyro();
      dataGyroX.addData(gyroscope.gx);
      dataGyroY.addData(gyroscope.gy);
      dataGyroZ.addData(gyroscope.gz);
      timerAccel=timer+EXPECTED_ACCEL_DELAY;
      return 1;
    } else {return 0;}
  } else {return 0;}
}

byte gyroMagnetCheck() {
  uint32_t timer=millis();
  if (timer>=timerMagnet) {
    if ( gyroscope.magAvailable() )   {
      gyroscope.readMag();
      dataMagX.addData(gyroscope.mx);
      dataMagY.addData(gyroscope.my);
      dataMagZ.addData(gyroscope.mz);
      timerMagnet=timerMagnet+EXPECTED_MAGNE_DELAY;
      return 1;
    } else {return 0;}
  } else {return 0;}
}  
