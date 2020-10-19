/*
 * queue.c
 *
 *  Created on: 19 жовт. 2020 р.
 *      Author: yevhen.surkov
 */

#include "queue.h"

#define MAX_SIZE 10

static int8_t = size = MAX_SIZE;
static int8_t = curent_element_position = -1;
static int8_t = last_element_position = -1;

static obj_led_t *led_que[size];

que_err_t led_enque (obj_led_t *objP_this)
{
	if (last_element_position == size - 1)
	{
	    return e_que_err_que_is_full;
	}
	else
	{
		if (curent_element_position == -1)
		{
			curent_element_position = 0;
		}
		last_element_position++;
		led_que[last_element_position] = objP_this;
		return e_que_err_ok;
	}
}

obj_led_t led_deque (void)
{
	 obj_led_t objP_this;
	 if (curent_element_position == -1)
	 {
	    return NULL;
	 }
	 else
	 {
	    objP_this = *led_que[curent_element_position];
		first_element_position++;
	    if (curent_element_position > last_element_position)
	    {
	    	curent_element_position = last_element_position = -1;
	    }
	    return objP_this;
	 }
}

obj_led_t led_que_check (void)
{
	 obj_led_t objP_this;
	 if (curent_element_position == -1)
	 {
	    return NULL;
	 }
	 else
	 {
	    objP_this = *led_que[curent_element_position];
	    return objP_this;
	 }
}
