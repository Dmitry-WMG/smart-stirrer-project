#ifndef BH1745NUC_COLOUR_SENSOR_H
#define BH1745NUC_COLOUR_SENSOR_H

// BH1745NUC I2C ADDRESS/BITS
#define BH1745NUC_DEFAULT_ADDRESS (0x38) // ADDR =’L’: “0111000”
#define BH1745NUC_ADDRESS_HIGH (0x39) // ADDR =’H’: “0111001”

// BH1745NUC Conversion Delay (in ms)
#define BH1745NUC_CONVERSIONDELAY  (100)

// BH1745NUC Command Set
#define BH1745NUC_CMD_SYSTEM_CONTROL (0x40) // System control
#define BH1745NUC_CMD_MODE_CONTROL1 (0x41) // Function setting
#define BH1745NUC_CMD_MODE_CONTROL2 (0x42) // Function setting
#define BH1745NUC_CMD_MODE_CONTROL3 (0x44) // Function setting
#define BH1745NUC_CMD_RED_DATA_LSB (0x50) // Low byte of RED
#define BH1745NUC_CMD_RED_DATA_MSB (0x51) // High byte of RED
#define BH1745NUC_CMD_GREEN_DATA_LSB (0x52) // Low byte of GREEN
#define BH1745NUC_CMD_GREEN_DATA_MSB (0x53) // High byte of GREEN
#define BH1745NUC_CMD_BLUE_DATA_LSB (0x54) // Low byte of BLUE
#define BH1745NUC_CMD_BLUE_DATA_MSB (0x55) // High byte of BLUE
#define BH1745NUC_CMD_CLEAR_DATA_LSB (0x56) // Low byte of CLEAR
#define BH1745NUC_CMD_CLEAR_DATA_MSB (0x57) // High byte of CLEAR
#define BH1745NUC_CMD_DINT_DATA_LSB (0x58) // Low byte of Internal Data
#define BH1745NUC_CMD_DINT_DATA_MSB (0x59) // High byte of Internal Data
#define BH1745NUC_CMD_INTERRUPT (0x60) // Interrupt setting
#define BH1745NUC_CMD_PERSISTENCE (0x61) // Persistence setting
#define BH1745NUC_CMD_THRESHOLD_HI_LSB (0x62) // Higher threshold low byte
#define BH1745NUC_CMD_THRESHOLD_HI_MSB (0x63) // Higher threshold high byte
#define BH1745NUC_CMD_THRESHOLD_LO_LSB (0x64) // Lower threshold low byte
#define BH1745NUC_CMD_THRESHOLD_LO_MSB (0x65) // Lower threshold high byte
#define BH1745NUC_CMD_MANUFACTURER_ID (0x92)  // Manufacturer ID

// System Control Register
#define BH1745NUC_SYS_CNTR_SW_RESET_MASK (0x80) // SW reset
#define BH1745NUC_SYS_CNTR_SW_RESET_NOT_START (0x00) // Initial reset is not started
#define BH1745NUC_SYS_CNTR_SW_RESET_START (0x80) // Initial reset is started
#define BH1745NUC_SYS_CNTR_INT_RESET_MASK  (0x40) // INTERRUPT reset
#define BH1745NUC_SYS_CNTR_INT_RESET_NOT_INTIAL (0x00) // INTERRUPT pin status is not initialized.
#define BH1745NUC_SYS_CNTR_INT_RESET_INACTIVE (0x40) // INTERRUPT pin become inactive (high impedance)

// Mode Control 1 Register
#define BH1745NUC_MODE_CNTR1_MEAS_TIME_MASK (0x07) // RGBC Measurement time.
#define BH1745NUC_MODE_CNTR1_MEAS_TIME_160 (0x00) // 000 : 160 msec
#define BH1745NUC_MODE_CNTR1_MEAS_TIME_320 (0x01) // 001 : 320 msec
#define BH1745NUC_MODE_CNTR1_MEAS_TIME_640 (0x02) // 010 : 640 msec
#define BH1745NUC_MODE_CNTR1_MEAS_TIME_1280 (0x03) // 011 : 1280 msec
#define BH1745NUC_MODE_CNTR1_MEAS_TIME_2560 (0x04) // 100 : 2560 msec
#define BH1745NUC_MODE_CNTR1_MEAS_TIME_5120 (0x05) // 101 : 5120 msec

