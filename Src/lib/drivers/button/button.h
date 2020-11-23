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

/// @brief button_err_t enum which express button erorrs
typedef enum
{
    e_button_err_ok,
    e_button_err_not_found,
    e_button_err_invalid_argument,
    e_button_err_callback_exist,
    e_button_err_callback_already_NULL
} button_err_t;

/// @brief button_err_t enum which express button events
typedef enum
{
  e_event_unpressed = 0,
  e_event_pressed,
  e_event_timeout,
} button_event_t;

/// @brief buttonCb_t type which contain function for callback
typedef void (*buttonCb_t)(button_event_t event);

/**
 @brief function which init button

 @return return type of error or ok if work correctly
 */
button_err_t button_init(void);

/**
 @brief function which deinit button

 @return return type of error or ok if work correctly
 */
button_err_t button_deinit(void);

/**
 @brief function which reg  callback for button

 @param[in] callback contains contains callback which should be reg

 @return return type of error or ok if work correctly
 */
button_err_t button_reg_callback(buttonCb_t callback);

/**
 @brief function which unreg  callback for button

 @return return type of error or ok if work correctly
 */
button_err_t button_unreg_callback(void);

/**
 @brief function which run button
 */
void button_run(void);

/**
 @brief function which set  timeout for button and add debouncer for this time

 @param[in] timeout_ms contains time in ms which should set

 @return return type of error or ok if work correctly
 */
button_err_t button_set_timeout(uint32_t timeout_ms);

/**
 @brief function which return timeout for button with debouncer

 @return return  timeout for button
 */
uint32_t button_get_timeout_with_debouncer(void);

/**
 @brief function which return how much time button press

 @return return how much time button press
 */
uint32_t button_get_pressed_time(void);

/**
 @brief function which return how much time button press

 @return return how much time button press
 */
button_err_t button_pressed_time_reset(void);

#ifdef __cplusplus
}
#endif
#endif /* SRC_LIB_DRIVERS_BUTTON_BUTTON_H_ */
