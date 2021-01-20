/*
 * uart_package_converotr.h
 *
 *  Created on: 14 січ. 2021 р.
 *      Author: yevhen.surkov
 */

#ifndef SRC_LIB_UL_UART_PACKAGE_CONVERTOR_UART_PACKAGE_CONVERTOR_H_
#define SRC_LIB_UL_UART_PACKAGE_CONVERTOR_UART_PACKAGE_CONVERTOR_H_

#include "lib/UL/io/io_uart/io_uart.h"

#ifdef __cplusplus
extern "C" {
#endif

/// @brief e_uart_package_convertor_err_t enum which express uart_package_convertor erorrs
typedef enum
{
    e_uart_package_convertor_err_ok,
    e_uart_package_convertor_err_invalid_argument
} e_uart_package_convertor_err_t;

/**
 @brief function which convert date that comes from uart

 @param[in][out] receive_message data which come from uart

 @param[in][out] receive_package expresses package that comes from uart

 @param[in] array_size contain information about size of receive_message array  led state

 @return return type of error or ok if work correctly
*/
e_uart_package_convertor_err_t convert_receive_package(uint8_t *receive_message, receive_package_t *receive_package, uint8_t array_size);

/**
 @brief function which convert data to header

 @param[in] led_num indicate  which led send state

 @param[in][out] send_package expresses package that will be sent to uart

 @return return type of error or ok if work correctly
*/
e_uart_package_convertor_err_t convert_header(led_num_t led_num, send_package_t *send_package);

/**
 @brief function which data to payload

 @param[in] led_state indicate  state of led (on/off)

 @param[in][out] send_package expresses package that will be sent to uart

 @return return type of error or ok if work correctly
*/
e_uart_package_convertor_err_t convert_payload(led_ctrl_t led_state, send_package_t *send_package);

/**
 @brief function which convert send_package to array

 @param[in][out] send_message data which will be send to uart

 @param[in] send_package expresses package that will be sent to uart

 @return return type of error or ok if work correctly
*/
e_uart_package_convertor_err_t convert_message(uint8_t *send_message, send_package_t send_package);

#ifdef __cplusplus
}
#endif
#endif /* SRC_LIB_UL_UART_PACKAGE_CONVERTOR_UART_PACKAGE_CONVERTOR_H_ */
