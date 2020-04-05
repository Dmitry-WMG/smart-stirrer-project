#ifndef LSM9DS1_IMU_H
#define LSM9DS1_IMU_H

// LSM9DS1 Addresses
#define LSM9DS1_AG_ADDR(sa0) ((sa0) == 0 ? 0x6A : 0x6B)
// #define LSM9DS1_M_ADDR(sa1)	((sa1) == 0 ? 0x1C : 0x1E)

// LSM9DS1 Accel/Gyro (XL/G) Registers
#define ACT_THS 0x04
#define ACT_DUR	0x05
#define INT_GEN_CFG_XL 0x06
#define INT_GEN_THS_X_XL 0x07
#define INT_GEN_THS_Y_XL 0x08
#define INT_GEN_THS_Z_XL 0x09
#define INT_GEN_DUR_XL 0x0A
#define REFERENCE_G 0x0B
#define INT1_CTRL 0x0C
#define INT2_CTRL 0x0D
#define WHO_AM_I_XG 0x0F
#define CTRL_REG1_G 0x10
#define CTRL_REG2_G	0x11
#define CTRL_REG3_G	0x12
#define ORIENT_CFG_G 0x13
#define INT_GEN_SRC_G 0x14
#define OUT_TEMP_L 0x15
#define OUT_TEMP_H 0x16
#define STATUS_REG_0 0x17
#define OUT_X_L_G 0x18
#define OUT_X_H_G 0x19
#define OUT_Y_L_G 0x1A
#define OUT_Y_H_G 0x1B
#define OUT_Z_L_G 0x1C
#define OUT_Z_H_G 0x1D
#define CTRL_REG4 0x1E
#define CTRL_REG5_XL 0x1F
#define CTRL_REG6_XL 0x20
#define CTRL_REG7_XL 0x21
#define CTRL_REG8 0x22
#define CTRL_REG9 0x23
#define CTRL_REG10 0x24
#define INT_GEN_SRC_XL 0x26
#define STATUS_REG_1 0x27
#define OUT_X_L_XL 0x28
#define OUT_X_H_XL 0x29
#define OUT_Y_L_XL 0x2A
#define OUT_Y_H_XL 0x2B
#define OUT_Z_L_XL 0x2C
#define OUT_Z_H_XL 0x2D
#define FIFO_CTRL 0x2E
#define FIFO_SRC 0x2F
#define INT_GEN_CFG_G 0x30
#define INT_GEN_THS_XH_G 0x31
#define INT_GEN_THS_XL_G 0x32
#define INT_GEN_THS_YH_G 0x33
#define INT_GEN_THS_YL_G 0x34
#define INT_GEN_THS_ZH_G 0x35
#define INT_GEN_THS_ZL_G 0x36
#define INT_GEN_DUR_G 0x37

// LSM9DS1 Magneto Registers 
#define OFFSET_X_REG_L_M 0x05
#define OFFSET_X_REG_H_M 0x06
#define OFFSET_Y_REG_L_M 0x07
#define OFFSET_Y_REG_H_M 0x08
#define OFFSET_Z_REG_L_M 0x09
#define OFFSET_Z_REG_H_M 0x0A
#define WHO_AM_I_M 0x0F
#define CTRL_REG1_M 0x20
#define CTRL_REG2_M 0x21
#define CTRL_REG3_M 0x22
#define CTRL_REG4_M 0x23
#define CTRL_REG5_M 0x24
#define STATUS_REG_M 0x27
#define OUT_X_L_M 0x28
#define OUT_X_H_M 0x29
#define OUT_Y_L_M 0x2A
#define OUT_Y_H_M 0x2B
#define OUT_Z_L_M 0x2C
#define OUT_Z_H_M 0x2D
#define INT_CFG_M 0x30
#define INT_SRC_M 0x31
#define INT_THS_L_M 0x32
#define INT_THS_H_M 0x33

// LSM9DS1 WHO_AM_I Responses
#define WHO_AM_I_AG_RSP	0x68
// #define WHO_AM_I_M_RSP 0x3D

// Sensor Sensitivity Constants
// Values set according to the typical specifications provided in
// table 3 of the LSM9DS1 datasheet. (pg 12)
#define SENSITIVITY_ACCELEROMETER_2   0.000061
#define SENSITIVITY_ACCELEROMETER_4   0.000122
#define SENSITIVITY_ACCELEROMETER_8   0.000244
#define SENSITIVITY_ACCELEROMETER_16  0.000732
#define SENSITIVITY_GYROSCOPE_245     0.00875
#define SENSITIVITY_GYROSCOPE_500     0.0175
#define SENSITIVITY_GYROSCOPE_2000    0.07
// #define SENSITIVITY_MAGNETOMETER_4    0.00014
// #define SENSITIVITY_MAGNETOMETER_8    0.00029
// #define SENSITIVITY_MAGNETOMETER_12   0.00043
// #define SENSITIVITY_MAGNETOMETER_16   0.00058

// Type Declarations
typedef enum { A_SCALE_2G, A_SCALE_16G, A_SCALE_4G, A_SCALE_8G } accel_scale_t;
typedef enum { G_SCALE_245DPS, G_SCALE_500DPS, G_SCALE_2000DPS } gyro_scale_t;
// typedef enum { M_SCALE_4GS, M_SCALE_8GS, M_SCALE_12GS, M_SCALE_16GS } mag_scale_t;
typedef enum { 
    G_ODR_PD, G_ODR_149, G_ODR_595, G_ODR_119, G_ODR_238, G_ODR_476, G_ODR_952 } gyro_odr_t;
typedef enum { XL_POWER_DOWN, XL_ODR_10, XL_ODR_50, XL_ODR_119, XL_ODR_238, XL_ODR_476, 
    XL_ODR_952 } accel_odr_t;
