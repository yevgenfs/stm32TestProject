/*
 * button.h
 *
 *  Created on: 13 лист. 2020 р.
 *      Author: yevhen.surkov
 */

#ifndef SRC_LIB_DRIVERS_BUTTON_BUTTON_H_
#define SRC_LIB_DRIVERS_BUTTON_BUTTON_H_

#include "stm32f4xx_hal.h"

#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

/// @brief struct which express button
typedef struct
{
  uint32_t       port;
  uint16_t       pin;
}button_t;

typedef enum
{
    e_button_err_ok,
    e_button_err_not_found,
    e_button_err_callback_NULL_enter,
    e_button_err_zero_enter_to_timeout,
    e_button_err_number_more_than_limit_set_to_timeout,
    e_button_err_callback_exist,
    e_button_err_callback_already_NULL
} button_err_t;

typedef enum
{
  e_event_unpressed = 0,
  e_event_pressed,
  e_event_timeout,
} button_event_t;

typedef void (*buttonCb_t)(button_event_t event);

button_err_t button_init(void);

button_err_t button_deinit(void);

button_err_t button_reg_callback(buttonCb_t callback);

button_err_t button_unreg_callback(void);

void button_run(void);

button_err_t button_set_timeout(uint32_t timeout_ms);

uint32_t button_get_pressed_time(void);

#ifdef __cplusplus
}
#endif
#endif /* SRC_LIB_DRIVERS_BUTTON_BUTTON_H_ */
