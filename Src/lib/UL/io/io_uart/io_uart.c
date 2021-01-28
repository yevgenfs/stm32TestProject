#include "lib/UL/io/io_uart/io_uart.h"
#include "lib/UL/uart_package_convertor/uart_package_convertor.h"
#include <stdbool.h>

#define SEND_MESSAGE_PARTS 4
#define RECEIVE_MESSAGE_LENGTH 254

UART_HandleTypeDef huart2;
bool is_all_data_receive = false;

obj_uart_t uart =
{
        .uart_handler = &huart2,
        .baud_rate    = 9600,
        .uart_type    = USART2,
};

volatile static send_package_t    send_package;
volatile static receive_package_t receive_package;
volatile static uint8_t           send_message[SEND_MESSAGE_PARTS];
volatile static uint8_t           receive_message[RECEIVE_MESSAGE_LENGTH];

e_io_uart_err_t io_uart_init()
{
    return (uart_init(&uart) == e_uart_err_ok) ?
            (e_io_uart_err_ok) : (e_io_uart_err_not_init);
}

e_io_uart_err_t io_uart_deinit()
{
    return (uart_deinit(&uart) == e_uart_err_ok) ?
            (e_io_uart_err_ok) : (e_io_uart_err_not_deinit);
}

e_io_uart_err_t send_to_uart(led_num_t led_num, led_ctrl_t led_state)
{
    if (convert_header(led_num, &send_package) != e_uart_package_convertor_err_ok)
    {
        return e_io_uart_err_invalid_argument;
    }

    if (convert_payload(led_state, &send_package) != e_uart_package_convertor_err_ok)
    {
        return e_io_uart_err_invalid_argument;
    }

    if (convert_message(send_message, send_package) != e_uart_package_convertor_err_ok)
    {
        return e_io_uart_err_invalid_argument;
    }

    if (uart_send(&uart, send_message) != e_uart_err_ok)
    {
        return e_io_uart_err_invalid_argument;
    }
    return e_io_uart_err_ok;
}

e_io_uart_err_t receive_from_uart()
{
    if (uart_receive(&uart, receive_message,
            RECEIVE_MESSAGE_LENGTH) != e_uart_err_ok)
    {
        return e_io_uart_err_invalid_argument;
    }
    return e_io_uart_err_ok;
}

uint32_t get_receive_payload_period_ms()
{
    return receive_package.receive_payload.period_ms;
}

e_io_uart_err_t io_uart_run(void)
{
    if (is_all_data_receive)
    {
        if (convert_receive_package(receive_message, &receive_package,
                RECEIVE_MESSAGE_LENGTH) == e_io_uart_err_ok)
        {
            set_spinner_period_ms(get_receive_payload_period_ms());
            is_all_data_receive = false;
        }
    }
    if (USART2->SR & UART_IT_RXNE)
    {
        if (receive_from_uart() == e_io_uart_err_ok)
        {
            return e_io_uart_err_ok;
        }
        return e_io_uart_err_not_found;
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    is_all_data_receive = true;
}
