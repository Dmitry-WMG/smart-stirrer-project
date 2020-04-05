// #define DEBUG_MODE

#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "boards.h"
#include "nordic_common.h"
#include "nrf.h"
#include "ble_hci.h"
#include "ble_advdata.h"
#include "ble_advertising.h"
#include "ble_conn_params.h"
#include "nrf_sdh.h"
#include "nrf_sdh_soc.h"
#include "nrf_sdh_ble.h"
#include "nrf_ble_gatt.h"
#include "nrf_ble_qwr.h"
#include "nrf_delay.h"
#include "app_timer.h"
#include "app_error.h"
#include "ble_nus.h"
#include "app_uart.h"
#include "app_util_platform.h"
#include "bsp_btn_ble.h"
#include "nrf_pwr_mgmt.h"
#include "nrf_drv_twi.h"

#if defined (UART_PRESENT)
#include "nrf_uart.h"
#endif
#if defined (UARTE_PRESENT)
#include "nrf_uarte.h"
#endif

#if defined(DEBUG_MODE)
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#endif

APP_TIMER_DEF(m_imu_timer);
APP_TIMER_DEF(m_start_timer); 
static volatile bool m_xfer_done = false;
static const nrf_drv_twi_t m_twi = NRF_DRV_TWI_INSTANCE(0);

#include "lsm9ds1_imu.h"

// BLE-specific definitions
#define DEVICE_NAME "Smart Stirrer Visc 70"
#define APP_BLE_CONN_CFG_TAG 1
#define NUS_SERVICE_UUID_TYPE BLE_UUID_TYPE_VENDOR_BEGIN
#define APP_BLE_OBSERVER_PRIO 3
#define APP_ADV_INTERVAL 64
#define APP_ADV_DURATION 18000
#define MIN_CONN_INTERVAL MSEC_TO_UNITS(20, UNIT_1_25_MS)
#define MAX_CONN_INTERVAL MSEC_TO_UNITS(75, UNIT_1_25_MS)
#define SLAVE_LATENCY 0
#define CONN_SUP_TIMEOUT MSEC_TO_UNITS(4000, UNIT_10_MS)
#define FIRST_CONN_PARAMS_UPDATE_DELAY APP_TIMER_TICKS(5000)
#define NEXT_CONN_PARAMS_UPDATE_DELAY APP_TIMER_TICKS(30000)
#define MAX_CONN_PARAMS_UPDATE_COUNT 3
#define DEAD_BEEF 0xDEADBEEF
#define UART_TX_BUF_SIZE 256                                         
#define UART_RX_BUF_SIZE 256 

BLE_NUS_DEF(m_nus, NRF_SDH_BLE_TOTAL_LINK_COUNT);                                   
NRF_BLE_GATT_DEF(m_gatt);                                                           
NRF_BLE_QWR_DEF(m_qwr);                                                             
BLE_ADVERTISING_DEF(m_advertising);
                                               
static uint16_t m_conn_handle = BLE_CONN_HANDLE_INVALID;                 
static uint16_t m_ble_nus_max_data_len = BLE_GATT_ATT_MTU_DEFAULT - 3;           
static ble_uuid_t m_adv_uuids[] = { { BLE_UUID_NUS_SERVICE, NUS_SERVICE_UUID_TYPE } };

static void gap_params_init(void) {
    ble_gap_conn_params_t gap_conn_params;
    ble_gap_conn_sec_mode_t sec_mode;
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&sec_mode);
    ret_code_t err_code = sd_ble_gap_device_name_set(&sec_mode, 
        (const uint8_t *)DEVICE_NAME, strlen(DEVICE_NAME));
    APP_ERROR_CHECK(err_code);
    memset(&gap_conn_params, 0, sizeof(gap_conn_params));
    gap_conn_params.min_conn_interval = MIN_CONN_INTERVAL;
    gap_conn_params.max_conn_interval = MAX_CONN_INTERVAL;
    gap_conn_params.slave_latency = SLAVE_LATENCY;
    gap_conn_params.conn_sup_timeout = CONN_SUP_TIMEOUT;
    err_code = sd_ble_gap_ppcp_set(&gap_conn_params);
    APP_ERROR_CHECK(err_code);
}

