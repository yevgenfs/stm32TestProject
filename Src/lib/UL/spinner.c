/*
 * spinner.c
 *
 *  Created on: 19 жовт. 2020 р.
 *      Author: yevhen.surkov
 */

led_err_t led_enable(led_num_t e_Led_number)
{
	for (int var = 0; var < e_led_num; var++)
	{
		if (led_arr[var].num == e_Led_number)
		{
			led_add(&led_arr[var]);
			led_arr[var].status = e_led_status_enable;
			return e_err_ok ;
		}
	}
	return e_err_not_found;
}

led_err_t led_disable(led_num_t e_LedNum)
{
	for (int var = 0; var < e_led_num; var++)
	{
		if (led_arr[var].num == e_LedNum)
		{
			led_remove(&led_arr[var]);
			return e_err_ok;
		}
	}
	return e_err_not_found;
}

led_err_t led_run(void)
{
	static int8_t count = 0;
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
    return e_err_ok;
}
