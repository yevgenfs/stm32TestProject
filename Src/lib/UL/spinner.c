/*
 * spinner.c
 *
 *  Created on: 19 жовт. 2020 р.
 *      Author: yevhen.surkov
 */

#include "spinner.h"

static obj_led_t led_arr[] =
{
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
}

led_err_t spiner_start(void)
{
	work_mode = e_spiner_work_mode_run;
	return e_led_err_ok;
}

led_err_t spiner_stop(void)
{
	work_mode = e_spiner_work_mode_pause;
	return e_led_err_ok;
}

led_err_t spiner_insert_led(obj_led_t *objP_this)
{
	if(led_enque(objP_this) == e_que_err_ok){
		return e_led_err_ok;
	}
	return e_led_err_not_found;
}

led_err_t spiner_remove_led(obj_led_t *objP_this)
{
	if(led_enque(objP_this) == e_que_err_ok){
		return e_led_err_ok;
	}
	return e_led_err_not_found;
}

static led_err_t spinner_enable(obj_led_t *objP_this)
{
	if(led_add(objP_this) == e_led_err_ok)
	{
	objP_this->status = e_led_status_enable;
    return e_led_err_ok;
	}
	return e_led_err_not_found;
}

static led_err_t spinner_disable(obj_led_t *objP_this)
{
	if(led_remove(objP_this) == e_led_err_ok)
	{
	objP_this->status = e_led_status_disable;
    return e_led_err_ok;
	}
	return e_led_err_not_found;
}

led_err_t spinner_deinit (void)
{
	if(led_deinit() == e_led_err_ok)
	{
    return e_led_err_ok;
	}
	return e_led_err_not_found;
}

led_err_t spinner_run(void)
{
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
    {
      count = 0;
    }
	}
    return e_led_err_ok;
}
