/*
 * uart_manager.c
 *
 *  Created on: 16 груд. 2020 р.
 *      Author: yevhen.surkov
 */

#include "uart_manager.h"

UART_HandleTypeDef huart2;

obj_uart_t uart =
{
       .uart_handler = &huart2,
       .baud_rate    = 9600,
       .uart_type    = USART2,
};

e_uart_manager_err_t uart_manager_init()
{
    if(uart_init(&uart) == e_uart_err_ok)
    {
        return e_uart_manager_err_ok;
    }
    return e_uart_manager_err_not_init;
}

e_uart_manager_err_t uart_manager_deinit()
{
    if(uart_deinit(&uart) == e_uart_err_ok)
    {
        return e_uart_manager_err_ok;
    }
    return e_uart_manager_err_not_init;
}

e_uart_manager_err_t send_to_uart(led_num_t led_num, led_ctrl_t led_state)
{
    if (led_num != NULL && led_state != NULL)
    {
        uart_send(&uart, "hello UART\n\0");
        return e_uart_manager_err_ok;
    }
    return e_uart_manager_err_invalid_argument;
}
