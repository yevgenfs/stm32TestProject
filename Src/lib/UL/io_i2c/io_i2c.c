/*
 * io_generic.c
 *
 *  Created on: 18 січ. 2021 р.
 *      Author: yevhen.surkov
 */

#include <lib/UL/io_i2c/io_i2c.h>

e_io_i2c_err_t io_i2c_init()
{
    return e_io_i2c_err_ok;
}

e_io_i2c_err_t io_i2c_deinit()
{
    return e_io_i2c_err_ok;
}

e_io_i2c_err_t send_to_i2c(led_num_t led_num, led_ctrl_t led_state)
{
    return e_io_i2c_err_ok;
}

e_io_i2c_err_t io_i2c_run(void)
{
    return e_io_i2c_err_ok;
}
