/*
 * spinner.c
 *      Author: yevhen.surkov
 */

#include "spinner.h"
#include "../utils/queue.h"

static obj_led_t led_arr[] =
{
        {
                .port = GPIOA,
                .pin = GPIO_PIN_1,
                .num = e_led_num_1,
                .status = e_led_status_disable,
                .led_state = e_led_off,
        },
        {
                .port = GPIOA,
                .pin = GPIO_PIN_2,
                .num = e_led_num_2,
                .status = e_led_status_disable,
                .led_state = e_led_off,
        },
        {
                .port = GPIOA,
                .pin = GPIO_PIN_3,
                .num = e_led_num_3,
                .status = e_led_status_disable,
                .led_state = e_led_off,
        },
        {
                .port = GPIOA,
                .pin = GPIO_PIN_4,
                .num = e_led_num_4,
                .status = e_led_status_disable,
                .led_state = e_led_off,
        },
};

static spinner_state_t spinner_state = e_spinner_state_run;

static queue_t queue;

void buttonEventsCb(button_event_t event)
{
    switch(event)
    {
        case e_event_unpressed:
            break;

        case e_event_pressed:
            break;

        case e_event_timeout:
            (spinner_state == e_spinner_state_pause) ? (spinner_state = e_spinner_state_run)
                    : (spinner_state = e_spinner_state_pause);
            break;
        default:
            break;
    }
}

e_spinner_err_t spinner_init(void)
{
    if(led_init() != e_led_err_ok)
    {
        return e_spinner_err_led_not_init;
    }
    if(create_queue(&queue, 10) != e_que_err_ok)
    {
        return e_spinner_err_queue_not_init;
    }
    if(button_init() != e_button_err_ok)
    {
        return e_spinner_err_button_not_init;
    }
    if(button_reg_callback(buttonEventsCb) != e_button_err_ok)
    {
        return e_spinner_err_button_callback_not_init;
    }
    if(button_set_timeout(1000) != e_button_err_ok)
    {
        return e_spinner_err_button_callback_not_init;
    }
    return e_spinner_err_ok;
}

e_spinner_err_t spinner_start(void)
{
    spinner_state = e_spinner_state_run;
    return e_spinner_err_ok;
}

e_spinner_err_t spinner_stop(void)
{
    spinner_state = e_spinner_state_pause;
    return e_spinner_err_ok;
}

e_spinner_err_t spinner_insert_led(led_num_t e_LedNum)
{
  spinner_ctrl_t objPL_item = { .led = e_LedNum, .cmd = e_spinner_ctrl_insert};
  return (en_queue(&queue, &objPL_item) == e_que_err_ok) ? (e_spinner_err_ok) :
          (e_spinner_err_not_add_to_queue);
}

e_spinner_err_t spinner_remove_led(led_num_t e_LedNum)
{
    spinner_ctrl_t objPL_item = { .led = e_LedNum, .cmd = e_spinner_ctrl_remove};
    return (en_queue(&queue, &objPL_item) == e_que_err_ok) ? (e_spinner_err_ok) :
            (e_spinner_err_not_add_to_queue);
}

e_spinner_err_t spinner_deinit(void)
{
    return ((led_deinit() == e_led_err_ok) && (delete_queue(&queue) == e_que_err_ok)) ?
            (e_spinner_err_ok) : (e_spinner_err_not_found);
}

e_spinner_err_t spinner_run(void)
{
    static uint32_t       period        = 400;
    static uint32_t       ms_from_last_operation         = 0;
    static int8_t         count         = 0;
    static spinner_ctrl_t objL_item     = {0};
    button_run();
    switch (spinner_state)
    {
        case e_spinner_state_pause:
            break;

        case e_spinner_state_run:
            if (de_queue(&queue, &objL_item) == e_que_err_ok)
            {
                spinner_state = e_spinner_state_process_cmd;
            }
            if(spinner_state == e_spinner_state_run  && ((HAL_GetTick() - ms_from_last_operation) > period))
            {
                ms_from_last_operation = HAL_GetTick();
                if (led_arr[count].status != e_led_status_disable)
                {
                    led_toggle(&led_arr[count]);
                }
                if (count++ >= e_led_num)
                {
                     count = 0;
                }
            }
            break;

        case e_spinner_state_process_cmd:

            if(objL_item.led == led_arr[count].num)
            {
                if (objL_item.cmd == e_spinner_ctrl_insert)
                {
                    led_add(&led_arr[count]);
                    objL_item.led = 0;
                    objL_item.cmd = 0;
                    spinner_state = e_spinner_state_run;
                }
                else if (objL_item.cmd == e_spinner_ctrl_remove)
                {
                    led_remove(&led_arr[count]);
                    objL_item.led = 0;
                    objL_item.cmd = 0;
                    spinner_state = e_spinner_state_run;
                }
                if (count++ >= e_led_num)
                {
                     count = 0;
                }
            }
            break;

        default:
            break;
    }
    return e_led_err_ok;
}
