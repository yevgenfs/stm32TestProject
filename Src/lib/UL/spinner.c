/*
 * spinner.c
 *      Author: yevhen.surkov
 */

#include "spinner.h"
#include "C:\Users\yevhen.surkov\Documents\STM_WORKPLACE\led_blink\Core\Src\lib\utils/queue.h"

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


e_spinner_err_t spinner_init(void)
{
    return (led_init() == e_led_err_ok
            && create_queue(&queue, 10) == e_que_err_ok) ?
            (e_spinner_err_ok) : (e_spinner_err_not_NULL);
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
    static int8_t count = 0;
    static spinner_ctrl_t objL_item = {0};
    switch (spinner_state)
    {
        case e_spinner_state_pause:
            break;

        case e_spinner_state_run:
            if (de_queue(&queue, &objL_item) == e_que_err_ok)
            {
                spinner_state = e_spinner_state_process_cmd;
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
            }
            break;

        default:
            break;
    }
    if (led_arr[count].status != e_led_status_disable && get_curent_size_queue(&queue) == 0)
    {
        led_toggle(&led_arr[count]);
    }
    if (count++ >= e_led_num)
    {
        count = 0;
    }
    return e_led_err_ok;
}
