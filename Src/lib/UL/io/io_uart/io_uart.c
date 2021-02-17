#include "io_uart.h"
#include "lib/drivers/uart/uart.h"
#include <stdbool.h>



UART_HandleTypeDef huart2;
static bool is_all_data_receive = false;
static io_genericCb_t objS_io_genericCb;

obj_uart_t uart =
{
        .uart_handler = &huart2,
        .baud_rate    = 9600,
        .uart_type    = USART2,
};

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

e_io_uart_err_t send_to_uart(uint8_t *send_message, uint8_t lenght)
{
    if (uart_send(&uart, send_message, lenght) != e_uart_err_ok)
    {
        return e_io_uart_err_invalid_argument;
    }
    return e_io_uart_err_ok;
}

e_io_uart_err_t io_uart_receive(uint8_t *receive_message, uint8_t lenght)
{
    if (uart_receive(&uart, receive_message,
            lenght) != e_uart_err_ok)
    {
        return e_io_uart_err_invalid_argument;
    }
    return e_io_uart_err_ok;
}

e_io_uart_err_t io_uart_reg_callback(io_genericCb_t callback)
{
    if(callback != NULL)
    {
        if(objS_io_genericCb == NULL)
        {
            objS_io_genericCb = callback;
            return e_io_uart_err_ok;
        }
        return e_io_uart_err_callback_exist;
    }
    return e_io_uart_err_invalid_argument;
}

e_io_uart_err_t io_uart_unreg_callback(void)
{
    if(objS_io_genericCb != NULL)
    {
        objS_io_genericCb = NULL;
        return e_io_uart_err_ok;
    }
    return e_io_uart_err_callback_already_NULL;
}

e_io_uart_err_t io_uart_run(void)
{
    if (is_all_data_receive)
    {
        is_all_data_receive = false;
        objS_io_genericCb(e_io_generic_event_data_received);
    }
    if (USART2->SR & UART_IT_RXNE)
    {
        objS_io_genericCb(e_io_generic_event_data_ready_to_receive);
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    is_all_data_receive = true;
}