static void sleep_mode_enter(void) {
    ret_code_t err_code = bsp_indication_set(BSP_INDICATE_IDLE);
    APP_ERROR_CHECK(err_code);
    err_code = sd_power_system_off();
    APP_ERROR_CHECK(err_code);
}

static void stop_all_timers(void) {
    ret_code_t err_code = app_timer_stop(m_imu_timer); 
    APP_ERROR_CHECK(err_code);
}

static void nrf_qwr_error_handler(uint32_t nrf_error) {
    stop_all_timers();
    APP_ERROR_HANDLER(nrf_error);
}

static void nus_data_handler(ble_nus_evt_t * p_evt);

static void services_init(void) {
    ret_code_t err_code;
    nrf_ble_qwr_init_t qwr_init = { 0 };
    qwr_init.error_handler = nrf_qwr_error_handler;
    err_code = nrf_ble_qwr_init(&m_qwr, &qwr_init);
    APP_ERROR_CHECK(err_code);

    ble_nus_init_t nus_init;
    memset(&nus_init, 0, sizeof(nus_init));
    nus_init.data_handler = nus_data_handler;
    err_code = ble_nus_init(&m_nus, &nus_init);
    APP_ERROR_CHECK(err_code);
}

static void on_conn_params_evt(ble_conn_params_evt_t * p_evt) {
    ret_code_t err_code; 
    if (p_evt->evt_type == BLE_CONN_PARAMS_EVT_FAILED) {
        stop_all_timers();
        err_code = sd_ble_gap_disconnect(m_conn_handle, BLE_HCI_CONN_INTERVAL_UNACCEPTABLE);
        APP_ERROR_CHECK(err_code);
    }
}

static void conn_params_error_handler(uint32_t nrf_error) {
    stop_all_timers(); // NOTE: does this function still work if the timers aren't on?
    APP_ERROR_HANDLER(nrf_error);
}

static void conn_params_init(void) {
    ret_code_t err_code;
    ble_conn_params_init_t cp_init;
    memset(&cp_init, 0, sizeof(cp_init));
    cp_init.p_conn_params = NULL;
    cp_init.first_conn_params_update_delay = FIRST_CONN_PARAMS_UPDATE_DELAY;
    cp_init.next_conn_params_update_delay = NEXT_CONN_PARAMS_UPDATE_DELAY;
    cp_init.max_conn_params_update_count = MAX_CONN_PARAMS_UPDATE_COUNT;
    cp_init.start_on_notify_cccd_handle = BLE_GATT_HANDLE_INVALID;
    cp_init.disconnect_on_fail = false;
    cp_init.evt_handler = on_conn_params_evt; // called to disconnect if connection fails 
    cp_init.error_handler = conn_params_error_handler; // stops timers 
    err_code = ble_conn_params_init(&cp_init);
    APP_ERROR_CHECK(err_code);
}

static void on_adv_evt(ble_adv_evt_t ble_adv_evt) {
    ret_code_t err_code;
    switch (ble_adv_evt) {
        case BLE_ADV_EVT_FAST:
            // NOTE: See components --> libraries --> bsp for the definitions
            err_code = bsp_indication_set(BSP_INDICATE_ADVERTISING);
            APP_ERROR_CHECK(err_code);
            break; // BLE_ADV_EVT_FAST
        case BLE_ADV_EVT_IDLE:
            sleep_mode_enter();
            break; // BLE_ADV_EVT_IDLE 
        default:
            // No implementation required.
            break;
    }
}

