// forming and sending communications data

void commsPackage1() {  
// forming package 1 that contains
// accelerometer data - 12 byte for 3 axes, mean and standard deviation
// checksum CRC16
  uint16_t crc;
  message[ 0]=returnByte(dataAccelX.mean(),0);
  message[ 1]=returnByte(dataAccelX.mean(),1); 
  message[ 2]=returnByte(dataAccelY.mean(),0);
  message[ 3]=returnByte(dataAccelY.mean(),1);
  message[ 4]=returnByte(dataAccelZ.mean(),0);
  message[ 5]=returnByte(dataAccelZ.mean(),1);
  message[ 6]=returnByte(dataAccelX.stdDeviation(),0);
  message[ 7]=returnByte(dataAccelX.stdDeviation(),1);
  message[ 8]=returnByte(dataAccelY.stdDeviation(),0);
  message[ 9]=returnByte(dataAccelY.stdDeviation(),1);
  message[10]=returnByte(dataAccelZ.stdDeviation(),0);
  message[11]=returnByte(dataAccelZ.stdDeviation(),1);
  message[12]=NULL;
  crc=uCRC16Lib::calculate(message, 12);
  message[12]=returnByte(crc,0);
  message[13]=returnByte(crc,1);
  message[14]=TERMINATOR1 + 0;
  message[15]=TERMINATOR2;
}

void commsPackage2() {  
// forming package 2 that contains
// gyroscope data - 12 byte for 3 axes, mean and standard deviation
// checksum CRC16
  uint16_t crc;
  message[ 0]=returnByte(dataGyroX.mean(),0);
  message[ 1]=returnByte(dataGyroX.mean(),1);
  message[ 2]=returnByte(dataGyroY.mean(),0);
  message[ 3]=returnByte(dataGyroY.mean(),1);
  message[ 4]=returnByte(dataGyroZ.mean(),0);
  message[ 5]=returnByte(dataGyroZ.mean(),1);
  message[ 6]=returnByte(dataGyroX.stdDeviation(),0);
  message[ 7]=returnByte(dataGyroX.stdDeviation(),1);
  message[ 8]=returnByte(dataGyroY.stdDeviation(),0);
  message[ 9]=returnByte(dataGyroY.stdDeviation(),1);
  message[10]=returnByte(dataGyroZ.stdDeviation(),0);
  message[11]=returnByte(dataGyroZ.stdDeviation(),1);
  message[12]=NULL;
  crc=uCRC16Lib::calculate(message, 12);
  message[12]=returnByte(crc,0);
  message[13]=returnByte(crc,1);
  message[14]=TERMINATOR1 + 1;
  message[15]=TERMINATOR2;
}

void commsPackage3() {  
// forming package 3 that contains
// magnetometer data - 12 byte for 3 axes, mean and standard deviation
// checksum CRC16
  uint16_t crc;
  message[ 0]=returnByte(dataMagX.mean(),0);
  message[ 1]=returnByte(dataMagX.mean(),1); 
  message[ 2]=returnByte(dataMagY.mean(),0);
  message[ 3]=returnByte(dataMagY.mean(),1);
  message[ 4]=returnByte(dataMagZ.mean(),0);
  message[ 5]=returnByte(dataMagZ.mean(),1);
  message[ 6]=returnByte(dataMagX.stdDeviation(),0);
  message[ 7]=returnByte(dataMagX.stdDeviation(),1);
  message[ 8]=returnByte(dataMagY.stdDeviation(),0);
  message[ 9]=returnByte(dataMagY.stdDeviation(),1);
  message[10]=returnByte(dataMagZ.stdDeviation(),0);
  message[11]=returnByte(dataMagZ.stdDeviation(),1);
  message[12]=NULL;
  crc=uCRC16Lib::calculate(message, 12);
  message[12]=returnByte(crc,0);
  message[13]=returnByte(crc,1);
  message[14]=TERMINATOR1 + 2;
  message[15]=TERMINATOR2;
}

void commsPackage4() {  
// forming package 4 that contains
// color data plus LED status
// checksum CRC16
  uint16_t crc;
  message[ 0]=returnByte(dataRed,0);
  message[ 1]=returnByte(dataRed,1); 
  message[ 2]=returnByte(dataGrn,0);
  message[ 3]=returnByte(dataGrn,1);
  message[ 4]=returnByte(dataBlu,0);
  message[ 5]=returnByte(dataBlu,1);
  message[ 6]=returnByte(dataClr,0);
  message[ 7]=returnByte(dataClr,1);
  message[ 8]=returnByte(dataLed,0);
  message[ 9]=returnByte(dataLed,1);
  message[10]=0;
  message[11]=0;
  message[12]=NULL;
  crc=uCRC16Lib::calculate(message, 12);
  message[12]=returnByte(crc,0);
  message[13]=returnByte(crc,1);
  message[14]=TERMINATOR1 + 3;
  message[15]=TERMINATOR2;
}

void commsPackage5() {  
// forming package 5 that contains
// ADC data and the battery status
// checksum CRC16
  uint16_t crc;
  message[ 0]=returnByte(adcbatteryLevel,0);
  message[ 1]=returnByte(adcbatteryLevel,1); 
  message[ 2]=returnByte(adcConductivity,0);
  message[ 3]=returnByte(adcConductivity,1);
  message[ 4]=returnByte(adcTemperature,0);
  message[ 5]=returnByte(adcTemperature,1);
  message[ 6]=returnByte(gyroscope.ax,0);
  message[ 7]=returnByte(gyroscope.ax,1);
  message[ 8]=returnByte(gyroscope.ay,0);   
  message[ 9]=returnByte(gyroscope.ay,1);
  message[10]=returnByte(gyroscope.az,0);
  message[11]=returnByte(gyroscope.az,1);
  message[12]=NULL;
  crc=uCRC16Lib::calculate(message, 12);
  message[12]=returnByte(crc,0);
  message[13]=returnByte(crc,1);
  message[14]=TERMINATOR1 + 4;
  message[15]=TERMINATOR2;
}

char returnByte(uint16_t input, uint8_t place) {    // conversion of an int value into a given byte position
  if (place) {
    input=(input & 0x00FF) ;
  } else {
    input=(input & 0xFF00) >>8;
  }
  return input;
}
