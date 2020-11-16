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
// click status select list
typedef enum
{
  cs_NO_PRESS    = 0,
  cs_SHORT_PRESS = 1,
  cs_LONG_PRESS  = 2,
}click_status_t;

/// @brief struct which express button
typedef struct
{
  uint32_t       port;
  uint16_t       pin;
  uint32_t        counter;
  click_status_t status;
}button_t;

typedef enum
{
    e_button_err_ok,
    e_button_err_not_found,
    e_button_err_NULL
} button_err_t;

/**
  @brief set up button
  sets the button and prepares for work
  @param[in] ptr_button pointer to button_t type which express button
*/
button_err_t button_init (button_t *ptr_button);

/**
  @brief checks if the button is pressed
  checks whether the button is pressed if the button is pressed then increases the counter if not then decreases
  @param[in] ptr_button pointer to button_t type which express button
*/
button_err_t button_handler (button_t *ptr_button);

/**
  @brief return type of button pressing
  returns one of the pressure types listed in click_status_t
  @param[in] ptr_button pointer to button_t type which express button
  @return is_button_press return type of button pressing
*/
click_status_t button_get_press_type (button_t *ptr_button);

#ifdef __cplusplus
}
#endif
#endif /* SRC_LIB_DRIVERS_BUTTON_BUTTON_H_ */
