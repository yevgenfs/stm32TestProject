/*
 * spinner.c
 *
 *  Created on: 19 жовт. 2020 р.
 *      Author: yevhen.surkov
 */

#include "spinner.h"

static obj_led_t led_arr[] =
{
<<<<<<< Updated upstream
		{
				.port       = GPIOA,
				.pin        = GPIO_PIN_1,
				.num        = e_led_num_1,
				.status     = e_led_status_disable,
				.new_state  = e_led_off,
				.curr_state = e_led_off,
		},
		{
		        .port       = GPIOA,
		        .pin        = GPIO_PIN_2,
		        .num        = e_led_num_2,
		        .status     = e_led_status_disable,
				.new_state  = e_led_off,
				.curr_state = e_led_off,
		},
		{
				.port       = GPIOA,
				.pin        = GPIO_PIN_3,
				.num        = e_led_num_3,
				.status     = e_led_status_disable,
				.new_state  = e_led_off,
				.curr_state = e_led_off,
		},
		{
				.port       = GPIOA,
				.pin        = GPIO_PIN_4,
				.num        = e_led_num_4,
		        .status     = e_led_status_disable,
		        .new_state  = e_led_off,
				.curr_state = e_led_off,
		},
};

static spiner_work_mode work_mode = e_spiner_work_mode_run;

led_err_t spinner_init (void)
{
	if(led_init() == e_led_err_ok)
	{
    return e_led_err_ok;
	}
	return e_led_err_not_found;
=======
        { .port = GPIOA, .pin = GPIO_PIN_1, .num = e_led_num_1, .status =
                e_led_status_disable, .new_state = e_led_off, .curr_state =
                e_led_off, },
        { .port = GPIOA, .pin = GPIO_PIN_2, .num = e_led_num_2, .status =
                e_led_status_disable, .new_state = e_led_off, .curr_state =
                e_led_off, },
        { .port = GPIOA, .pin = GPIO_PIN_3, .num = e_led_num_3, .status =
                e_led_status_disable, .new_state = e_led_off, .curr_state =
                e_led_off, },
        { .port = GPIOA, .pin = GPIO_PIN_4, .num = e_led_num_4, .status =
                e_led_status_disable, .new_state = e_led_off, .curr_state =
                e_led_off, }, };

static spiner_work_mode work_mode = e_spiner_work_mode_run;

static spinner_ctrl_t spinner_queue_pool[10];

e_spinner_err_t spinner_init(void)
{
    return (led_init() == e_led_err_ok
            && queue_create(spinner_queue_pool, sizeof(spinner_queue_pool[0]),
                    10) == e_que_err_ok) ?
            (e_spinner_err_ok) : (e_spinner_err_not_NULL);
>>>>>>> Stashed changes
}

led_err_t spiner_start(void)
{
    work_mode = e_spiner_work_mode_run;
    return e_spinner_err_ok;
}

led_err_t spiner_stop(void)
{
    work_mode = e_spiner_work_mode_pause;
    return e_spinner_err_ok;
}

led_err_t spiner_insert_led(obj_led_t *objP_this)
{
<<<<<<< Updated upstream
	if(led_enque(objP_this) == e_que_err_ok){
		return e_led_err_ok;
	}
	return e_led_err_not_found;
=======
    if (NULL != objP_this)
    {
        spinner_ctrl_t objPL_item =
        { .obj_led_t = objP_this, .e_spiner_ctrl_t = e_spiner_ctrl_insert, };
        return (led_enque(objPL_item) == e_que_err_ok) ?
                (e_spinner_err_ok) : (e_spinner_err_not_add_to_queue);
    }
    return e_spinner_err_not_NULL;
>>>>>>> Stashed changes
}

