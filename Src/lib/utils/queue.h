/*
 * queue
 *
 *  Created on: 19 жовт. 2020 р.
 *      Author: yevhen.surkov
 */

#ifndef SRC_LIB_UTILS_QUEUE_H_
#define SRC_LIB_UTILS_QUEUE_H_

#include "C:\Users\yevhen.surkov\Documents\STM_WORKPLACE\led_blink\Core\Src\lib\UL\spinner.h"


typedef enum
{
    e_que_err_ok,
    e_que_err_que_is_full,
    e_que_err_que_is_empty,
    e_que_err_que_NULL_enter,
} que_err_t;

typedef struct
{
    void*    P_array;
    uint32_t size;
    uint32_t quantity;
} queue_struct_t;

que_err_t queue_create(void* P_array, uint32_t size, uint32_t quantity);

que_err_t led_enque(void *objP_this);

obj_led_t led_deque(void);

obj_led_t led_que_check(void);

#endif /* SRC_LIB_UTILS_QUEUE_H_ */
