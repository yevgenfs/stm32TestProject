/*
 * io_config.c
 *
 *  Created on: 29 січ. 2021 р.
 *      Author: yevhen.surkov
 */
#include "io_config.h"
#include "lib/UL/io/io_uart/io_uart.h"
#include "lib/UL/io/io_spi/io_spi.h"
#include "lib/UL/io/io_i2c/io_i2c.h"

static io_generic_config_t protocol_config[] =
{
        {
                .send_function            = send_to_uart,
                .receive_function         = io_uart_receive,
                .run_function             = io_uart_run,
                .init_function            = io_uart_init,
                .convert_message_for_send = convert_message,
                .convert_receive_package  = convert_receive_package,
                .reg_callback             = io_uart_reg_callback,
                .unreg_callback           = io_uart_unreg_callback,
        },
        {
                .send_function            = send_to_spi,
                .run_function             = io_spi_run,
                .init_function            = io_spi_init,
                .convert_message_for_send = convert_message,
                .convert_receive_package  = convert_receive_package,
        },
        {
                .send_function            = send_to_i2c,
                .run_function             = io_i2c_run,
                .init_function            = io_i2c_init,
                .convert_message_for_send = convert_message,
                .convert_receive_package  = convert_receive_package,
        },
};

e_io_config_err_t io_configurate()
{
    return (io_generic_init(&protocol_config[0]) == e_io_generic_err_ok) ? e_io_config_err_ok
            : e_io_config_err_not_init;
}
