/*
 * dl_led.h
 *
 *  Created on: Oct 13, 2020
 *      Author: yevhen.surkov
 * @file
 * @brief Header file with function descriptions
 * dl_led.h - Library for interaction with leds on Driver level.
 *
 */

#ifndef LED_H_
#define LED_H_

/// @file stm32f4xx_hal.h - Library that give access to the stm HAL level.
#include "stm32f4xx_hal.h"

#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  e_err_ok,
  e_err_not_found,
}led_err_t;

typedef enum {
	e_led_off ,
	e_led_on
}led_ctrl_t;

typedef enum {
	e_led_status_disable ,
	e_led_status_enable
}led_status_t;

typedef enum {
  e_led_num_1,
  e_led_num_2,
  e_led_num_3,
  e_led_num_4,
  e_led_num
}led_num_t;

typedef struct{
	uint32_t      port;
	uint16_t      pin;
	led_num_t     num;
	led_status_t  status;
	led_ctrl_t    new_state;
	led_ctrl_t    curr_state;
}obj_led_t;

/**
  @brief function which init leds

  @return return type of error or ok if work correctly
*/
led_err_t led_init (void);

/**
  @brief function which deinit leds

  @return return type of error or ok if work correctly
*/
led_err_t led_deinit (void);

/**
  @brief function which turn off led or turn on led

  @param[in] objP_this instance of led which should   turn off or turn on

  @param[in] state indicate which action to perfom on or off

  @return return type of error or ok if work correctly
*/
led_err_t led_control (led_num_t e_LedNum, led_ctrl_t type);

/**
  @brief function which init led

  @param[in] objP_this instance of led which should  init

  @return return type of error or ok if work correctly
*/
led_err_t led_add(obj_led_t *objP_this);

/**
  @brief function which deinit led

  @param[in] objP_this instance of led which should  deinit

  @return return type of error or ok if work correctly
*/
led_err_t led_remove(obj_led_t *objP_this);

/**
  @brief function which change new_state of led instance

  @param[in][out] objP_this instance of led which should set

  @param[in] state indicate which state should set on or off

  @return return type of error or ok if work correctly
*/
led_err_t led_set_state(obj_led_t *objP_this, led_ctrl_t state);

#ifdef __cplusplus
}
#endif
#endif /* LED_DRIVER_H_ */
