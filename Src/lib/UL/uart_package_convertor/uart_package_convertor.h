/*
 * uart_package_converotr.h
 *
 *  Created on: 14 січ. 2021 р.
 *      Author: yevhen.surkov
 */

#ifndef SRC_LIB_UL_UART_PACKAGE_CONVERTOR_UART_PACKAGE_CONVERTOR_H_
#define SRC_LIB_UL_UART_PACKAGE_CONVERTOR_UART_PACKAGE_CONVERTOR_H_

#include "../uart_manager/uart_manager.h"

#ifdef __cplusplus
extern "C" {
#endif

/// @brief e_uart_manager_err_t enum which express uart_manager erorrs
typedef enum
{
    e_uart_package_convertor_err_ok,
    e_uart_package_convertor_err_invalid_argument
} e_uart_package_convertor_err_t;

e_uart_package_convertor_err_t convert_receive_package(uint8_t *receive_message, receive_package_t *receive_package, uint8_t array_size);

e_uart_package_convertor_err_t convert_header(led_num_t led_num, send_package_t *send_package);

e_uart_package_convertor_err_t convert_payload(led_ctrl_t led_state, send_package_t *send_package);

e_uart_package_convertor_err_t convert_message(uint8_t *send_message, send_package_t send_package);

#ifdef __cplusplus
}
#endif
#endif /* SRC_LIB_UL_UART_PACKAGE_CONVERTOR_UART_PACKAGE_CONVERTOR_H_ */
