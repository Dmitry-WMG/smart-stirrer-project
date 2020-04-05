#ifndef SS_ABSTRACT_TWI_H
#define SS_ABSTRACT_TWI_H

static void write_to_register(uint8_t dev_addr, uint8_t reg, uint8_t value) {
    ret_code_t err_code;
    uint8_t data[2] = { reg, value };
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, dev_addr, data, sizeof(data), false);
    // err_code = nrf_drv_twi_tx(&m_twi, dev_addr, data, 1, false);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
}

static void read_from_register(uint8_t dev_addr, uint8_t * reg, uint8_t data[]) {
    ret_code_t err_code;
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, dev_addr, reg, sizeof(reg), true);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
    m_xfer_done = false;
    err_code = nrf_drv_twi_rx(&m_twi, dev_addr, data, sizeof(*data));
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
}

#endif /* SS_ABSTRACT_TWI_H */