led_err_t spiner_remove_led(obj_led_t *objP_this)
{
    if (NULL != objP_this)
    {
        spinner_ctrl_t objPL_item =
        { .obj_led_t = objP_this, .e_spiner_ctrl_t = e_spiner_ctrl_remove, };
        return (led_enque(objPL_item) == e_que_err_ok) ?
                (e_spinner_err_ok) : (e_spinner_err_not_add_to_queue);
    }
    return e_spinner_err_not_NULL;
}

static led_err_t spinner_enable(obj_led_t *objP_this)
{
    if (led_add(objP_this) == e_led_err_ok)
    {
        objP_this->status = e_led_status_enable;
        return e_spinner_err_ok;
    }
    return e_spinner_err_not_found;
}

static led_err_t spinner_disable(obj_led_t *objP_this)
{
    if (led_remove(objP_this) == e_led_err_ok)
    {
        objP_this->status = e_led_status_disable;
        return e_spinner_err_ok;
    }
    return e_spinner_err_not_found;
}

led_err_t spinner_deinit(void)
{
<<<<<<< Updated upstream
	if(led_deinit() == e_led_err_ok)
	{
    return e_led_err_ok;
	}
	return e_led_err_not_found;
=======
    return (led_deinit() == e_led_err_ok) ?
            (e_spinner_err_ok) : (e_spinner_err_not_found);
>>>>>>> Stashed changes
}

led_err_t spinner_run(void)
{
<<<<<<< Updated upstream
	static int8_t count = 0;
	if (work_mode == e_spiner_work_mode_run)
	{
	if (led_que_check() != NULL && led_que_check().num == led_arr[count].num)
	{
		led_deque();
		(led_arr[count].status == e_led_status_disable) ?
				spinner_enable(&led_arr[count]) : spinner_disable(&led_arr[count]);
	}
	if (led_arr[count].status != e_led_status_disable)
	{
	  if (e_led_on == led_arr[count].curr_state)
	  {
		  led_set_state(&led_arr[count], e_led_off);
	  }
	  else if (e_led_off == led_arr[count].curr_state)
	  {
		  led_set_state(&led_arr[count], e_led_on);
	  }
	  _Bool  state_changed = (led_arr[count].new_state != led_arr[count].curr_state);
	  if (state_changed != 0)
	  {
		  HAL_GPIO_WritePin(led_arr[count].port, led_arr[count].pin,
		    	(led_arr[count].new_state == e_led_on) ? SET : RESET);
		  led_arr[count].curr_state = led_arr[count].new_state;
	  }
	}
    if (count++ >= e_led_num)
=======
    static int8_t count = 0;

    switch (work_mode)
    {
    case e_spiner_work_mode_pause:
>>>>>>> Stashed changes
    {
        break;
    }
    case e_spiner_work_mode_run:
    {
        spinner_ctrl_t *objPL_item = NULL;

        if (e_que_err_que_is_empty != led_deque(objPL_item))
        {
            if (NULL != objPL_item)
            {
                return;
            }

            if (objPL_item->cmd == e_spiner_ctrl_insert)
            {
                led_add(objPL_item->objP_led);
            }
            else if (objPL_item->cmd == e_spiner_ctrl_remove)
            {
                led_remove(objPL_item->objP_leds);
            }
        }

        (led_arr[count].status == e_led_status_disable) ?
                spinner_enable(&led_arr[count]) :
                spinner_disable(&led_arr[count]);

        if (led_arr[count].status != e_led_status_disable)
        {
            led_toggle(&led_arr[count]);
            _Bool state_changed = (led_arr[count].new_state
                    != led_arr[count].curr_state);
            if (state_changed != 0)
            {
                HAL_GPIO_WritePin(led_arr[count].port, led_arr[count].pin,
                        (led_arr[count].new_state == e_led_on) ? SET : RESET);
                led_arr[count].curr_state = led_arr[count].new_state;
            }
        }
        if (count++ >= e_led_num)
        {
            count = 0;
        }
        break;
    }
    default:
    }

    return e_led_err_ok;
}
