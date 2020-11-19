/*
 * queue.c
 *
 *  Created on: 19 жовт. 2020 р.
 *      Author: yevhen.surkov
 */

#include "queue.h"
#include "stdlib.h"
#include "string.h"

queue_err_t create_queue(queue_t *queue_this, uint32_t size)
{
    if (size != 0 && queue_this != NULL)
    {
        queue_this->front = -1;
        queue_this->rear = -1;
        queue_this->curent_size = 0;
        queue_this->size = size;
        if (((queue_this->P_array = (spinner_ctrl_t*) malloc(
                size * sizeof(spinner_ctrl_t)))) == NULL)
        {
            return e_que_err_allocation_error;
        }
        return e_que_err_ok;
    }
    return e_que_err_invalid_argument;

}

queue_err_t en_queue(queue_t *queue_this, spinner_ctrl_t *P_item)
{
    if (P_item != NULL && queue_this != NULL)
    {
        if ((queue_this->front == 0 && queue_this->rear == queue_this->size - 1)
                || (queue_this->rear
                        == (queue_this->front - 1) % (queue_this->size - 1)))
        {
            return e_que_err_que_is_full;
        } else if (queue_this->front == -1) /* Insert First Element */
        {
            queue_this->front = 0;
            queue_this->rear = 0;
            memcpy(&queue_this->P_array[queue_this->rear], P_item,
                    sizeof(spinner_ctrl_t));
            queue_this->curent_size++;
        } else if (queue_this->rear == queue_this->size - 1
                && queue_this->front != 0)
        {
            queue_this->rear = 0;
            memcpy(&queue_this->P_array[queue_this->rear], P_item,
                    sizeof(spinner_ctrl_t));
            queue_this->curent_size++;
        } else
        {
            queue_this->rear++;
            memcpy(&queue_this->P_array[queue_this->rear], P_item,
                    sizeof(spinner_ctrl_t));
            queue_this->curent_size++;
        }
        return e_que_err_ok;
    }
    return e_que_err_invalid_argument;
}

queue_err_t de_queue(queue_t *queue_this, spinner_ctrl_t *P_item)
{
    if (queue_this != NULL)
    {
        if (queue_this->curent_size == 0)
        {
            P_item = NULL;
            return e_que_err_que_is_empty;
        }
        memcpy(P_item, &queue_this->P_array[queue_this->front],
                sizeof(spinner_ctrl_t));
        queue_this->curent_size--;
        if (queue_this->front == queue_this->rear)
        {
            queue_this->curent_size = 0;
        } else if (queue_this->front == queue_this->size - 1)
        {
            queue_this->front = 0;
        } else
        {
            queue_this->front++;
        }
        return e_que_err_ok;
    }
    return e_que_err_invalid_argument;
}

queue_err_t delete_queue(queue_t *queue_this)
{
    if (queue_this != NULL)
    {
        free(queue_this->P_array);
        return e_que_err_ok;
    }
    return e_que_err_invalid_argument;
}

uint32_t get_curent_size_queue(queue_t *queue_this)
{
    if (queue_this != NULL)
    {
        return queue_this->curent_size;
    }
    return e_que_err_invalid_argument;
}
