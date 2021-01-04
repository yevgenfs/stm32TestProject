/*
 * uart_manager.c
 *
 *  Created on: 16 груд. 2020 р.
 *      Author: yevhen.surkov
 */

#include "uart_manager.h"
#define SEND_MESSAGE_PARTS 4
#define RECEIVE_MESSAGE_LENGTH 258

UART_HandleTypeDef huart2;

obj_uart_t uart =
{
       .uart_handler = &huart2,
       .baud_rate    = 9600,
       .uart_type    = USART2,
};

static send_package_t             send_package;
volatile static receive_package_t receive_package;
static uint8_t                    send_message [SEND_MESSAGE_PARTS];
static uint8_t                    receive_message[RECEIVE_MESSAGE_LENGTH];

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
    send_package.send_header.led_num = (uint8_t)led_num;
    return e_uart_manager_err_ok;
}

e_uart_manager_err_t convert_payload(led_ctrl_t led_state)
{
    send_package.send_payload.led_status = led_state;
    return e_uart_manager_err_ok;
}

e_uart_manager_err_t convert_message()
{
    send_message[0] = send_package.send_header.led_num;
    send_message[1] = send_package.send_payload.led_status;
    send_message[2] = '\n';
    send_message[3] = '\0';
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

    if (uart_send(&uart, send_message) != e_uart_err_ok)
    {
        return e_uart_manager_err_invalid_argument;
    }
    return e_uart_manager_err_ok;
}

e_uart_manager_err_t convert_receive_package(uint8_t *receive_message)
{
    if (receive_message != NULL)
    {
        receive_package.receive_header.length     = receive_message[1];
        receive_package.receive_payload.period_ms = 0;
        for (int i = 2; i < receive_package.receive_header.length + 2; i++)
        {
            receive_package.receive_payload.period_ms =
                    receive_package.receive_payload.period_ms
                            + receive_message[i];
            if (i != receive_package.receive_header.length + 1)
            {
                receive_package.receive_payload.period_ms =
                        receive_package.receive_payload.period_ms * 10;
            }
        }
        receive_package.receive_header.length = 0;
        return e_uart_manager_err_ok;
    }
    return e_uart_manager_err_invalid_argument;
}

e_uart_manager_err_t receive_from_uart()
{
    if (uart_receive(&uart, receive_message,
            RECEIVE_MESSAGE_LENGTH) != e_uart_err_ok)
    {
        return e_uart_manager_err_invalid_argument;
    }
    receive_package.receive_payload.period_ms = 0;
    if (convert_receive_package(&receive_message) != e_uart_manager_err_ok)
    {
        return e_uart_manager_err_invalid_argument;
    }
    return e_uart_manager_err_ok;
}

uint32_t get_receive_payload_period_ms()
{
    return  receive_package.receive_payload.period_ms;
}

e_uart_manager_err_t uart_manager_run(void)
{
//    if(huart2.RxXferCount==0)
//    {
        if (receive_from_uart() == e_uart_manager_err_ok)
        {
            set_spinner_period_ms(get_receive_payload_period_ms());
        }
    //}
    return e_uart_manager_err_ok;
}

//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//    if (receive_from_uart() == e_uart_manager_err_ok)
//    {
//        set_spinner_period_ms(get_receive_payload_period_ms());
//    }
//}