typedef enum { A_ABW_408, A_ABW_211, A_ABW_105, A_ABW_50 } accel_abw_t;
// typedef enum { 
//     M_ODR_0625, M_ODR_125, M_ODR_250, M_ODR_5, M_ODR_10, M_ODR_20, M_ODR_40, M_ODR_80 } mag_odr_t;
typedef enum { XG_INT1 = INT1_CTRL, XG_INT2 = INT2_CTRL } interrupt_select_t;
typedef enum { 
	INT_DRDY_XL = (1 << 0),	INT_DRDY_G = (1 << 1), INT1_BOOT = (1 << 2), INT2_DRDY_TEMP = (1 << 2), 
	INT_FTH = (1 << 3), INT_OVR = (1 << 4), INT_FSS5 = (1 << 5), INT_IG_XL = (1 << 6), 
	INT1_IG_G = (1 << 7), INT2_INACT = (1 << 7) } interrupt_generators_t;
typedef enum { 
	XLIE_XL = (1 << 0), XHIE_XL = (1 << 1), YLIE_XL = (1 << 2), YHIE_XL = (1 << 3), 
	ZLIE_XL = (1 << 4), ZHIE_XL = (1 << 5), GEN_6D = (1 << 6) } accel_interrupt_generator_t;
typedef enum { 
	XLIE_G = (1 << 0), XHIE_G = (1 << 1), YLIE_G = (1 << 2),
	YHIE_G = (1 << 3), ZLIE_G = (1 << 4), ZHIE_G = (1 << 5) } gyro_interrupt_generator_t;
// typedef enum { ZIEN = (1 << 5), YIEN = (1 << 6), XIEN = (1 << 7) } mag_interrupt_generator_t;
typedef enum { INT_ACTIVE_HIGH, INT_ACTIVE_LOW } h_lactive_t;
typedef enum { INT_PUSH_PULL, INT_OPEN_DRAIN } pp_od_t;
typedef enum { FIFO_OFF = 0, FIFO_THS = 1, FIFO_CONT_TRIGGER = 3, 
    FIFO_OFF_TRIGGER = 4, FIFO_CONT = 6 } fifoMode_t;
typedef enum { X_AXIS, Y_AXIS, Z_AXIS, ALL_AXIS } lsm9ds1_axis_t;

typedef struct {
	uint8_t agAddress, // mAddress, _mAddress, 
        _xgAddress, accel_enabled, accel_scale, 
        accel_sampleRate, accel_enableX, accel_enableY, accel_enableZ, accel_highResEnable, 
        accel_highResBandwidth, gyro_enabled, gyro_sampleRate, gyro_bandwidth, gyro_lowPowerEnable, 
        gyro_HPFEnable, gyro_HPFCutoff, gyro_flipX, gyro_flipY, gyro_flipZ, gyro_orientation, 
        gyro_enableX, gyro_enableY, gyro_enableZ, gyro_latchInterrupt, temp_enabled; // , mag_enabled, mag_scale; 
        // mag_sampleRate, mag_tempCompensationEnable, mag_XYPerformance, mag_ZPerformance, 
        // mag_lowPowerEnable, mag_operatingMode, temp_enabled;
    uint16_t gyro_scale; 
	int8_t accel_bandwidth;
    float aRes, gRes;// , mRes;
    float gBias[3], aBias[3];// , mBias[3];
    int16_t gBiasRaw[3], aBiasRaw[3];//, mBiasRaw[3];
    bool _autoCalc;
} lsm9ds1_config_t;

lsm9ds1_config_t lsm9ds1_config;
int16_t m_imu_raw[7]; // a(x, y, z), g(x, y, z), m(x, y, z), temp
// uint8_t m_imu_data[40]; // a(x, y, z), g(x, y, z), m(x, y, z), temp

void calcaRes(lsm9ds1_config_t * lsm_cfg) {
    switch (lsm_cfg->accel_scale) {
        case 2:  lsm_cfg->aRes = SENSITIVITY_ACCELEROMETER_2;  break;
        case 4:  lsm_cfg->aRes = SENSITIVITY_ACCELEROMETER_4;  break;
        case 8:  lsm_cfg->aRes = SENSITIVITY_ACCELEROMETER_8;  break;
        case 16: lsm_cfg->aRes = SENSITIVITY_ACCELEROMETER_16; break;
        default: break;
    }
}

void calcgRes(lsm9ds1_config_t * lsm_cfg) {
    switch (lsm_cfg->gyro_scale) {
        case 245:  lsm_cfg->gRes = SENSITIVITY_GYROSCOPE_245;  break;
        case 500:  lsm_cfg->gRes = SENSITIVITY_GYROSCOPE_500;  break;
        case 2000: lsm_cfg->gRes = SENSITIVITY_GYROSCOPE_2000; break;
        default:   break;
    }
}

/*void calcmRes(lsm9ds1_config_t * lsm_cfg) {
    switch (lsm_cfg->mag_scale) {
        case 4:  lsm_cfg->mRes = SENSITIVITY_MAGNETOMETER_4;  break;
        case 8:  lsm_cfg->mRes = SENSITIVITY_MAGNETOMETER_8;  break;
        case 12: lsm_cfg->mRes = SENSITIVITY_MAGNETOMETER_12; break;
        case 16: lsm_cfg->mRes = SENSITIVITY_MAGNETOMETER_16; break;
        default: break;
    }	
}*/

