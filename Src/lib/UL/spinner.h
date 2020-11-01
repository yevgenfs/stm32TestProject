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

<<<<<<< Updated upstream
typedef enum {
	e_spiner_work_mode_pause,
	e_spiner_work_mode_run,
}spiner_work_mode;

led_err_t spinner_init (void);

led_err_t spinner_run (void);

led_err_t spinner_deinit (void);
=======
typedef enum
{
    e_spiner_work_mode_pause = 0,
    e_spiner_work_mode_run,
} spiner_work_mode_t;

typedef enum
{
    e_spiner_ctrl_insert = 0,
    e_spiner_ctrl_remove
} e_spiner_ctrl_t;

typedef enum
{
    e_spinner_err_ok,
    e_spinner_err_not_found,
    e_spinner_err_not_NULL,
    e_spinner_err_not_add_to_queue
} e_spinner_err_t;

typedef struct
{
    obj_led_t       *objP_led;
    e_spiner_ctrl_t cmd;
} spinner_ctrl_t;

e_spinner_err_t spinner_init(void);

e_spinner_err_t spinner_run(void);

e_spinner_err_t spinner_deinit(void);
>>>>>>> Stashed changes

#ifdef __cplusplus
}
#endif
#endif /* SRC_LIB_UL_SPINNER_H_ */
