/*
 * queue.c
 *
 *  Created on: 19 жовт. 2020 р.
 *      Author: yevhen.surkov
 */

#include "queue.h"
#include "stdlib.h"
#include "string.h"

static int32_t max_size = 0;
static int32_t curent_element_position = -8;
static int32_t last_element_position = -8;
static queue_struct_t obj_queue;

que_err_t queue_create(void* thisP_array, uint32_t size, uint32_t quantity)
{
    if(thisP_array != NULL && size != 0 && quantity != 0)
    {

        max_size           = quantity * size;
        obj_queue.P_array  = thisP_array;
        obj_queue.size     = size;
        obj_queue.quantity = quantity;
        return e_que_err_ok;
    }
    return e_que_err_que_NULL_enter;
}

que_err_t led_enque(void *objP_this)
{
    if(objP_this != NULL)
    {
        if (last_element_position == (max_size - obj_queue.size))
        {
            return e_que_err_que_is_full;
        } else
        {
            if (curent_element_position < 0)
            {
                curent_element_position = 0;
            }
            last_element_position += obj_queue.size;
            memcpy((void*)(obj_queue.P_array + last_element_position), (void*)objP_this, obj_queue.size);
            if (last_element_position == max_size)
            {
                last_element_position   = -8;
            }
            return e_que_err_ok;
        }
    }
    return e_que_err_que_NULL_enter;
}

que_err_t led_deque(void *objP_this)
{

    if (curent_element_position < 0)
    {
        objP_this = NULL;
        return e_que_err_que_is_empty;
    }
    else
    {
        objP_this = (obj_queue.P_array + curent_element_position);
        if(objP_this != NULL)
        {
            curent_element_position += obj_queue.size;
            if (curent_element_position > last_element_position)
            {
                curent_element_position = -8;
            }
            return e_que_err_ok;
        }
        return e_que_err_que_NULL_enter;
    }
}

