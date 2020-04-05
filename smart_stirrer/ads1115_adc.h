#ifndef ADS1115_ADC_H
#define ADS1115_ADC_H

#define ADS1115_ADDRESS (0x48)
#define ADS1115_CONVERSIONDELAY (8)

#define ADS1115_REG_POINTER_MASK      (0x03)
#define ADS1115_REG_POINTER_CONVERT   (0x00)
#define ADS1115_REG_POINTER_CONFIG    (0x01)
#define ADS1115_REG_POINTER_LOWTHRESH (0x02)
#define ADS1115_REG_POINTER_HITHRESH  (0x03)

#define ADS1115_REG_CONFIG_OS_MASK    (0x8000)
#define ADS1115_REG_CONFIG_OS_SINGLE  (0x8000)   // Write: Set to start a single-conversion
#define ADS1115_REG_CONFIG_OS_BUSY    (0x0000)     // Read: Bit = 0 when conversion is in progress
#define ADS1115_REG_CONFIG_OS_NOTBUSY (0x8000)  // Read: Bit = 1 when device is not converting

#define ADS1115_REG_CONFIG_MUX_MASK     (0x7000)
#define ADS1115_REG_CONFIG_MUX_DIFF_0_1 (0x0000)  // Differential P = AIN0, N = AIN1 (default)
#define ADS1115_REG_CONFIG_MUX_DIFF_0_3 (0x1000)  // Differential P = AIN0, N = AIN3
#define ADS1115_REG_CONFIG_MUX_DIFF_1_3 (0x2000)  // Differential P = AIN1, N = AIN3
#define ADS1115_REG_CONFIG_MUX_DIFF_2_3 (0x3000)  // Differential P = AIN2, N = AIN3
#define ADS1115_REG_CONFIG_MUX_SINGLE_0 (0x4000)  // Single-ended AIN0
#define ADS1115_REG_CONFIG_MUX_SINGLE_1 (0x5000)  // Single-ended AIN1
#define ADS1115_REG_CONFIG_MUX_SINGLE_2 (0x6000)  // Single-ended AIN2
#define ADS1115_REG_CONFIG_MUX_SINGLE_3 (0x7000)  // Single-ended AIN3

#define ADS1115_REG_CONFIG_PGA_MASK   (0x0E00)
#define ADS1115_REG_CONFIG_PGA_6_144V (0x0000)  // +/-6.144V range = Gain 2/3
#define ADS1115_REG_CONFIG_PGA_4_096V (0x0200)  // +/-4.096V range = Gain 1
#define ADS1115_REG_CONFIG_PGA_2_048V (0x0400)  // +/-2.048V range = Gain 2 (default)
#define ADS1115_REG_CONFIG_PGA_1_024V (0x0600)  // +/-1.024V range = Gain 4
#define ADS1115_REG_CONFIG_PGA_0_512V (0x0800)  // +/-0.512V range = Gain 8
#define ADS1115_REG_CONFIG_PGA_0_256V (0x0A00)  // +/-0.256V range = Gain 16

#define ADS1115_REG_CONFIG_MODE_MASK   (0x0100)
#define ADS1115_REG_CONFIG_MODE_CONTIN (0x0000)  // Continuous conversion mode
#define ADS1115_REG_CONFIG_MODE_SINGLE (0x0100)  // Power-down single-shot mode (default)

#define ADS1115_REG_CONFIG_DR_MASK    (0x00E0)  
#define ADS1115_REG_CONFIG_DR_128SPS  (0x0000)  // 128 samples per second
#define ADS1115_REG_CONFIG_DR_250SPS  (0x0020)  // 250 samples per second
#define ADS1115_REG_CONFIG_DR_490SPS  (0x0040)  // 490 samples per second
#define ADS1115_REG_CONFIG_DR_920SPS  (0x0060)  // 920 samples per second
#define ADS1115_REG_CONFIG_DR_1600SPS (0x0080)  // 1600 samples per second (default)
#define ADS1115_REG_CONFIG_DR_2400SPS (0x00A0)  // 2400 samples per second
#define ADS1115_REG_CONFIG_DR_3300SPS (0x00C0)  // 3300 samples per second

#define ADS1115_REG_CONFIG_CMODE_MASK   (0x0010)
#define ADS1115_REG_CONFIG_CMODE_TRAD   (0x0000)  // Traditional comparator with hysteresis (default)
#define ADS1115_REG_CONFIG_CMODE_WINDOW (0x0010)  // Window comparator

#define ADS1115_REG_CONFIG_CPOL_MASK    (0x0008)
#define ADS1115_REG_CONFIG_CPOL_ACTVLOW (0x0000)  // ALERT/RDY pin is low when active (default)
#define ADS1115_REG_CONFIG_CPOL_ACTVHI  (0x0008)  // ALERT/RDY pin is high when active

