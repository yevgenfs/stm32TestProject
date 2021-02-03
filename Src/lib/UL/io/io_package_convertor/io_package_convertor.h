/*
 * uart_package_converotr.h
 *
 *  Created on: 14 січ. 2021 р.
 *      Author: yevhen.surkov
 */

#ifndef SRC_LIB_UL_IO_PACKAGE_CONVERTOR_IO_PACKAGE_CONVERTOR_H_
#define SRC_LIB_UL_IO_PACKAGE_CONVERTOR_IO_PACKAGE_CONVERTOR_H_

#include <stdint.h>
#include "lib/drivers/led/led.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
    e_io_package_convertor_comand_led,
    e_io_package_convertor_comand_timeout
}e_io_package_convertor_comand_t;

/// @brief header_t struct which express package header
typedef struct
{
    uint8_t comand_id;
    uint8_t message_lenght;
}send_header_t;

/// @brief payload_t struct which express package payload
typedef struct
{
    uint8_t led_num;
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
e_uart_package_convertor_err_t convert_receive_package(uint8_t *receive_message, uint8_t array_size, receive_package_t *receive_package);

/**
 @brief function which convert send_package to array

 @param[in][out] send_message data which will be send to uart

 @param[in] send_package expresses package that will be sent to uart

 @return return type of error or ok if work correctly
*/
e_uart_package_convertor_err_t convert_message(uint8_t *send_message, uint8_t size,
        led_num_t led_num, led_ctrl_t led_state);

#ifdef __cplusplus
}
#endif
#endif /* SRC_LIB_UL_IO_PACKAGE_CONVERTOR_IO_PACKAGE_CONVERTOR_H_ */
