/*
 * uart_manager.h
 *
 *  Created on: 16 груд. 2020 р.
 *      Author: yevhen.surkov
 */

#ifndef SRC_LIB_UL_UART_MANAGER_UART_MANAGER_H_
#define SRC_LIB_UL_UART_MANAGER_UART_MANAGER_H_

#include "../../drivers/uart/uart.h"
#include "../../UL/spinner/spinner.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    uint8_t led_num;
}header_t;

typedef struct
{
    uint8_t led_status;
}payload_t;


typedef struct
{
    header_t  header;
    payload_t payload;

}package_t;

/// @brief e_uart_manager_err_t enum which express uart_manager erorrs
typedef enum
{
    e_uart_manager_err_ok,
    e_uart_manager_err_not_found,
    e_uart_manager_err_not_init,
    e_uart_manager_err_invalid_argument
} e_uart_manager_err_t;

e_uart_manager_err_t uart_manager_init();

e_uart_manager_err_t uart_manager_deinit();

e_uart_manager_err_t send_to_uart(led_num_t led_num, led_ctrl_t led_state);

#ifdef __cplusplus
}
#endif
#endif /* SRC_LIB_UL_UART_MANAGER_UART_MANAGER_H_ */