static void lsm9ds1_imu_init(lsm9ds1_config_t * lsm_cfg) {

    lsm_cfg->agAddress = LSM9DS1_AG_ADDR(1);
    // lsm_cfg->mAddress = LSM9DS1_M_ADDR(1);

    lsm_cfg->gyro_enabled = true;
    lsm_cfg->gyro_enableX = true;
    lsm_cfg->gyro_enableY = true;
    lsm_cfg->gyro_enableZ = true;
    lsm_cfg->gyro_scale = 2000;
    lsm_cfg->gyro_sampleRate = 3;
    lsm_cfg->gyro_bandwidth = 0;
    lsm_cfg->gyro_lowPowerEnable = false;
    lsm_cfg->gyro_HPFEnable = false;
    lsm_cfg->gyro_HPFCutoff = 0;
    lsm_cfg->gyro_flipX = false;
    lsm_cfg->gyro_flipY = false;
    lsm_cfg->gyro_flipZ = false;
    lsm_cfg->gyro_orientation = 0;
    lsm_cfg->gyro_latchInterrupt = true;
    lsm_cfg->accel_enabled = true;
    lsm_cfg->accel_enableX = true;
    lsm_cfg->accel_enableY = true;
    lsm_cfg->accel_enableZ = true;
    lsm_cfg->accel_scale = 8;
    lsm_cfg->accel_sampleRate = 3;
    lsm_cfg->accel_bandwidth = -1;
    lsm_cfg->accel_highResEnable = false;
    lsm_cfg->accel_highResBandwidth = 0;
    /*lsm_cfg->mag_enabled = true;
    lsm_cfg->mag_scale = 4;
    lsm_cfg->mag_sampleRate = 7;
    lsm_cfg->mag_tempCompensationEnable = false;
    lsm_cfg->mag_XYPerformance = 3;
    lsm_cfg->mag_ZPerformance = 3;
    lsm_cfg->mag_lowPowerEnable = false;
    lsm_cfg->mag_operatingMode = 0;*/
    lsm_cfg->temp_enabled = true;
    
    for (int i = 0; i < 3; i++) {
        lsm_cfg->aBias[i]    = 0; 
        lsm_cfg->aBiasRaw[i] = 0;
        lsm_cfg->gBias[i]    = 0;
        lsm_cfg->gBiasRaw[i] = 0;
        // lsm_cfg->mBias[i]    = 0;
        // lsm_cfg->mBiasRaw[i] = 0;
    }
    lsm_cfg->_autoCalc = true; // NOTE: false
    
    lsm_cfg->_xgAddress = lsm_cfg->agAddress;
    // lsm_cfg->_mAddress = lsm_cfg->mAddress;
    
    // constrain the scales
    if ((lsm_cfg->gyro_scale != 245) && (lsm_cfg->gyro_scale != 500) && 
        (lsm_cfg->gyro_scale != 2000)) {
        lsm_cfg->gyro_scale = 245;
    }
        
    if ((lsm_cfg->accel_scale != 2) && (lsm_cfg->accel_scale != 4) && 
        (lsm_cfg->accel_scale != 8) && (lsm_cfg->accel_scale != 16)) {
        lsm_cfg->accel_scale = 2;
    }
        
    /*if ((lsm_cfg->mag_scale != 4) && (lsm_cfg->mag_scale != 8) && 
        (lsm_cfg->mag_scale != 12) && (lsm_cfg->mag_scale != 16)) {
        lsm_cfg->mag_scale = 4;
    }*/
    
    calcaRes(lsm_cfg); // Calculate g/ADC tick, stored in aRes variable
    calcgRes(lsm_cfg); // Calculate DPS/ADC tick, stored in gRes variable
    // calcmRes(lsm_cfg); // Calculate Gs/ADC tick, stored in mRes variable
        
    // Read the gyro group WHO_AM_I_M
    /*uint8_t mTest[1];
    uint8_t start_address = WHO_AM_I_M;
    m_xfer_done = false;
    ret_code_t err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_mAddress, &start_address, 1, true);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    m_xfer_done = false;
    err_code = nrf_drv_twi_rx(&m_twi, lsm_cfg->_mAddress, mTest, 1);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);*/
    
    // Read the accel/mag group WHO_AM_I_XG
    uint8_t xgTest[1];
    uint8_t start_address = WHO_AM_I_XG;
    m_xfer_done = false;
    ret_code_t err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_xgAddress, &start_address, 1, true);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    m_xfer_done = false;
    err_code = nrf_drv_twi_rx(&m_twi, lsm_cfg->_xgAddress, xgTest, 1);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
     
    /*if (((xgTest[0] << 8) | mTest[0]) != ((WHO_AM_I_AG_RSP << 8) | WHO_AM_I_M_RSP)) {
        return;
    }*/
    
    uint8_t tempRegValue = 0;
    if (lsm_cfg->gyro_enabled) {
        tempRegValue = (lsm_cfg->gyro_sampleRate & 0x07) << 5;
    }
    switch (lsm_cfg->gyro_scale) {
        case 500:  tempRegValue |= (0x1 << 3); break;
        case 2000: tempRegValue |= (0x3 << 3); break;
    }
    tempRegValue |= (lsm_cfg->gyro_bandwidth & 0x3);
    
    uint8_t reg[2];
    reg[0] = CTRL_REG1_G;
    reg[1] = tempRegValue;
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_xgAddress, reg, 2, false);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    
    reg[0] = CTRL_REG2_G;
    reg[1] = 0x00;
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_xgAddress, reg, 2, false);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    
    tempRegValue = lsm_cfg->gyro_lowPowerEnable ? (1 << 7) : 0;
    if (lsm_cfg->gyro_HPFEnable) {
        tempRegValue |= (1 << 6) | (lsm_cfg->gyro_HPFCutoff & 0x0F);
    }
    reg[0] = CTRL_REG3_G;
    reg[1] = tempRegValue;
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_xgAddress, reg, 2, false);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);

    tempRegValue = 0;
    if (lsm_cfg->gyro_enableZ) { tempRegValue |= (1 << 5); }
    if (lsm_cfg->gyro_enableY) { tempRegValue |= (1 << 4); }
    if (lsm_cfg->gyro_enableX) { tempRegValue |= (1 << 3); }
    if (lsm_cfg->gyro_latchInterrupt) { tempRegValue |= (1 << 1); }
    reg[0] = CTRL_REG4;
    reg[1] = tempRegValue;
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_xgAddress, reg, 2, false);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);

    tempRegValue = 0;
    if (lsm_cfg->gyro_flipX) { tempRegValue |= (1 << 5); }
    if (lsm_cfg->gyro_flipY) { tempRegValue |= (1 << 4); }
    if (lsm_cfg->gyro_flipZ) { tempRegValue |= (1 << 3); }
    reg[0] = ORIENT_CFG_G;
    reg[1] = tempRegValue;
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_xgAddress, reg, 2, false);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    
    tempRegValue = 0;
    if (lsm_cfg->accel_enableZ) { tempRegValue |= (1 << 5); }
    if (lsm_cfg->accel_enableY) { tempRegValue |= (1 << 4); }
    if (lsm_cfg->accel_enableX) { tempRegValue |= (1 << 3); }
    reg[0] = CTRL_REG5_XL;
    reg[1] = tempRegValue;
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_xgAddress, reg, 2, false);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    
    tempRegValue = 0;
    if (lsm_cfg->accel_enabled) {
        tempRegValue |= (lsm_cfg->accel_sampleRate & 0x07) << 5;
    }
    switch (lsm_cfg->accel_scale) {
        case 4: tempRegValue |= (0x2 << 3); break;
        case 8: tempRegValue |= (0x3 << 3); break;
        case 16: tempRegValue |= (0x1 << 3); break;
    }
    if (lsm_cfg->accel_bandwidth >= 0) {
        tempRegValue = (tempRegValue | (1 << 2)) | (lsm_cfg->accel_bandwidth & 0x03);
    }
    reg[0] = CTRL_REG6_XL;
    reg[1] = tempRegValue;
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_xgAddress, reg, 2, false);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    
    tempRegValue = 0;
    if (lsm_cfg->accel_highResEnable) {
        tempRegValue = (tempRegValue | (1 << 7)) | (lsm_cfg->accel_highResBandwidth & 0x3) << 5;
    }
    reg[0] = CTRL_REG7_XL;
    reg[1] = tempRegValue;
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_xgAddress, reg, 2, false);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);

    /*tempRegValue = 0;
    if (lsm_cfg->mag_tempCompensationEnable) { tempRegValue |= (1 << 7); }
    // NOTE: do these next two lines belong in the if??
    tempRegValue |= (lsm_cfg->mag_XYPerformance & 0x3) << 5;
    tempRegValue |= (lsm_cfg->mag_sampleRate & 0x7) << 2;
    reg[0] = CTRL_REG1_M;
    reg[1] = tempRegValue;
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_mAddress, reg, 2, false);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    
    tempRegValue = 0;
    switch (lsm_cfg->mag_scale) {
        case 8:  tempRegValue |= (0x1 << 5); break;
        case 12: tempRegValue |= (0x2 << 5); break;
        case 16: tempRegValue |= (0x3 << 5); break;
    }
    reg[0] = CTRL_REG2_M;
    reg[1] = tempRegValue;
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_mAddress, reg, 2, false);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    
    tempRegValue = 0;
    if (lsm_cfg->mag_lowPowerEnable) { tempRegValue |= (1 << 5); }
    // NOTE: does this following line belong in the if??
    tempRegValue |= (lsm_cfg->mag_operatingMode & 0x3);
    // NOTE maybe we don't need THIS particular I2C transfer
    reg[0] = CTRL_REG3_M;
    reg[1] = tempRegValue;
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_mAddress, reg, 2, false);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);

    tempRegValue = (lsm_cfg->mag_ZPerformance & 0x3) << 2;
    reg[0] = CTRL_REG4_M;
    reg[1] = tempRegValue;
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_mAddress, reg, 2, false);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);

    tempRegValue = 0;
    reg[0] = CTRL_REG5_M;
    reg[1] = tempRegValue;
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_mAddress, reg, 2, false);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);*/

}

