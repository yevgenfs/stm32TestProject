/*
 * button_controler.c
 *
 *  Created on: 2 груд. 2020 р.
 *      Author: yevhen.surkov
 */
#include "button_controler.h"
#include <stdbool.h>

static bool is_button_pass_timeout = false;

void buttonEventsCb(button_event_t event)
{
    switch(event)
    {
        case e_event_unpressed:
            if(is_button_pass_timeout == true)
            {
                set_spinner_period_ms(button_get_pressed_time() - button_get_timeout_with_debouncer());
                button_pressed_time_reset();
                is_button_pass_timeout = false;
            }
            break;

        case e_event_pressed:
            break;

        case e_event_timeout:
            is_button_pass_timeout = true;
            break;
        default:
            break;
    }
}

e_button_controler_err_t button_controler_init(void)
{
    if(button_init() != e_button_err_ok)
    {
        return e_button_controler_err_not_init;
    }

    if(button_reg_callback(buttonEventsCb) != e_button_err_ok)
    {
        return e_button_controler_err_not_init;
    }

    if(button_set_timeout(1000) != e_button_err_ok)
    {
        return e_button_controler_err_not_init;
    }
    return e_button_controler_err_ok;
}

e_button_controler_err_t button_controler_run(void)
{
    static uint32_t       ms_from_last_button_read   = 0;
    static uint32_t       button_read_period_ms      = 1;
    if (((HAL_GetTick() - ms_from_last_button_read) > button_read_period_ms))
    {
        ms_from_last_button_read = HAL_GetTick();
        button_run();
    }
}


