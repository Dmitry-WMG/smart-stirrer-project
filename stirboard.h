#ifndef STIRBOARD_H
#define STIRBOARD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "nrf_gpio.h"

// LED definitions for the stirboard
#define LEDS_NUMBER           1
#define LED_1                 NRF_GPIO_PIN_MAP(0, 30)
#define LED_START             LED_1
#define LED_STOP              LED_1
#define LEDS_ACTIVE_STATE     1
#define LEDS_LIST             { LED_1 }
#define LEDS_INV_MASK         LEDS_MASK
#define BSP_LED_0             30

#define BUTTONS_NUMBER        0
#define BUTTON_PULL           NRF_GPIO_PIN_PULLUP
#define BUTTONS_ACTIVE_STATE  0
#define BUTTONS_LIST          { }

// Stirboard mappings
#define STIRBOARD_SCL_PIN     NRF_GPIO_PIN_MAP(1, 4)
#define STIRBOARD_SDA_PIN     NRF_GPIO_PIN_MAP(1, 6)

#ifdef __cplusplus
}
#endif

#endif // PCA10056_H