void enableFIFO(lsm9ds1_config_t * lsm_cfg, bool enable /* = true */) {
    ret_code_t err_code;
    uint8_t temp[1]; 
    uint8_t start_address = CTRL_REG9;
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_xgAddress, &start_address, 1, true);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    m_xfer_done = false;
    err_code = nrf_drv_twi_rx(&m_twi, lsm_cfg->_xgAddress, temp, 1);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    if (enable) { temp[0] |= (1 << 1); }
    else { temp[0] &= ~(1 << 1); }

    uint8_t reg[2];
    reg[0] = CTRL_REG9;
    reg[1] = temp[0];
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_xgAddress, reg, 2, false);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
}

void setFIFO(lsm9ds1_config_t * lsm_cfg, fifoMode_t fifoMode, uint8_t fifoThs) {
    uint8_t reg[2];
    reg[0] = FIFO_CTRL;
    // Limit threshold - 0x1F (31) is the maximum.
    reg[1] = ((fifoMode & 0x7) << 5) | ((fifoThs <= 0x1F ? fifoThs : 0x1F) & 0x1F);
    m_xfer_done = false;
    ret_code_t err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_xgAddress, reg, sizeof(reg), false);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false); 
}


void readAccel(lsm9ds1_config_t * lsm_cfg) {
    ret_code_t err_code;
    uint8_t buff[6] = { 0, 0, 0, 0, 0, 0 };
    uint8_t start_address = OUT_X_L_XL;
    
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_xgAddress, &start_address, 1, true);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    
    m_xfer_done = false;
    err_code = nrf_drv_twi_rx(&m_twi, lsm_cfg->_xgAddress, buff, 6);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    
    for (int i = 0; i <= 2; i++) 
        m_imu_raw[i] = (buff[(2*i)+1] << 8) | buff[2*i];

    if (lsm_cfg->_autoCalc) {
        m_imu_raw[0] -= lsm_cfg->aBiasRaw[X_AXIS]; 
        m_imu_raw[1] -= lsm_cfg->aBiasRaw[Y_AXIS]; 
        m_imu_raw[2] -= lsm_cfg->aBiasRaw[Z_AXIS];
    }
}


int16_t readAccelAxis(lsm9ds1_config_t * lsm_cfg, lsm9ds1_axis_t axis) {
    ret_code_t err_code;
    uint8_t temp[2] = { 0, 0 };
    uint8_t start_address = OUT_X_L_XL + (2 * axis);
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_xgAddress, &start_address, 1, true);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    m_xfer_done = false;
    err_code = nrf_drv_twi_rx(&m_twi, lsm_cfg->_xgAddress, temp, 2);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    int16_t value = (temp [1] << 8) | temp[0];
    if (lsm_cfg->_autoCalc) {
        value -= lsm_cfg->aBiasRaw[axis];
    }
    return value;
}

void readGyro(lsm9ds1_config_t * lsm_cfg) {
    
    ret_code_t err_code;
    uint8_t buff[6] = { 0, 0, 0, 0, 0, 0 };
    uint8_t start_address = OUT_X_L_G;
    
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_xgAddress, &start_address, 1, true);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    
    m_xfer_done = false;
    err_code = nrf_drv_twi_rx(&m_twi, lsm_cfg->_xgAddress, buff, 6);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);

    for (int i = 0; i <= 2; i++)
        m_imu_raw[i+3] = (buff[(2*i)+1] << 8) | buff[2*i]; 

    if (lsm_cfg->_autoCalc) {
        m_imu_raw[3] -= lsm_cfg->gBiasRaw[X_AXIS];
        m_imu_raw[4] -= lsm_cfg->gBiasRaw[Y_AXIS];
        m_imu_raw[5] -= lsm_cfg->gBiasRaw[Z_AXIS];
    }
}
	