// Mode Control 2 Register
#define BH1745NUC_MODE_CNTR2_RGBC_VALID_MASK (0x80) // RGBC Data Update Status
#define BH1745NUC_MODE_CNTR2_RGBC_VALID_NOT_UPDATE (0x00)
#define BH1745NUC_MODE_CNTR2_RGBC_VALID_UPDATE (0x80)
#define BH1745NUC_MODE_CNTR2_RGBC_EN_MASK (0x10) 
#define BH1745NUC_MODE_CNTR2_RGBC_EN_INACTIVE (0x00) 
#define BH1745NUC_MODE_CNTR2_RGBC_EN_ACTIVE (0x10) 
#define BH1745NUC_MODE_CNTR2_ADC_GAIN_MASK (0x03) // GAIN setting
#define BH1745NUC_MODE_CNTR2_ADC_GAIN_1X (0x00) // 00 : 1X
#define BH1745NUC_MODE_CNTR2_ADC_GAIN_2X (0x01) // 01 : 2X
#define BH1745NUC_MODE_CNTR2_ADC_GAIN_16X (0x02) // 10 : 16X

// Interrupt Register
#define BH1745NUC_INTR_INT_STATUS_MASK (0x80) // INTERRUPT STATUS of RGBC
#define BH1745NUC_INTR_INT_STATUS_INACTIVE (0x00) // Interrupt signal is inactive
#define BH1745NUC_INTR_INT_STATUS_ACTIVE (0x80) // Interrupt signal is active
#define BH1745NUC_INTR_INT_LATCH_MASK (0x10) // INTERRUPT STATUS of RGBC
#define BH1745NUC_INTR_INT_LATCH_LATCHED (0x00)
#define BH1745NUC_INTR_INT_LATCH_UPDATED (0x10)
#define BH1745NUC_INTR_INT_SOURCE_MASK (0x0C) // INTERRUPT source select
#define BH1745NUC_INTR_INT_SOURCE_RED (0x00) // 00 : Red channel
#define BH1745NUC_INTR_INT_SOURCE_GREEN (0x04) // 00 : Green channel
#define BH1745NUC_INTR_INT_SOURCE_BLUE (0x08) // 00 : Blue channel
#define BH1745NUC_INTR_INT_SOURCE_CLEAR (0x0C) // 00 : Clear channel
#define BH1745NUC_INTR_INT_ENABLE_MASK (0x01) // INTERRUPT Enable
#define BH1745NUC_INTR_INT_ENABLE_DISABLE (0x00) // INTERRUPT pin disable
#define BH1745NUC_INTR_INT_ENABLE_ENABLE (0x01) // INTERRUPT pin enable

// Persistence Register
#define BH1745NUC_PERSISTENCE_MASK (0x03) // Interrupt persistence function
#define BH1745NUC_PERSISTENCE_TOGGLED_EACH (0x00) // 00 : Status toggled at each measurement end
#define BH1745NUC_PERSISTENCE_UPDATED_EACH (0x01) // 01 : Status updated at each measurement end
#define BH1745NUC_PERSISTENCE_UPDATED_4 (0x02) // 10 : Updated if 4 threshold judgments are the same
#define BH1745NUC_PERSISTENCE_UPDATED_8 (0x03) // 10 : Updated if 4 threshold judgments are the same

typedef enum {
    SW_RESET_NOT_START = BH1745NUC_SYS_CNTR_SW_RESET_NOT_START,
    SW_RESET_START = BH1745NUC_SYS_CNTR_SW_RESET_START
} bhSWReset_t;

