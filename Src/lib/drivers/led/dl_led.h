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

#ifndef DL_LED_H_
#define DL_LED_H_

/// @file stm32f4xx_hal.h - Library that give access to the stm HAL level.
#include "stm32f4xx_hal.h"

#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
  @brief turn on red led
  turn on red led
*/
void dl_led_rad_led_on ();

/**
  @brief turn off red led
  turn off red led
*/
void dl_led_rad_led_off ();


/**
  @brief turn on green led
  turn on green led
*/
void dl_led_green_led_on ();

/**
  @brief turn off green led
  turn off green led
*/
void dl_led_green_led_off ();

/**
  @brief turn on yellow led
  turn on yellow led
*/
void dl_led_yellow_led_on ();

/**
  @brief turn off yellow led
  turn off yellow led
*/
void dl_led_yellow_led_off ();

/**
  @brief turn on blue led
  turn on blue led
*/
void dl_led_blue_led_on ();

/**
  @brief turn off blue led
  turn off blue led
*/
void dl_led_blue_led_off ();

#ifdef __cplusplus
}
#endif
#endif /* LED_DRIVER_H_ */