static void ble_evt_handler(ble_evt_t const * p_ble_evt, void * p_context) {
    ret_code_t err_code;
    switch (p_ble_evt->header.evt_id) {
        case BLE_GAP_EVT_CONNECTED:
#if defined(DEBUG_MODE)
            NRF_LOG_INFO("Connected.");
#endif
            err_code = bsp_indication_set(BSP_INDICATE_IDLE);
            APP_ERROR_CHECK(err_code);
            bsp_board_led_off(BSP_BOARD_LED_0);
            m_conn_handle = p_ble_evt->evt.gap_evt.conn_handle;
            err_code = nrf_ble_qwr_conn_handle_assign(&m_qwr, m_conn_handle);
            APP_ERROR_CHECK(err_code);
            err_code = app_timer_start(m_start_timer, APP_TIMER_TICKS(1000), NULL);
            APP_ERROR_CHECK(err_code);
            break; // BLE_GAP_EVT_CONNECTED 
        case BLE_GAP_EVT_DISCONNECTED:
#if defined(DEBUG_MODE)
            NRF_LOG_INFO("Disconnected.");
#endif
            m_conn_handle = BLE_CONN_HANDLE_INVALID;
            stop_all_timers();
            break; // BLE_GAP_EVT_DISCONNECTED 
        case BLE_GAP_EVT_PHY_UPDATE_REQUEST: {
#if defined(DEBUG_MODE)
            NRF_LOG_DEBUG("PHY update request.");
#endif
            ble_gap_phys_t const phys = {
                .rx_phys = BLE_GAP_PHY_AUTO, .tx_phys = BLE_GAP_PHY_AUTO,
            };
            err_code = sd_ble_gap_phy_update(p_ble_evt->evt.gap_evt.conn_handle, &phys);
            APP_ERROR_CHECK(err_code);
        } break; // BLE_GAP_EVT_PHY_UPDATE_REQUEST 
        case BLE_GAP_EVT_SEC_PARAMS_REQUEST: // Pairing not supported
            err_code = sd_ble_gap_sec_params_reply(m_conn_handle, 
                BLE_GAP_SEC_STATUS_PAIRING_NOT_SUPP, NULL, NULL);
            APP_ERROR_CHECK(err_code);
            break; // BLE_GAP_EVT_SEC_PARAMS_REQUEST 
        case BLE_GATTS_EVT_SYS_ATTR_MISSING:
            err_code = sd_ble_gatts_sys_attr_set(m_conn_handle, NULL, 0, 0);
            APP_ERROR_CHECK(err_code);
            break; // BLE_GATTS_EVT_SYS_ATTR_MISSING 
        case BLE_GATTC_EVT_TIMEOUT:
            stop_all_timers();
            err_code = sd_ble_gap_disconnect(p_ble_evt->evt.gattc_evt.conn_handle,
                BLE_HCI_REMOTE_USER_TERMINATED_CONNECTION);
            APP_ERROR_CHECK(err_code);
            break; // BLE_GATTC_EVT_TIMEOUT
        case BLE_GATTS_EVT_TIMEOUT:
            stop_all_timers();
            err_code = sd_ble_gap_disconnect(p_ble_evt->evt.gatts_evt.conn_handle,
                BLE_HCI_REMOTE_USER_TERMINATED_CONNECTION);
            APP_ERROR_CHECK(err_code);
            break; // BLE_GATTS_EVT_TIMEOUT
        default: break;
    }
}


static void ble_stack_init(void) {
    ret_code_t err_code;
    err_code = nrf_sdh_enable_request();
    APP_ERROR_CHECK(err_code);
    uint32_t ram_start = 0;
    err_code = nrf_sdh_ble_default_cfg_set(APP_BLE_CONN_CFG_TAG, &ram_start);
    APP_ERROR_CHECK(err_code);
    err_code = nrf_sdh_ble_enable(&ram_start); // Enable BLE stack.
    APP_ERROR_CHECK(err_code);
    NRF_SDH_BLE_OBSERVER(m_ble_observer, APP_BLE_OBSERVER_PRIO, ble_evt_handler, NULL);
}