typedef enum {
    INT_RESET_NOT_INTIAL = BH1745NUC_SYS_CNTR_INT_RESET_NOT_INTIAL,
    INT_RESET_INACTIVE = BH1745NUC_SYS_CNTR_INT_RESET_INACTIVE
} bhINTReset_t;

typedef enum {
    MEAS_TIME_160 = BH1745NUC_MODE_CNTR1_MEAS_TIME_160,
    MEAS_TIME_320 = BH1745NUC_MODE_CNTR1_MEAS_TIME_320,
    MEAS_TIME_640 = BH1745NUC_MODE_CNTR1_MEAS_TIME_640,
    MEAS_TIME_1280 = BH1745NUC_MODE_CNTR1_MEAS_TIME_1280,
    MEAS_TIME_2560 = BH1745NUC_MODE_CNTR1_MEAS_TIME_2560,
    MEAS_TIME_5120 = BH1745NUC_MODE_CNTR1_MEAS_TIME_5120
} bhMeasTime_t;

typedef enum {
    RGBC_VALID_NOT_UPDATE  = BH1745NUC_MODE_CNTR2_RGBC_VALID_NOT_UPDATE,
    RGBC_VALID_UPDATE = BH1745NUC_MODE_CNTR2_RGBC_VALID_UPDATE
} bhRGBCValid_t;

typedef enum {
    RGBC_EN_INACTIVE = BH1745NUC_MODE_CNTR2_RGBC_EN_INACTIVE,
    RGBC_EN_ACTIVE = BH1745NUC_MODE_CNTR2_RGBC_EN_ACTIVE
} bhRGBCEnable_t;

typedef enum {
    ADC_GAIN_1X = BH1745NUC_MODE_CNTR2_ADC_GAIN_1X,
    ADC_GAIN_2X = BH1745NUC_MODE_CNTR2_ADC_GAIN_2X,
    ADC_GAIN_16X = BH1745NUC_MODE_CNTR2_ADC_GAIN_16X
} bhADCGain_t;

typedef enum {
    STATUS_INACTIVE = BH1745NUC_INTR_INT_STATUS_INACTIVE,
    STATUS_ACTIVE = BH1745NUC_INTR_INT_STATUS_ACTIVE
} bhINTStatus_t;

typedef enum {
    INT_LATCH_LATCHED = BH1745NUC_INTR_INT_LATCH_LATCHED,
    INT_LATCH_UPDATED = BH1745NUC_INTR_INT_LATCH_UPDATED
} bhINTLatch_t;

typedef enum {
    INT_SOURCE_RED = BH1745NUC_INTR_INT_SOURCE_RED,
    INT_SOURCE_GREEN = BH1745NUC_INTR_INT_SOURCE_GREEN,
    INT_SOURCE_BLUE = BH1745NUC_INTR_INT_SOURCE_BLUE,
    INT_SOURCE_CLEAR = BH1745NUC_INTR_INT_SOURCE_CLEAR
} bhINTSource_t;

typedef enum {
    INT_ENABLE_DISABLE = BH1745NUC_INTR_INT_ENABLE_DISABLE,
    INT_ENABLE_ENABLE = BH1745NUC_INTR_INT_ENABLE_ENABLE
} bhINTEnable_t;

typedef enum {
    PERSISTENCE_TOGGLED_EACH = BH1745NUC_PERSISTENCE_TOGGLED_EACH,
    PERSISTENCE_UPDATED_EACH = BH1745NUC_PERSISTENCE_UPDATED_EACH,
    PERSISTENCE_UPDATED_4 = BH1745NUC_PERSISTENCE_UPDATED_4,
    PERSISTENCE_UPDATED_8 = BH1745NUC_PERSISTENCE_UPDATED_8
} bhPersistance_t;

typedef struct {
    uint8_t start_address;
    uint8_t bh_conversionDelay;
    bhSWReset_t bh_swreset;
    bhINTReset_t bh_intreset;
    bhMeasTime_t bh_meastime;
    bhRGBCValid_t bh_rgbcvalid;
    bhRGBCEnable_t bh_rgbcenable;
    bhADCGain_t bh_adcgain;
    bhINTStatus_t bh_intstatus;
    bhINTLatch_t bh_intlatch;
    bhINTSource_t bh_intsource;
    bhINTEnable_t bh_intenable;
    bhPersistance_t bh_persistance; 
} bh1745nuc_config_t; 

