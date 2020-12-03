/*
 * spinner.h
 */

#ifndef SRC_LIB_UL_SPINNER_H_
#define SRC_LIB_UL_SPINNER_H_

/// @file stm32f4xx_hal.h - Library that give access to the stm HAL level.
#include "stm32f4xx_hal.h"

#include "main.h"
#include "../../drivers/led/led.h"


#ifdef __cplusplus
extern "C" {
#endif

/// @brief spinner_state_t enum which express spinner state machine
typedef enum
{
    e_spinner_state_pause = 0,
    e_spinner_state_run,
    e_spinner_state_process_cmd,
} spinner_state_t;

/// @brief e_spinner_ctrl_t enum which express should led add in spinner or remove from spinner
typedef enum
{
    e_spinner_ctrl_insert = 0,
    e_spinner_ctrl_remove
} e_spinner_ctrl_t;

/// @brief spinner_ctrl_t struct which express spinner instance which save in queue
typedef struct
{
    led_num_t       led;
    e_spinner_ctrl_t cmd;
}spinner_ctrl_t;

/// @brief e_spinner_err_t enum which express spinner erorrs
typedef enum
{
    e_spinner_err_ok,
    e_spinner_err_not_found,
    e_spinner_err_not_init,
    e_spinner_err_not_add_to_queue,
    e_spinner_err_invalid_argument
} e_spinner_err_t;


/**
 @brief function which init spinner

 @return return type of error or ok if work correctly
 */
e_spinner_err_t spinner_init(void);

/**
 @brief function which deinit spinner

 @return return type of error or ok if work correctly
 */
e_spinner_err_t spinner_deinit(void);

/**
 @brief function which start spinner

 @return return type of error or ok if work correctly
 */
e_spinner_err_t spinner_start(void);

/**
 @brief function which stop spinner

 @return return type of error or ok if work correctly
 */
e_spinner_err_t spinner_stop(void);

/**
 @brief function which insert led in spinner

 @param[in] e_LedNum indicate which led should insert

 @return return type of error or ok if work correctly
 */
e_spinner_err_t spinner_insert_led(led_num_t e_LedNum);

/**
 @brief function which remove led from spinner

 @param[in] e_LedNum indicate which led should remove

 @return return type of error or ok if work correctly
 */
e_spinner_err_t spinner_remove_led(led_num_t e_LedNum);

/**
 @brief function which run spinner

 @return return type of error or ok if work correctly
 */
e_spinner_err_t spinner_run(void);

/**
 @brief function which set spinner period in ms

 @return return type of error or ok if work correctly
 */
e_spinner_err_t set_spinner_period_ms(uint32_t period);

#ifdef __cplusplus
}
#endif
#endif /* SRC_LIB_UL_SPINNER_H_ */