void gatt_evt_handler(nrf_ble_gatt_t * p_gatt, nrf_ble_gatt_evt_t const * p_evt) {
    if ((m_conn_handle == p_evt->conn_handle) && 
        (p_evt->evt_id == NRF_BLE_GATT_EVT_ATT_MTU_UPDATED)) {
        m_ble_nus_max_data_len = p_evt->params.att_mtu_effective - OPCODE_LENGTH - HANDLE_LENGTH;
#if defined(DEBUG_MODE)
        NRF_LOG_INFO("Data len is set to 0x%X(%d)", m_ble_nus_max_data_len, m_ble_nus_max_data_len);
#endif
    }
#if defined(DEBUG_MODE)
    NRF_LOG_DEBUG("ATT MTU exchange completed. central 0x%x peripheral 0x%x",
        p_gatt->att_mtu_desired_central, p_gatt->att_mtu_desired_periph);
#endif
}

void gatt_init(void) {
    ret_code_t err_code = nrf_ble_gatt_init(&m_gatt, gatt_evt_handler);
    APP_ERROR_CHECK(err_code);
    err_code = nrf_ble_gatt_att_mtu_periph_set(&m_gatt, NRF_SDH_BLE_GATT_MAX_MTU_SIZE);
    APP_ERROR_CHECK(err_code);
}

static void advertising_init(void) {
    ble_advertising_init_t init;
    memset(&init, 0, sizeof(init));
    init.advdata.name_type = BLE_ADVDATA_FULL_NAME;
    init.advdata.include_appearance = false;
    init.advdata.flags = BLE_GAP_ADV_FLAGS_LE_ONLY_LIMITED_DISC_MODE;
    init.srdata.uuids_complete.uuid_cnt = sizeof(m_adv_uuids) / sizeof(m_adv_uuids[0]);
    init.srdata.uuids_complete.p_uuids = m_adv_uuids;
    init.config.ble_adv_fast_enabled = true;
    init.config.ble_adv_fast_interval = APP_ADV_INTERVAL;
    init.config.ble_adv_fast_timeout = APP_ADV_DURATION;
    init.evt_handler = on_adv_evt;
    ret_code_t err_code = ble_advertising_init(&m_advertising, &init);
    APP_ERROR_CHECK(err_code);
    ble_advertising_conn_cfg_tag_set(&m_advertising, APP_BLE_CONN_CFG_TAG);
}

static void advertising_start(void) {
    ret_code_t err_code = ble_advertising_start(&m_advertising, BLE_ADV_MODE_FAST);
    APP_ERROR_CHECK(err_code);
}

void bsp_event_handler(bsp_event_t event) {
    ret_code_t err_code;
    switch (event) {
        case BSP_EVENT_SLEEP:
            sleep_mode_enter();
            break; // BSP_EVENT_SLEEP 
        case BSP_EVENT_DISCONNECT:
            err_code = sd_ble_gap_disconnect(m_conn_handle, 
                BLE_HCI_REMOTE_USER_TERMINATED_CONNECTION);
            if (err_code != NRF_ERROR_INVALID_STATE) { APP_ERROR_CHECK(err_code); }
            break; // BSP_EVENT_DISCONNECT
        case BSP_EVENT_WHITELIST_OFF:
            if (m_conn_handle == BLE_CONN_HANDLE_INVALID) {
                err_code = ble_advertising_restart_without_whitelist(&m_advertising);
                if (err_code != NRF_ERROR_INVALID_STATE) { APP_ERROR_CHECK(err_code); }
            } break; // BSP_EVENT_WHITELIST_OFF 
        default:
            break;
    }
}

static void leds_init() {
    bsp_event_t startup_event;
    ret_code_t err_code = bsp_init(BSP_INIT_LEDS, bsp_event_handler);
    APP_ERROR_CHECK(err_code);
}

