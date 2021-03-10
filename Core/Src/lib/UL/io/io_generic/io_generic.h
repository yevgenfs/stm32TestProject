/*
 * io_generic.h
 *
 *  Created on: 18 січ. 2021 р.
 *      Author: yevhen.surkov
 */

#ifndef SRC_LIB_UL_IO_GENERIC_IO_GENERIC_H_
#define SRC_LIB_UL_IO_GENERIC_IO_GENERIC_H_

#include "lib/UL/spinner/spinner.h"
#include "lib/UL/io/io_package_convertor/io_package_convertor.h"

#ifdef __cplusplus
extern "C" {
#endif

/// @brief e_io_generic_err_t enum which express io_generic events
typedef enum
{
    e_io_generic_event_data_ready_to_receive,
    e_io_generic_event_data_received,
}e_io_generic_event_t;

/// @brief io_genericCb_t type which contain function for callback
typedef void (*io_genericCb_t)(e_io_generic_event_t event);

/// @brief e_io_generic_err_t enum which express io_generic errors
typedef enum
{
    e_io_generic_err_ok,
    e_io_generic_err_not_found,
    e_io_generic_err_not_init,
    e_io_generic_err_not_deinit,
    e_io_generic_err_invalid_argument
} e_io_generic_err_t;

/// @brief io_generic_config_t struct which contain protocol functions for io_generic
typedef struct
{
    void (*send_function)(uint8_t *send_message, uint8_t lenght);
    void (*receive_function)(uint8_t *receive_message, uint8_t lenght);
    void (*run_function)();
    void (*init_function)();
    void (*convert_receive_package)(uint8_t *receive_message, uint8_t array_size, receive_package_t *receive_package);
    void (*convert_message_for_send)(uint8_t *send_message, uint8_t size,
            led_num_t led_num, led_ctrl_t led_state);
    void (*reg_callback)(io_genericCb_t callback);
    void (*unreg_callback)(void);
} io_generic_config_t;

/**
 @brief function which init io_generic

 @param[in] objPL_conf pointer to object that contain function for io_generic setUP

 @return return type of error or ok if work correctly
*/
e_io_generic_err_t io_generic_init(io_generic_config_t* objPL_conf);

/**
 @brief function which deinit io_generic

 @return return type of error or ok if work correctly
*/
e_io_generic_err_t io_generic_deinit();

/**
 @brief function which send led data to io_generic

 @param[in] led_num indicate which led should transmit

 @param[in] led_state indicate  led state (on or off)

 @return return type of error or ok if work correctly
*/
e_io_generic_err_t io_generic_send(led_num_t led_num, led_ctrl_t led_state);

/**
 @brief function which manage receive data from io_generic

 @return return type of error or ok if work correctly
*/
e_io_generic_err_t io_generic_run(void);

#ifdef __cplusplus
}
#endif
#endif /* SRC_LIB_UL_IO_GENERIC_IO_GENERIC_H_ */
