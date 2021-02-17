/*
 * uart_manager.h
 *
 *  Created on: 16 груд. 2020 р.
 *      Author: yevhen.surkov
 */

#ifndef SRC_LIB_UL_IO_UART_IO_UART_H_
#define SRC_LIB_UL_IO_UART_IO_UART_H_

#include "lib/UL/io/io_generic/io_generic.h"

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/// @brief e_io_uart_err_t enum which express io_uart erorrs
typedef enum
{
    e_io_uart_err_ok,
    e_io_uart_err_not_found,
    e_io_uart_err_not_init,
    e_io_uart_err_not_deinit,
    e_io_uart_err_invalid_argument,
    e_io_uart_err_callback_exist,
    e_io_uart_err_callback_already_NULL,
} e_io_uart_err_t;

/**
 @brief function which init io_uart

 @return return type of error or ok if work correctly
*/
e_io_uart_err_t io_uart_init();

/**
 @brief function which deinit io_uart

 @return return type of error or ok if work correctly
*/
e_io_uart_err_t io_uart_deinit();

/**
 @brief function which send led data to uart

 @param[in] send_message array which contain data which should transmit

 @param[in] lenght of  array

 @return return type of error or ok if work correctly
*/
e_io_uart_err_t send_to_uart(uint8_t *send_message, uint8_t lenght);

/**
 @brief function which manage receive data from uart

 @return return type of error or ok if work correctly
*/
e_io_uart_err_t io_uart_run(void);

/**
 @brief function which send led data to uart

 @param[in][out] receive_message array in which data should receive

 @param[in] lenght of  receive data

 @return return type of error or ok if work correctly
*/
e_io_uart_err_t io_uart_receive(uint8_t *receive_message, uint8_t lenght);

/**
 @brief function which reg  callback for uart

 @param[in] callback contains contains callback which should be reg

 @return return type of error or ok if work correctly
 */
e_io_uart_err_t io_uart_reg_callback(io_genericCb_t callback);

/**
 @brief function which unreg  callback for uart

 @return return type of error or ok if work correctly
 */
e_io_uart_err_t io_uart_unreg_callback(void);

#ifdef __cplusplus
}
#endif
#endif /* SRC_LIB_UL_IO_UART_IO_UART_H_ */