int16_t readGyroAxis(lsm9ds1_config_t * lsm_cfg, lsm9ds1_axis_t axis) {
    ret_code_t err_code;
    uint8_t temp[2] = { 0, 0 };
    uint8_t start_address = OUT_X_L_G + (2 * axis);
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_xgAddress, &start_address, 1, true);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    m_xfer_done = false;
    err_code = nrf_drv_twi_rx(&m_twi, lsm_cfg->_xgAddress, temp, 2);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    int16_t value = (temp[1] << 8) | temp[0];
    if (lsm_cfg->_autoCalc) { value -= lsm_cfg->gBiasRaw[axis]; }
    return value;
}


/*void readMag(lsm9ds1_config_t * lsm_cfg) {
    
    ret_code_t err_code;
    uint8_t buff[6] = { 0, 0, 0, 0, 0, 0 };
    uint8_t start_address = OUT_X_L_M;
    
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_mAddress, &start_address, 1, true);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    
    m_xfer_done = false;
    err_code = nrf_drv_twi_rx(&m_twi, lsm_cfg->_mAddress, buff, 6);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);

    for (int i = 0; i <= 2; i++)
        m_imu_raw[i+6] = (buff[(2*i)+1] << 8) | buff[2*i];

    if (lsm_cfg->_autoCalc) {
        m_imu_raw[6] -= lsm_cfg->mBiasRaw[X_AXIS];
        m_imu_raw[7] -= lsm_cfg->mBiasRaw[Y_AXIS];
        m_imu_raw[8] -= lsm_cfg->mBiasRaw[Z_AXIS];
    }
}


int16_t readMagAxis(lsm9ds1_config_t * lsm_cfg, lsm9ds1_axis_t axis) {
    ret_code_t err_code;
    uint8_t temp[2] = { 0, 0 };
    uint8_t start_address = OUT_X_L_M + (2 * axis);
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_mAddress, &start_address, 1, true);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    m_xfer_done = false;
    err_code = nrf_drv_twi_rx(&m_twi, lsm_cfg->_mAddress, temp, 2);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    return (temp[1] << 8) | temp[0];
}*/

void readTemp(lsm9ds1_config_t * lsm_cfg) {
    
    ret_code_t err_code;
    uint8_t temp[2] = { 0, 0 };
    uint8_t start_address = OUT_TEMP_L;
    
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_xgAddress, &start_address, 1, true);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    
    m_xfer_done = false;
    err_code = nrf_drv_twi_rx(&m_twi, lsm_cfg->_xgAddress, temp, 2);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    
	m_imu_raw[6] = 25 + (int16_t)(temp[1] << 8 | temp[0]);

}

float calcAccel(lsm9ds1_config_t * lsm_cfg, int16_t accel) {
    return lsm_cfg->aRes * (float)accel;
}

float calcGyro(lsm9ds1_config_t * lsm_cfg, int16_t gyro) {
    return lsm_cfg->gRes * (float)gyro;
}

/*float calcMag(lsm9ds1_config_t * lsm_cfg, int16_t mag) { 
    return lsm_cfg->mRes * (float)mag; 
}*/

	
void calibrate(lsm9ds1_config_t * lsm_cfg, bool autoCalc/*=true*/) {
    ret_code_t err_code;
    uint8_t start_address = 0;
    uint8_t data[6] = { 0, 0, 0, 0, 0, 0 };
    uint8_t samples[1] = { 0 };
    int ii;
    int32_t aBiasRawTemp[3] = { 0, 0, 0 };
    int32_t gBiasRawTemp[3] = { 0, 0, 0 };
    enableFIFO(lsm_cfg, true);
    setFIFO(lsm_cfg, FIFO_THS, 0x1F);
    while (samples[0] < 0x1F) {
        start_address = FIFO_SRC;
        m_xfer_done = false;
        err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_xgAddress, &start_address, 1, true);
        APP_ERROR_CHECK(err_code);
        while (m_xfer_done == false);
        m_xfer_done = false;
        err_code = nrf_drv_twi_rx(&m_twi, lsm_cfg->_xgAddress, samples, 1);
        APP_ERROR_CHECK(err_code);
        while (m_xfer_done == false);
        samples[0] &= 0x3F; 
    }
    for (ii = 0; ii < samples[0]; ii++)  {	
        readAccel(lsm_cfg);
        aBiasRawTemp[0] += m_imu_raw[0];
        aBiasRawTemp[1] += m_imu_raw[1];
        aBiasRawTemp[2] += m_imu_raw[2] - (int16_t)(1./lsm_cfg->aRes);
        readGyro(lsm_cfg);
        gBiasRawTemp[0] += m_imu_raw[3];
        gBiasRawTemp[1] += m_imu_raw[4];
        gBiasRawTemp[2] += m_imu_raw[5];
    }  
    for (ii = 0; ii < 3; ii++) {
        lsm_cfg->aBias[ii] = calcAccel(lsm_cfg, lsm_cfg->aBiasRaw[ii]);                                                                                                                                                                         
        lsm_cfg->aBiasRaw[ii] = aBiasRawTemp[ii] / samples[0];
        lsm_cfg->gBias[ii] = calcGyro(lsm_cfg, lsm_cfg->gBiasRaw[ii]);
        lsm_cfg->gBiasRaw[ii] = gBiasRawTemp[ii] / samples[0];
    }
    enableFIFO(lsm_cfg, false);
    setFIFO(lsm_cfg, FIFO_OFF, 0x00);
    if (autoCalc) {
        lsm_cfg->_autoCalc = true;
    }
}

uint8_t accelAvailable(lsm9ds1_config_t * lsm_cfg) {
    ret_code_t err_code;
    uint8_t status[1] = { 0 };
    uint8_t start_address = STATUS_REG_1;
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_xgAddress, &start_address, 1, true);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    m_xfer_done = false;
    err_code = nrf_drv_twi_rx(&m_twi, lsm_cfg->_xgAddress, status, 1);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    return (status[0] & (1 << 0));
}