#if defined(DEBUG_MODE)
static void log_init(void) {
    ret_code_t err_code = NRF_LOG_INIT(NULL);
    APP_ERROR_CHECK(err_code);
    NRF_LOG_DEFAULT_BACKENDS_INIT();
}
#endif

static void power_management_init(void) {
    ret_code_t err_code = nrf_pwr_mgmt_init();
    APP_ERROR_CHECK(err_code);
}

void assert_nrf_callback(uint16_t line_num, const uint8_t * p_file_name) {
    app_error_handler(DEAD_BEEF, line_num, p_file_name);
}

void twi_callback(nrf_drv_twi_evt_t const * p_event, void * p_context) {
    switch (p_event->type) {
        case NRF_DRV_TWI_EVT_DONE:
            m_xfer_done = true;
            break;
        default: break;
    }
}

static void twi_init(void) {
    const nrf_drv_twi_config_t twi_config = {
        .scl = STIRBOARD_SCL_PIN,
        .sda = STIRBOARD_SDA_PIN,
        .frequency = NRF_DRV_TWI_FREQ_100K,
        .interrupt_priority = APP_IRQ_PRIORITY_HIGH,
        .clear_bus_init = false  
    };
    ret_code_t err_code = nrf_drv_twi_init(&m_twi, &twi_config, twi_callback, NULL);
    APP_ERROR_CHECK(err_code);
    nrf_drv_twi_enable(&m_twi);
}

void imu_timer_handler(void * p_context) {
    lsm9ds1_read(&lsm9ds1_config);
#if defined(DEBUG_MODE)
    NRF_LOG_INFO("Accel: %d %d %d", m_imu_raw[0], m_imu_raw[1], m_imu_raw[2]);
    NRF_LOG_INFO("Gyro:  %d %d %d", m_imu_raw[3], m_imu_raw[4], m_imu_raw[5]);
#endif
    uint16_t imu[7] = { 0, 0, 0, 0, 0, 0, 0 };
    uint8_t data_array[14];
    for (int i = 0; i <= 6; i++) {
        imu[i] = m_imu_raw[i]; // imu[i] = 32768 + m_imu_raw[i];
        data_array[(2*i)] = imu[i] >> 8; // high byte first
        data_array[(2*i)+1] = imu[i] & 0xFF; // then low byte
    }
    uint16_t length = sizeof(data_array);
    ret_code_t err_code = ble_nus_data_send(&m_nus, data_array, &length, m_conn_handle);
    APP_ERROR_CHECK(err_code);
}


void start_data_handler(void * p_context) {
    ret_code_t err_code = app_timer_start(m_imu_timer, APP_TIMER_TICKS(70), NULL);
    APP_ERROR_CHECK(err_code);
}

static void timers_init(void) {
    ret_code_t err_code = app_timer_init();
    APP_ERROR_CHECK(err_code);
    err_code = app_timer_create(&m_start_timer, APP_TIMER_MODE_SINGLE_SHOT, start_data_handler);
    APP_ERROR_CHECK(err_code);
    err_code = app_timer_create(&m_imu_timer, APP_TIMER_MODE_REPEATED, imu_timer_handler);
    APP_ERROR_CHECK(err_code);
}

static void nus_data_handler(ble_nus_evt_t * p_evt) { }


int main(void) {

#if defined(DEBUG_MODE)
    log_init(); 
#endif
    timers_init();
    leds_init(); 
    power_management_init();

    ble_stack_init();
    gap_params_init();
    gatt_init();
    services_init();
    advertising_init();
    conn_params_init();

    twi_init();
    lsm9ds1_imu_init(&lsm9ds1_config);

#if defined(DEBUG_MODE)
    NRF_LOG_INFO("Smart Stirrer initialised.");
#endif
    advertising_start();
    
    while (true) {
        // if (NRF_LOG_PROCESS() == false) {
            nrf_pwr_mgmt_run();
        // }
    }
}
// *************************************************************************************************
