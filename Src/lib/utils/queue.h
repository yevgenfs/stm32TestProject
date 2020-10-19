/*
 * queue
 *
 *  Created on: 19 жовт. 2020 р.
 *      Author: yevhen.surkov
 */

#ifndef SRC_LIB_UTILS_QUEUE_H_
#define SRC_LIB_UTILS_QUEUE_H_

typedef enum
{
  e_que_err_ok,
  e_que_err_que_is_full,
  e_que_err_que_is_empty,
}que_err_t;


que_err_t led_enque (led_queue_t *objP_this);

obj_led_t led_deque (void);

obj_led_t led_que_check (void);

#endif /* SRC_LIB_UTILS_QUEUE_H_ */
