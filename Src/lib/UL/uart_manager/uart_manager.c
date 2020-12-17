/*
 * uart_manager.c
 *
 *  Created on: 16 груд. 2020 р.
 *      Author: yevhen.surkov
 */

#include "uart_manager.h"
#define MESSAGE_PARTS 4

UART_HandleTypeDef huart2;

obj_uart_t uart =
{
       .uart_handler = &huart2,
       .baud_rate    = 9600,
       .uart_type    = USART2,
};

package_t package;
uint8_t   message [MESSAGE_PARTS];

e_uart_manager_err_t uart_manager_init()
{
    return(uart_init(&uart) == e_uart_err_ok) ? (e_uart_manager_err_ok)
            : (e_uart_manager_err_not_init);
}

e_uart_manager_err_t uart_manager_deinit()
{
    return(uart_deinit(&uart) == e_uart_err_ok) ? (e_uart_manager_err_ok)
            : (e_uart_manager_err_not_deinit);
}

e_uart_manager_err_t convert_header(led_num_t led_num)
{
    package.header.led_num = (uint8_t)led_num;
    return e_uart_manager_err_ok;
}

e_uart_manager_err_t convert_payload(led_ctrl_t led_state)
{
    package.payload.led_status = led_state;
    return e_uart_manager_err_ok;
}

e_uart_manager_err_t convert_message()
{
    message[0] = package.header.led_num;
    message[1] = package.payload.led_status;
    message[2] = '\n';
    message[3] = '\0';
    return e_uart_manager_err_ok;
}

e_uart_manager_err_t send_to_uart(led_num_t led_num, led_ctrl_t led_state)
{
    if (convert_header(led_num) != e_uart_manager_err_ok)
    {
        return e_uart_manager_err_invalid_argument;
    }

    if (convert_payload(led_state) != e_uart_manager_err_ok)
    {
        return e_uart_manager_err_invalid_argument;
    }

    if (convert_message() != e_uart_manager_err_ok)
    {
        return e_uart_manager_err_invalid_argument;
    }

    if (uart_send(&uart, message) != e_uart_err_ok)
    {
        return e_uart_manager_err_invalid_argument;
    }
    return e_uart_manager_err_ok;
}
