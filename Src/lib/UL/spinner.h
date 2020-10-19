/*
 * spinner.h
 *
 *  Created on: 19 жовт. 2020 р.
 *      Author: yevhen.surkov
 */

#ifndef SRC_LIB_UL_SPINNER_H_
#define SRC_LIB_UL_SPINNER_H_


/// @file stm32f4xx_hal.h - Library that give access to the stm HAL level.
#include "stm32f4xx_hal.h"

#include "main.h"
#include "lib/drivers/led/led.h"
#include "lib/utils/queue.h"

#ifdef __cplusplus
extern "C" {
#endif

led_err_t spinner_init (void);

led_err_t spinner_run (void);

led_err_t spinner_enable (led_num_t e_LedNum);

led_err_t led_disable (led_num_t e_LedNum);

led_err_t spinner_deinit (void);

#ifdef __cplusplus
}
#endif
#endif /* SRC_LIB_UL_SPINNER_H_ */