uint8_t gyroAvailable(lsm9ds1_config_t * lsm_cfg) {
    ret_code_t err_code;
    uint8_t status[1] = { 0 };
    uint8_t start_address = STATUS_REG_1;
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_xgAddress, &start_address, 1, true);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    m_xfer_done = false;
    err_code = nrf_drv_twi_rx(&m_twi, lsm_cfg->_xgAddress, status, 1);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    return ((status[0] & (1 << 1)) >> 1);
}

/*uint8_t magAvailable(lsm9ds1_config_t * lsm_cfg, lsm9ds1_axis_t axis) {
    ret_code_t err_code;
    uint8_t status[1] = { 0 };
    uint8_t start_address = STATUS_REG_M;
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_mAddress, &start_address, 1, true);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    m_xfer_done = false;
    err_code = nrf_drv_twi_rx(&m_twi, lsm_cfg->_mAddress, status, 1);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    return ((status[0] & (1 << axis)) >> axis);
}

uint8_t tempAvailable(lsm9ds1_config_t * lsm_cfg) {
    ret_code_t err_code;
    uint8_t status[1] = { 0 };
    uint8_t start_address = STATUS_REG_1;
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_xgAddress, &start_address, 1, true);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    m_xfer_done = false;
    err_code = nrf_drv_twi_rx(&m_twi, lsm_cfg->_xgAddress, status, 1);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    return ((status[0] & (1 << 2)) >> 2);
}*/


/*void calibrateMag(lsm9ds1_config_t * lsm_cfg, bool loadIn) {
    ret_code_t err_code; 
    int16_t magMin[3] = { 0, 0, 0 };
    int16_t magMax[3] = { 0, 0, 0 }; // The road warrior
    
    for (int i = 0; i < 128; i++) {
        while (!magAvailable(lsm_cfg, ALL_AXIS));
        readMag(lsm_cfg);
        int16_t magTemp[3] = { 0, 0, 0 };
        magTemp[0] = m_imu_data[6];		
        magTemp[1] = m_imu_data[7];
        magTemp[2] = m_imu_data[8];
        for (int j = 0; j < 3; j++) {
            if (magTemp[j] > magMax[j]) { magMax[j] = magTemp[j]; }
            if (magTemp[j] < magMin[j]) { magMin[j] = magTemp[j]; }
        }
    }
    for (int j = 0; j < 3; j++) {
        lsm_cfg->mBiasRaw[j] = (magMax[j] + magMin[j]) / 2;
        lsm_cfg->mBias[j] = calcMag(lsm_cfg, lsm_cfg->mBiasRaw[j]);
        if (loadIn) {
            // offset the magnetometer
            if (j > 2) { 
                return; // TODO what to do about this return?? 
            }
            uint8_t reg[2];
            reg[0] = OFFSET_X_REG_L_M + (2 * j);
            reg[1] = lsm_cfg->mBiasRaw[j] & 0x00FF;;
            m_xfer_done = false;
            err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_mAddress, reg, 2, false);
            APP_ERROR_CHECK(err_code);
            while (m_xfer_done == false);

            reg[0] = OFFSET_X_REG_H_M + (2 * j);
            reg[1] = (lsm_cfg->mBiasRaw[j] & 0xFF00) >> 8;
            m_xfer_done = false;
            err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_mAddress, reg, 2, false);
            APP_ERROR_CHECK(err_code);
            while (m_xfer_done == false);
        }
    }
}*/

void setAccelScale(lsm9ds1_config_t * lsm_cfg, uint8_t aScl) {
    
    ret_code_t err_code;
    uint8_t start_address = CTRL_REG6_XL;
    uint8_t tempRegValue[1] = { 0 };
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_xgAddress, &start_address, 1, true);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    m_xfer_done = false;
    err_code = nrf_drv_twi_rx(&m_twi, lsm_cfg->_xgAddress, tempRegValue, 1);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    
    tempRegValue[0] &= 0xE7;
    switch (aScl) {
        case 4:  tempRegValue[0] |= (0x2 << 3); lsm_cfg->accel_scale = 4;  break;
        case 8:  tempRegValue[0] |= (0x3 << 3); lsm_cfg->accel_scale = 8;  break;
        case 16: tempRegValue[0] |= (0x1 << 3); lsm_cfg->accel_scale = 16; break;
        default: lsm_cfg->accel_scale = 2; break;
    }
    uint8_t reg[2];
    reg[0] = CTRL_REG6_XL;
    reg[1] = tempRegValue[0];
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_xgAddress, reg, 2, false);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    
    // aScale = aScl
    calcaRes(lsm_cfg);
}


void setGyroScale(lsm9ds1_config_t * lsm_cfg, uint16_t gScl) {
    
    ret_code_t err_code;
    uint8_t start_address = CTRL_REG1_G;
    uint8_t ctrl1RegValue[1] = { 0 };
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_xgAddress, &start_address, 1, true);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    m_xfer_done = false;
    err_code = nrf_drv_twi_rx(&m_twi, lsm_cfg->_xgAddress, ctrl1RegValue, 1);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    
    ctrl1RegValue[0] &= 0xE7;
    switch (gScl) {
        case 500:  ctrl1RegValue[0] |= (0x1 << 3); lsm_cfg->gyro_scale = 500;  break;
        case 2000: ctrl1RegValue[0] |= (0x3 << 3); lsm_cfg->gyro_scale = 2000; break;
        default:   lsm_cfg->gyro_scale = 245; break;
    }
    uint8_t reg[2];
    reg[0] = CTRL_REG1_G;
    reg[1] = ctrl1RegValue[0];
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_xgAddress, reg, 2, false);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    // gScale = gScl
    calcgRes(lsm_cfg);	
}


/*void setMagScale(lsm9ds1_config_t * lsm_cfg, uint8_t mScl) {
    
    ret_code_t err_code;
    uint8_t start_address = CTRL_REG2_M;
    uint8_t temp[1] = { 0 };
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_mAddress, &start_address, 1, true);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    m_xfer_done = false;
    err_code = nrf_drv_twi_rx(&m_twi, lsm_cfg->_mAddress, temp, 1);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    
    temp[0] &= 0xFF^(0x3 << 5); 
    switch (mScl) {
        case 8:  temp[0] |= (0x1 << 5); lsm_cfg->mag_scale = 8;  break;
        case 12: temp[0] |= (0x2 << 5); lsm_cfg->mag_scale = 12; break;
        case 16: temp[0] |= (0x3 << 5); lsm_cfg->mag_scale = 16; break;
        default: lsm_cfg->mag_scale = 4; break;
    }			
    uint8_t reg[2];
    reg[0] = CTRL_REG2_M;
    reg[1] = temp[0];
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_mAddress, reg, 2, false);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    // mScale = mScl;
    calcmRes(lsm_cfg);
}*/

