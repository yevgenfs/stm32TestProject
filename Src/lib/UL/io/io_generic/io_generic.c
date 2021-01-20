/*
 * io_generic.c
 *
 *  Created on: 18 січ. 2021 р.
 *      Author: yevhen.surkov
 */

#include "io_generic.h"
#include "lib/UL/io/io_uart/io_uart.h"
#include "lib/UL/io/io_spi/io_spi.h"
#include "lib/UL/io/io_i2c/io_i2c.h"

io_generic_config_t objS_conf = {0};

e_io_generic_err_t io_generic_init(io_generic_config_t* objPL_conf)
{
    if (objPL_conf != NULL && objPL_conf->send_function != NULL
            && objPL_conf->run_function != NULL && objPL_conf->init_function != NULL)
    {
        objS_conf.send_function = objPL_conf->send_function;
        objS_conf.run_function = objPL_conf->run_function;
        objS_conf.init_function = objPL_conf->init_function;
        objS_conf.init_function();
        return e_io_generic_err_ok;
    }
    return e_io_generic_err_not_init;
}

e_io_generic_err_t io_generic_deinit(void)
{
    return e_io_generic_err_ok;
}

e_io_generic_err_t io_generic_send(led_num_t led_num, led_ctrl_t led_state)
{
    objS_conf.send_function(led_num, led_state);
    return e_io_generic_err_ok;
}

e_io_generic_err_t io_generic_run(void)
{
    objS_conf.run_function();
    return e_io_generic_err_ok;
}
