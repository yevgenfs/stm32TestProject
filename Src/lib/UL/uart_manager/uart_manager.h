/*
 * uart_manager.h
 *
 *  Created on: 16 груд. 2020 р.
 *      Author: yevhen.surkov
 */

#ifndef SRC_LIB_UL_UART_MANAGER_UART_MANAGER_H_
#define SRC_LIB_UL_UART_MANAGER_UART_MANAGER_H_

#include "../../drivers/uart/uart.h"
#include "../spinner/spinner.h"


#ifdef __cplusplus
extern "C" {
#endif

/// @brief header_t struct which express package header
typedef struct
{
    uint8_t led_num;
}send_header_t;

/// @brief payload_t struct which express package payload
typedef struct
{
    uint8_t led_status;
}send_payload_t;

/// @brief package_t struct which express uart package
typedef struct
{
    send_header_t  send_header;
    send_payload_t send_payload;
}send_package_t;

/// @brief header_t struct which express receive package header
typedef struct
{
    uint8_t comand_id;
    uint8_t length;
}receive_header_t;

/// @brief payload_t struct which express receive package payload
typedef struct
{
    uint32_t period_ms;
}receive_payload_t;

/// @brief package_t struct which express receive uart package
typedef struct
{
    receive_header_t  receive_header;
    receive_payload_t receive_payload;
}receive_package_t;

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
 @brief function which send led data to uart

 @param[in] led_num indicate which led should transmit

 @param[in] led_state indicate  led state (on or off)

 @return return type of error or ok if work correctly
*/
e_uart_manager_err_t send_to_uart(led_num_t led_num, led_ctrl_t led_state);

/**
 @brief function which manage receive data from uart

 @return return type of error or ok if work correctly
*/
e_uart_manager_err_t uart_manager_run(void);

#ifdef __cplusplus
}
#endif
#endif /* SRC_LIB_UL_UART_MANAGER_UART_MANAGER_H_ */