bh1745nuc_config_t bh1745nuc_config;
//uint16_t m_colour_sensor_data[4][4];
uint16_t m_colour_sensor_data[4];

// Set up the registers for the BH1745NUC colour sensor
static void bh1745nuc_colour_sensor_init(bh1745nuc_config_t * bh_cfg) {
    
    // Configure the default values
    bh_cfg->start_address = 0x50;
    bh_cfg->bh_swreset = SW_RESET_NOT_START;
    bh_cfg->bh_meastime = MEAS_TIME_160;
    bh_cfg->bh_rgbcvalid = RGBC_VALID_UPDATE;
    bh_cfg->bh_rgbcenable = RGBC_EN_ACTIVE;
    bh_cfg->bh_adcgain = ADC_GAIN_1X;
    bh_cfg->bh_intstatus = STATUS_INACTIVE;
    bh_cfg->bh_intlatch = INT_LATCH_LATCHED;
    bh_cfg->bh_intenable = INT_ENABLE_DISABLE;
    bh_cfg->bh_persistance = PERSISTENCE_UPDATED_EACH;

    ret_code_t err_code;
    uint8_t tx_buffer[2];

    tx_buffer[0] = BH1745NUC_CMD_SYSTEM_CONTROL;
    tx_buffer[1] = bh_cfg->bh_swreset | bh_cfg->bh_intreset;
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, BH1745NUC_DEFAULT_ADDRESS, tx_buffer, 2, false);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);

    tx_buffer[0] = BH1745NUC_CMD_MODE_CONTROL1;
    tx_buffer[1] = bh_cfg->bh_meastime;
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, BH1745NUC_DEFAULT_ADDRESS, tx_buffer, 2, false);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);

    tx_buffer[0] = BH1745NUC_CMD_MODE_CONTROL2;
    tx_buffer[1] = (bh_cfg->bh_rgbcvalid | bh_cfg->bh_rgbcenable) | bh_cfg->bh_adcgain;
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, BH1745NUC_DEFAULT_ADDRESS, tx_buffer, 2, false);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    
    tx_buffer[0] = BH1745NUC_CMD_MODE_CONTROL3;
    tx_buffer[1] = 0x02;
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, BH1745NUC_DEFAULT_ADDRESS, tx_buffer, 2, false);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    
    tx_buffer[0] = BH1745NUC_CMD_INTERRUPT;
    tx_buffer[1] = bh_cfg->bh_intstatus | bh_cfg->bh_intlatch | bh_cfg->bh_intsource | bh_cfg->bh_intenable;
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, BH1745NUC_DEFAULT_ADDRESS, tx_buffer, 2, false);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    
    tx_buffer[0] = BH1745NUC_CMD_PERSISTENCE;
    tx_buffer[1] = bh_cfg->bh_persistance;
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, BH1745NUC_DEFAULT_ADDRESS, tx_buffer, 2, false);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
}

static void bh1745nuc_read(/*int t, */bh1745nuc_config_t * bh_cfg) {
    
    ret_code_t err_code;
    
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, BH1745NUC_DEFAULT_ADDRESS, &bh_cfg->start_address, 1, true);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    
    uint8_t col_temp[8];
    m_xfer_done = false;
    err_code = nrf_drv_twi_rx(&m_twi, BH1745NUC_DEFAULT_ADDRESS, col_temp, 8);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);

    for (int i = 0; i <= 3; i++) {
        m_colour_sensor_data/*[t]*/[i]  = (uint16_t)(col_temp[(2*i)+1]) << 8;
        m_colour_sensor_data/*[t]*/[i] |= (uint16_t)(col_temp[2*i]); 
    }
}



#endif /* BH1745NUC_COLOUR_SENSOR_H */