void setAccelODR(lsm9ds1_config_t * lsm_cfg, uint8_t aRate) {
    ret_code_t err_code;
    if ((aRate & 0x07) != 0) {
        uint8_t start_address = CTRL_REG6_XL;
        uint8_t temp[1] = { 0 };
        m_xfer_done = false;
        err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_xgAddress, &start_address, 1, true);
        APP_ERROR_CHECK(err_code);
        while (m_xfer_done == false);
        m_xfer_done = false;
        err_code = nrf_drv_twi_rx(&m_twi, lsm_cfg->_xgAddress, temp, 1);
        APP_ERROR_CHECK(err_code);
        while (m_xfer_done == false);
        
        temp[0] &= 0x1F;
        temp[0] |= ((aRate & 0x07) << 5);
        lsm_cfg->accel_sampleRate = aRate & 0x07;
        uint8_t reg[2];
        reg[0] = CTRL_REG6_XL;
        reg[1] = temp[0];
        m_xfer_done = false;
        err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_xgAddress, reg, 2, false);
        APP_ERROR_CHECK(err_code);
        while (m_xfer_done == false);
    }
}	

void setGyroODR(lsm9ds1_config_t * lsm_cfg, uint8_t gRate) {
    ret_code_t err_code;
    if ((gRate & 0x07) != 0) { 
        uint8_t start_address = CTRL_REG1_G;
        uint8_t temp[1] = { 0 };
        m_xfer_done = false;
        err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_xgAddress, &start_address, 1, true);
        APP_ERROR_CHECK(err_code);
        while (m_xfer_done == false);
        m_xfer_done = false;
        err_code = nrf_drv_twi_rx(&m_twi, lsm_cfg->_xgAddress, temp, 1);
        APP_ERROR_CHECK(err_code);
        while (m_xfer_done == false);
        
        temp[0] &= 0xFF^(0x7 << 5); 
        temp[0] |= (gRate & 0x07) << 5;
        lsm_cfg->gyro_sampleRate = gRate & 0x07; 
        uint8_t reg[2];
        reg[0] = CTRL_REG1_G;
        reg[1] = temp[0];
        m_xfer_done = false;
        err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_xgAddress, reg, 2, false);
        APP_ERROR_CHECK(err_code);
        while (m_xfer_done == false);
    }
}

/*void setMagODR(lsm9ds1_config_t * lsm_cfg, uint8_t mRate) {
    
    ret_code_t err_code;
    uint8_t start_address = CTRL_REG1_M; 
    uint8_t temp[1] = { 0 };
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_mAddress, &start_address, 1, true);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    m_xfer_done = false;
    err_code = nrf_drv_twi_rx(&m_twi, lsm_cfg->_mAddress, temp, 1);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    temp[0] &= 0xFF^(0x7 << 2);
    temp[0] |= ((mRate & 0x07) << 2);
    lsm_cfg->mag_sampleRate = mRate & 0x07;
    uint8_t reg[2];
    reg[0] = CTRL_REG1_M;
    reg[1] = temp[0];
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_mAddress, reg, 2, false);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
} */

void configInactivity(lsm9ds1_config_t * lsm_cfg, uint8_t duration, uint8_t threshold, 
    bool sleepOn) {
    
    uint8_t temp = 0;
    temp = threshold & 0x7F;
    if (sleepOn) temp |= (1 << 7);

    uint8_t reg[2];

    reg[0] = ACT_THS;
    reg[1] = temp;
    m_xfer_done = false;
    ret_code_t err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_xgAddress, reg, 2, false);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);

    reg[0] = ACT_DUR;
    reg[1] = duration;
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_xgAddress, reg, 2, false);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
}

void configAccelInt(lsm9ds1_config_t * lsm_cfg, uint8_t generator, bool andInterrupts /*=false*/) {
    uint8_t temp = generator;
    if (andInterrupts) temp |= 0x80;
    uint8_t reg[2];
    reg[0] = INT_GEN_CFG_XL;
    reg[1] = temp;
    m_xfer_done = false;
    ret_code_t err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_xgAddress, reg, 2, false);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);

}

void configAccelThs(lsm9ds1_config_t * lsm_cfg, uint8_t threshold, lsm9ds1_axis_t axis, 
                                                uint8_t duration /* = 0 */, bool wait /* = 0 */) {
    uint8_t reg[2];
    reg[0] = INT_GEN_THS_X_XL;
    reg[1] = threshold;
    m_xfer_done = false;
    ret_code_t err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_xgAddress, reg, 2, false);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    
    uint8_t temp = (duration & 0x7F);
    if (wait) temp |= 0x80;
    
    reg[0] = INT_GEN_DUR_XL;
    reg[1] = temp;
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_xgAddress, reg, 2, false);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
}

void configGyroInt(lsm9ds1_config_t * lsm_cfg, uint8_t generator, bool aoi, bool latch) {
    uint8_t temp = generator;
    if (aoi) temp |= 0x80;
    if (latch) temp |= 0x40;
    uint8_t reg[2];
    reg[0] = INT_GEN_CFG_G;
    reg[1] = temp;
    m_xfer_done = false;
    ret_code_t err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_xgAddress, reg, 2, false);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
}

void configGyroThs(lsm9ds1_config_t * lsm_cfg, int16_t threshold, lsm9ds1_axis_t axis, 
                                                                    uint8_t duration, bool wait) {
    uint8_t buffer[2];
    buffer[0] = (threshold & 0x7F00) >> 8;
    buffer[1] = (threshold & 0x00FF);

    uint8_t reg[2];
    reg[0] = INT_GEN_THS_XH_G + (axis * 2);
    reg[1] = buffer[0];
    m_xfer_done = false;
    ret_code_t err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_xgAddress, reg, 2, false);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);

    reg[0] = INT_GEN_THS_XH_G + 1 + (axis * 2);
    reg[1] = buffer[1];
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_xgAddress, reg, 2, false);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    
    uint8_t temp;
    temp = (duration & 0x7F);
    if (wait) temp |= 0x80;
    
    reg[0] = INT_GEN_DUR_G;
    reg[1] = temp;
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_xgAddress, reg, 2, false);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
}

