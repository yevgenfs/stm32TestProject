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

/// @brief header_t struct which express package header
typedef struct
{
    uint8_t led_num;
}header_t;

/// @brief payload_t struct which express package payload
typedef struct
{
    uint8_t led_status;
}payload_t;

/// @brief package_t struct which express uart package
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
    e_uart_manager_err_not_deinit,
    e_uart_manager_err_invalid_argument
} e_uart_manager_err_t;

/**
 @brief function which init uart_manager

 @return return type of error or ok if work correctly
*/
e_uart_manager_err_t uart_manager_init();

/**
 @brief function which deinit uart_manager

 @return return type of error or ok if work correctly
*/
e_uart_manager_err_t uart_manager_deinit();

/**
 @brief function which insert led in spinner

 @param[in] led_num indicate which led should transmit

 @param[in] led_state indicate  led state (on or off)

 @return return type of error or ok if work correctly
*/
e_uart_manager_err_t send_to_uart(led_num_t led_num, led_ctrl_t led_state);

/**
 @brief function which receive data  from uart

 @param[out] message_buffer data which receive

 @param[in] length  of input data

 @return return type of error or ok if work correctly
*/
e_uart_manager_err_t receive_from_uart(uint8_t* receive_message, uint8_t length);

#ifdef __cplusplus
}
#endif
#endif /* SRC_LIB_UL_UART_MANAGER_UART_MANAGER_H_ */
