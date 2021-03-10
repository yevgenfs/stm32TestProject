/*
 * io_generic.c
 *
 *  Created on: 18 січ. 2021 р.
 *      Author: yevhen.surkov
 */

#include "io_generic.h"

#define PACKAGE_LENGTH 254

io_generic_config_t objS_conf = {0};

volatile static uint8_t send_message[PACKAGE_LENGTH]    = {0};
volatile static uint8_t receive_message[PACKAGE_LENGTH] = {0};
volatile static receive_package_t receive_package = {0};

void io_genericEventsCb(e_io_generic_event_t event)
{
    switch(event)
    {
        case e_io_generic_event_data_ready_to_receive:
            objS_conf.receive_function(&receive_message, PACKAGE_LENGTH);
            break;

        case e_io_generic_event_data_received:
            objS_conf.convert_receive_package(&receive_message, PACKAGE_LENGTH, &receive_package);
            if (receive_package.receive_payload.period_ms > 0)
            {
                set_spinner_period_ms(receive_package.receive_payload.period_ms);
            }
            break;

        default:
            break;
    }
}

e_io_generic_err_t io_generic_init(io_generic_config_t* objPL_conf)
{
    if (objPL_conf == NULL)
    {
        return e_io_generic_err_not_init;
    }

    if (objPL_conf->init_function == NULL)
    {
        return e_io_generic_err_not_init;
    }

    if (objPL_conf->send_function == NULL)
    {
        return e_io_generic_err_not_init;
    }

    if (objPL_conf->run_function == NULL)
    {
        return e_io_generic_err_not_init;
    }

    if (objPL_conf->receive_function == NULL)
    {
        return e_io_generic_err_not_init;
    }

    if (objPL_conf->convert_message_for_send == NULL)
    {
        return e_io_generic_err_not_init;
    }

    if (objPL_conf->convert_receive_package == NULL)
    {
        return e_io_generic_err_not_init;
    }

    if (objPL_conf->reg_callback == NULL)
    {
        return e_io_generic_err_not_init;
    }

    if (objPL_conf->unreg_callback == NULL)
    {
        return e_io_generic_err_not_init;
    }

    objS_conf.send_function            = objPL_conf->send_function;
    objS_conf.receive_function         = objPL_conf->receive_function;
    objS_conf.run_function             = objPL_conf->run_function;
    objS_conf.init_function            = objPL_conf->init_function;
    objS_conf.convert_message_for_send = objPL_conf->convert_message_for_send;
    objS_conf.convert_receive_package  = objPL_conf->convert_receive_package;
    objS_conf.reg_callback             = objPL_conf->reg_callback;
    objS_conf.unreg_callback           = objPL_conf->unreg_callback;

    objS_conf.init_function();
    objS_conf.reg_callback(io_genericEventsCb);
    return e_io_generic_err_ok;
}

e_io_generic_err_t io_generic_deinit(void)
{
    return e_io_generic_err_ok;
}

e_io_generic_err_t io_generic_send(led_num_t led_num, led_ctrl_t led_state)
{
    objS_conf.convert_message_for_send(&send_message, PACKAGE_LENGTH, led_num, led_state);
    objS_conf.send_function(&send_message, PACKAGE_LENGTH);
    return e_io_generic_err_ok;
}

e_io_generic_err_t io_generic_run(void)
{
    objS_conf.run_function();
    return e_io_generic_err_ok;
}
