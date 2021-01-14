/*
 * uart_package_convertor.c
 *
 *  Created on: 14 січ. 2021 р.
 *      Author: yevhen.surkov
 */
#include "uart_package_convertor.h"

e_uart_package_convertor_err_t convert_receive_package(uint8_t *receive_message, receive_package_t *receive_package, uint8_t array_size)
{
    if (receive_message != NULL)
    {
        receive_package->receive_header.length = receive_message[1];
        receive_package->receive_payload.period_ms = 0;
        for (int i = 2; i < receive_package->receive_header.length + 2 && i < array_size; i++)
        {
            receive_package->receive_payload.period_ms =
                    receive_package->receive_payload.period_ms
                            + receive_message[i];
            if (i != receive_package->receive_header.length + 1)
            {
                receive_package->receive_payload.period_ms =
                        receive_package->receive_payload.period_ms * 10;
            }
        }
        receive_package->receive_header.length = 0;
        return e_uart_package_convertor_err_ok;
    }
    return e_uart_package_convertor_err_invalid_argument;
}

e_uart_package_convertor_err_t convert_header(led_num_t led_num, send_package_t *send_package)
{
    send_package->send_header.led_num = (uint8_t) led_num;
    return e_uart_package_convertor_err_ok;
}

e_uart_package_convertor_err_t convert_payload(led_ctrl_t led_state, send_package_t *send_package)
{
    send_package->send_payload.led_status = led_state;
    return e_uart_package_convertor_err_ok;
}

e_uart_package_convertor_err_t convert_message(uint8_t *send_message, send_package_t send_package)
{
    *(send_message + 0) = send_package.send_header.led_num;
    *(send_message + 1) = send_package.send_payload.led_status;
    *(send_message + 2) = '\n';
    *(send_message + 3) = '\0';
    return e_uart_package_convertor_err_ok;
}
