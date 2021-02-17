/*
 * uart_package_convertor.c
 *
 *  Created on: 14 січ. 2021 р.
 *      Author: yevhen.surkov
 */
#include "io_package_convertor.h"

#define SEND_MASSAGE_LENGHT 2

static send_package_t    send_package;

e_uart_package_convertor_err_t convert_receive_package(uint8_t *receive_message, uint8_t array_size, receive_package_t *receive_package)
{
    if (receive_message != NULL)
    {
        receive_package->receive_header.comand_id = receive_message[0];
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

e_uart_package_convertor_err_t convert_header()
{
    send_package.send_header.comand_id      = e_io_package_convertor_comand_led;
    send_package.send_header.message_lenght = SEND_MASSAGE_LENGHT;
    return e_uart_package_convertor_err_ok;
}

e_uart_package_convertor_err_t convert_payload(led_num_t led_num, led_ctrl_t led_state)
{
    send_package.send_payload.led_num    = (uint8_t) led_num;
    send_package.send_payload.led_status = (uint8_t) led_state;
    return e_uart_package_convertor_err_ok;
}

e_uart_package_convertor_err_t convert_message(uint8_t *send_message, uint8_t size,
        led_num_t led_num, led_ctrl_t led_state)
{
    convert_header();
    convert_payload(led_num, led_state);
    *(send_message + 0) = send_package.send_header.comand_id;
    *(send_message + 1) = send_package.send_header.message_lenght;
    *(send_message + 2) = send_package.send_payload.led_num;
    *(send_message + 3) = send_package.send_payload.led_status;
    *(send_message + 4) = '\0';
    return e_uart_package_convertor_err_ok;
}