void configInt(lsm9ds1_config_t * lsm_cfg, interrupt_select_t interrupt, uint8_t generator, 
    h_lactive_t activeLow /*= INT_ACTIVE_LOW */, pp_od_t pushPull /* = INT_PUSH_PULL */) {
    
    uint8_t reg[2];
    reg[0] = interrupt;
    reg[1] = generator;
    m_xfer_done = false;
    ret_code_t err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_xgAddress, reg, 2, false);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    
    uint8_t temp[1] = { 0 };
    uint8_t start_address = CTRL_REG8;
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_xgAddress, &start_address, 1, true);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    m_xfer_done = false;
    err_code = nrf_drv_twi_rx(&m_twi, lsm_cfg->_xgAddress, temp, 1);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);

    if (activeLow) { temp[0] |= (1<<5); }
    else { temp[0] &= ~(1<<5); }
    if (pushPull) { temp[0] &= ~(1<<4); }
    else { temp[0] |= (1<<4); }
    
    reg[0] = CTRL_REG8;
    reg[1] = temp[0];
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_xgAddress, reg, sizeof(reg), false);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
}
                
/*void configMagInt(lsm9ds1_config_t * lsm_cfg, uint8_t generator, h_lactive_t activeLow, 
                                                                        bool latch) {
    uint8_t config = (generator & 0xE0);	
    if (activeLow == INT_ACTIVE_HIGH) config |= (1 << 2);
    if (!latch) config |= (1 << 1);
    if (generator != 0) config |= (1 << 0);
    uint8_t reg[2];
    reg[0] = INT_CFG_M;
    reg[1] = config;
    m_xfer_done = false;
    ret_code_t err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_mAddress, reg, 2, false);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
}

void configMagThs(lsm9ds1_config_t * lsm_cfg, uint16_t threshold) {
    uint8_t reg[2];
    ret_code_t err_code;

    reg[0] = INT_THS_H_M;
    reg[1] = (uint8_t)((threshold & 0x7F00) >> 8);
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_mAddress, reg, sizeof(reg), false);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);

    reg[0] = INT_THS_L_M;
    reg[1] = (uint8_t)(threshold & 0x00FF);
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_mAddress, reg, sizeof(reg), false);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
}*/

uint8_t getGyroIntSrc(lsm9ds1_config_t * lsm_cfg) {
    ret_code_t err_code;
    uint8_t start_address = INT_GEN_SRC_G;
    uint8_t intSrc[1] = { 0 };
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_xgAddress, &start_address, 1, true);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    m_xfer_done = false;
    err_code = nrf_drv_twi_rx(&m_twi, lsm_cfg->_xgAddress, intSrc, 1);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    if (intSrc[0] & (1<<6)) {
        return (intSrc[0] & 0x3F);
    }
    return 0;
}

uint8_t getAccelIntSrc(lsm9ds1_config_t * lsm_cfg) {
    ret_code_t err_code;
    uint8_t start_address = INT_GEN_SRC_XL;
    uint8_t intSrc[1] = { 0 };
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_xgAddress, &start_address, 1, true);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    m_xfer_done = false;
    err_code = nrf_drv_twi_rx(&m_twi, lsm_cfg->_xgAddress, intSrc, 1);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    if (intSrc[0] & (1 << 6)) {
        return (intSrc[0] & 0x3F);	
    }
    return 0;
}

/*uint8_t getMagIntSrc(lsm9ds1_config_t * lsm_cfg) {
    ret_code_t err_code;
    uint8_t start_address = INT_SRC_M;
    uint8_t intSrc[1] = { 0 };
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_mAddress, &start_address, 1, true);;
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    m_xfer_done = false;
    err_code = nrf_drv_twi_rx(&m_twi, lsm_cfg->_mAddress, intSrc, 1);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    if (intSrc[0] & (1 << 0)) {
        return (intSrc[0] & 0xFE);	
    }	
    return 0;
}*/

uint8_t getInactivity(lsm9ds1_config_t * lsm_cfg) {
    ret_code_t err_code;
    uint8_t start_address = STATUS_REG_0;
    uint8_t temp[1] = { 0 };
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_xgAddress, &start_address, 1, true);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    m_xfer_done = false;
    err_code = nrf_drv_twi_rx(&m_twi, lsm_cfg->_xgAddress, temp, 1);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    return (temp[0] & 0x10);
}

void sleepGyro(lsm9ds1_config_t * lsm_cfg, bool enable /* = true */) {
    ret_code_t err_code;
    uint8_t temp[1] = { 0 };
    uint8_t start_address = CTRL_REG9;
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_xgAddress, &start_address, 1, true);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    m_xfer_done = false;
    err_code = nrf_drv_twi_rx(&m_twi, lsm_cfg->_xgAddress, temp, 1);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    if (enable == true) {
        temp[0] |= (1 << 6);
    } else { temp[0] &= ~(1 << 6); }
    uint8_t reg[2];
    reg[0] = CTRL_REG9;
    reg[1] = temp[0];
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_xgAddress, reg, 2, false);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
}

uint8_t getFIFOSamples(lsm9ds1_config_t * lsm_cfg) { 
    ret_code_t err_code;
    uint8_t tmp[1] = { 0 };
    uint8_t start_address = FIFO_SRC; 
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, lsm_cfg->_xgAddress, &start_address, 1, true);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    m_xfer_done = false;
    err_code = nrf_drv_twi_rx(&m_twi, lsm_cfg->_xgAddress, tmp, 1);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    return (uint8_t)(tmp[0] & 0x3F);
}

void lsm9ds1_read(lsm9ds1_config_t * lsm_cfg) {
    readAccel(lsm_cfg);
    readGyro(lsm_cfg);
    readTemp(lsm_cfg);
}


#endif /* LSM9DS1_imu_H */ 