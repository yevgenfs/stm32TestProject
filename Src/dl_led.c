/*
 * dl_led.c
 *
 *  Created on: Oct 13, 2020
 *      Author: yevhen.surkov
 *
 * @file
 * @brief Source file with function realization
 * dl_leds.сpp - Library realization  for interaction with leds on DL level.
 */

#include "dl_led.h"

void dl_led_rad_led_on ()
{
  HAL_GPIO_WritePin(RAD_LED_GPIO_Port, RAD_LED_Pin, SET);
}

void dl_led_rad_led_off ()
{
  HAL_GPIO_WritePin(RAD_LED_GPIO_Port, RAD_LED_Pin, RESET);
}

void dl_led_green_led_on ()
{
  HAL_GPIO_WritePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin, SET);
}

void dl_led_green_led_off ()
{
  HAL_GPIO_WritePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin, RESET);
}

void dl_led_yellow_led_on ()
{
  HAL_GPIO_WritePin(YELLOW_LED_GPIO_Port, YELLOW_LED_Pin, SET);
}

void dl_led_yellow_led_off ()
{
  HAL_GPIO_WritePin(YELLOW_LED_GPIO_Port, YELLOW_LED_Pin, RESET);
}

void dl_led_blue_led_on ()
{
  HAL_GPIO_WritePin(BLUE_LED_GPIO_Port, BLUE_LED_Pin, SET);
}

void dl_led_blue_led_off ()
{
  HAL_GPIO_WritePin(BLUE_LED_GPIO_Port, BLUE_LED_Pin, RESET);
}