#define ADS1115_REG_CONFIG_CLAT_MASK   (0x0004)  // Determines if ALERT/RDY pin latches once asserted
#define ADS1115_REG_CONFIG_CLAT_NONLAT (0x0000)  // Non-latching comparator (default)
#define ADS1115_REG_CONFIG_CLAT_LATCH  (0x0004)  // Latching comparator

#define ADS1115_REG_CONFIG_CQUE_MASK  (0x0003)
#define ADS1115_REG_CONFIG_CQUE_1CONV (0x0000)  // Assert ALERT/RDY after one conversions
#define ADS1115_REG_CONFIG_CQUE_2CONV (0x0001)  // Assert ALERT/RDY after two conversions
#define ADS1115_REG_CONFIG_CQUE_4CONV (0x0002)  // Assert ALERT/RDY after four conversions
#define ADS1115_REG_CONFIG_CQUE_NONE  (0x0003)  // Disable the comparator and put ALERT/RDY in high state (default)

typedef enum {
    GAIN_TWOTHIRDS = ADS1115_REG_CONFIG_PGA_6_144V,
    GAIN_ONE       = ADS1115_REG_CONFIG_PGA_4_096V,
    GAIN_TWO       = ADS1115_REG_CONFIG_PGA_2_048V,
    GAIN_FOUR      = ADS1115_REG_CONFIG_PGA_1_024V,
    GAIN_EIGHT     = ADS1115_REG_CONFIG_PGA_0_512V,
    GAIN_SIXTEEN   = ADS1115_REG_CONFIG_PGA_0_256V
} adsGain_t;

typedef struct {
    uint8_t m_i2cAddress;
    uint8_t m_conversionDelay;
    uint8_t start_address;
    uint16_t std_config;
    adsGain_t m_gain;
} ads1115_config_t;


ads1115_config_t ads1115_config;
uint16_t m_adc_data[4][3];

static void ads1115_adc_init(ads1115_config_t * ads_cfg) {
    ads_cfg->m_i2cAddress = ADS1115_ADDRESS;
    ads_cfg->m_conversionDelay = ADS1115_CONVERSIONDELAY;
    ads_cfg->start_address = ADS1115_REG_POINTER_CONVERT;
    ads_cfg->m_gain = GAIN_TWOTHIRDS;
    ads_cfg->std_config = 
        ADS1115_REG_CONFIG_CQUE_NONE     | // Disable the comparator
        ADS1115_REG_CONFIG_CLAT_NONLAT   | // Non-latching
        ADS1115_REG_CONFIG_CPOL_ACTVLOW  | // Alert/Rdy active low
        ADS1115_REG_CONFIG_CMODE_TRAD    | // Traditional comparator
        ADS1115_REG_CONFIG_DR_1600SPS    | // 1600 samples per second
        ADS1115_REG_CONFIG_MODE_SINGLE;    // Single-shot mode
}

static void ads1115_read_single_ended(int t, ads1115_config_t * ads_cfg, uint8_t channel) {
    
    if (channel >= 3) { return; }
    uint16_t config = (uint16_t)(ads_cfg->std_config) | (uint16_t)(ads_cfg->m_gain);

    // Set PGA/voltage range and single-ended input channel
    switch (channel) {
        case 0: config |= ADS1115_REG_CONFIG_MUX_SINGLE_0; break;
        case 1: config |= ADS1115_REG_CONFIG_MUX_SINGLE_1; break;
        case 2: config |= ADS1115_REG_CONFIG_MUX_SINGLE_2; break;
    }

    config |= ADS1115_REG_CONFIG_OS_SINGLE; // Set "start single-conversion" bit

    ret_code_t err_code;
    
    uint8_t cfg_tx_buffer[3] = { 0, 0, 0 };
    cfg_tx_buffer[0] = ADS1115_REG_POINTER_CONFIG;
    cfg_tx_buffer[1] = (uint8_t)(config >> 8);
    cfg_tx_buffer[2] = (uint8_t)(config & 0xFF);
    
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, ADS1115_ADDRESS, cfg_tx_buffer, 3, false);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    
    nrf_delay_ms(8);  // wait for the conversion delay
    
    uint8_t adc_temp_data[2] = { 0, 0 };
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, ADS1115_ADDRESS, &ads1115_config.start_address, 1, true);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    
    m_xfer_done = false;
    err_code = nrf_drv_twi_rx(&m_twi, ADS1115_ADDRESS, adc_temp_data, 2);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);

    m_adc_data[t][channel]  = ((uint16_t)(adc_temp_data[0]) & 0x7F) << 8;
    m_adc_data[t][channel] |= (uint16_t)(adc_temp_data[1]);
}

uint16_t ads_format_raw(uint8_t high_byte, uint8_t low_byte) {
    uint16_t val = (uint16_t)(high_byte) << 8;
    val |= (uint16_t)(low_byte);
    // val &= (uint16_t)(0x7FFF);
    return val;
}


float ads_get_voltage(ads1115_config_t * ads_cfg, uint16_t raw_value) {
    float val = 0.1875f * (float)(raw_value);
    val /= 1000.0;
    return val;
}


#endif /* ADS1115_ADC_H */ 