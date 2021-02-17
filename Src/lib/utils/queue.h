/*
 * queue
 *
 *  Created on: 19 жовт. 2020 р.
 *      Author: yevhen.surkov
 */

#ifndef SRC_LIB_UTILS_QUEUE_H_
#define SRC_LIB_UTILS_QUEUE_H_

#include "lib/UL/spinner/spinner.h"


/// @brief queue_err_t enum which express queue erorrs
typedef enum
{
    e_que_err_ok,
    e_que_err_que_is_full,
    e_que_err_que_is_empty,
    e_que_err_invalid_argument,
    e_que_err_allocation_error,
} queue_err_t;

/// @brief queue_t struct which express queue of spinner_ctrl_t
typedef struct
{
    uint32_t        rear;
    uint32_t        front;
    uint32_t        size;
    uint32_t        curent_size;
    spinner_ctrl_t* P_array;
}queue_t;

/**
 @brief function which create queue

 @param[in][out] queue_this instance of queue  which should create

 @param[in] size  of queue which should create

 @return return type of error or ok if work correctly
 */
queue_err_t create_queue(queue_t *queue_this, uint32_t size);

/**
 @brief function which add spinner_ctrl_t in  queue

 @param[in][out] queue_this instance of queue in which should add element

 @param[in] P_item instance of spinner_ctrl_t which add to the queue

 @return return type of error or ok if work correctly
 */
queue_err_t en_queue(queue_t *queue_this, spinner_ctrl_t *P_item);

/**
 @brief function which return spinner_ctrl_t from  queue

 @param[in] queue_this instance of queue from which should return element

 @param[out] P_item instance of spinner_ctrl_t which return from the queue

 @return return type of error or ok if work correctly
 */
queue_err_t de_queue(queue_t *queue_this, spinner_ctrl_t *P_item);

/**
 @brief function which return curent_size   queue

 @param[in] queue_this instance of queue from which should return size

 @return return uint32_t size
 */
uint32_t get_curent_size_queue (queue_t *queue_this);

/**
 @brief function which delete queue

 @param[in] queue_this instance of queue  which should delete

 @return return type of error or ok if work correctly
 */
queue_err_t delete_queue (queue_t *queue_this);

#endif /* SRC_LIB_UTILS_QUEUE_H_ */
