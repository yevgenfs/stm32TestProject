/*
 * uart.h
 *
 *  Created on: 9 груд. 2020 р.
 *      Author: yevhen.surkov
 */
#ifndef UART_H_
#define UART_H_

#include "stm32f4xx_hal.h"
#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

/// @brief led_err_t enum which express uart erorrs
typedef enum
{
    e_uart_err_ok,
    e_uart_err_init_fail,
    e_uart_err_busy,
    e_uart_err_timeout,
} uart_err_t;

typedef struct
{
    UART_HandleTypeDef* uart_handler;
    USART_TypeDef       uart_type;
    uint32_t            baud_rate;
} obj_uart_t;

/**
 @brief function which init uart

 @param[in] objP_this instance of uart which should  init

 @return return type of error or ok if work correctly
 */
uart_err_t uart_init(obj_uart_t* objP_this);

/**
 @brief function which deinit uart

 @param[in] objP_this instance of uart which should  deinit

 @return return type of error or ok if work correctly
 */
uart_err_t uart_deinit(obj_uart_t* objP_this);

/**
 @brief function which init led

 @param[in] objP_this instance of led which should  init

 @return return type of error or ok if work correctly
 */
uart_err_t uart_send(obj_uart_t* objP_this , uint8_t str[], uint16_t size);


#ifdef __cplusplus
}
#endif
#endif
