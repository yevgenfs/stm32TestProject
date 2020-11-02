/*
 * queue.c
 *
 *  Created on: 19 жовт. 2020 р.
 *      Author: yevhen.surkov
 */

#include "queue.h"

static int8_t max_size = 0;
static int8_t curent_element_position = -1;
static int8_t last_element_position = -1;

static queue_struct_t obj_queue;

que_err_t queue_create(void* thisP_array, uint32_t size, uint32_t quantity)
{
    if(thisP_array != NULL && size != NULL && quantity != NULL)
    {
        max_size = size;
        obj_queue.P_array = thisP_array;
        obj_queue.size = size;
        obj_queue.quantity = quantity;
        return e_que_err_ok;
    }
    return e_que_err_que_NULL_enter;
}

que_err_t led_enque(void *objP_this)
{
    if(objP_this != NULL)
    {
        if (last_element_position == (max_size - 1))
        {
            return e_que_err_que_is_full;
        } else
        {
            if (curent_element_position == -1)
            {
                curent_element_position = 0;
            }
            last_element_position++;
            obj_queue.P_array[last_element_position] = objP_this;
            return e_que_err_ok;
        }
    }
    return e_que_err_que_NULL_enter;
}

obj_led_t led_deque(void /**objP_this*/)
{
    obj_led_t objP_this;
    if (curent_element_position == -1)
    {
        return NULL;
    }
    else
    {
        objP_this = *obj_queue.P_array[curent_element_position];
        curent_element_position++;
        if (curent_element_position > last_element_position)
        {
            curent_element_position = last_element_position = -1;
        }
        return objP_this;
    }
}

obj_led_t led_que_check(void)
{
    obj_led_t objP_this;
    if (curent_element_position == -1)
    {
        return NULL;
    }
    else
    {
        objP_this = *obj_queue.P_array[curent_element_position];
        return objP_this;
    }
}
