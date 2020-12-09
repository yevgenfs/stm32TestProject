/*
 * uart.c
 *
 *  Created on: 9 груд. 2020 р.
 *      Author: yevhen.surkov
 */
#include "uart.h"

//UART_HandleTypeDef huart1;

//static obj_uart_t uart =
//{
//       .uart_handler = &huart1,
//       .baud_rate    = 9600,
//       .uart_type    = USART1,
//};

uart_err_t uart_init(obj_uart_t* objP_this)
{
    objP_this->uart_handler->Instance           = USART1;
    objP_this->uart_handler->Init.BaudRate      = objP_this->baud_rate;
    objP_this->uart_handler->Init.WordLength    = UART_WORDLENGTH_8B;
    objP_this->uart_handler->Init.StopBits      = UART_STOPBITS_1;
    objP_this->uart_handler->Init.Parity        = UART_PARITY_NONE;
    objP_this->uart_handler->Init.Mode          = UART_MODE_TX_RX;
    objP_this->uart_handler->Init.HwFlowCtl     = UART_HWCONTROL_NONE;
    objP_this->uart_handler->Init.OverSampling  = UART_OVERSAMPLING_16;

    if (HAL_UART_Init(&objP_this->uart_handler) != HAL_OK)
    {
      Error_Handler();
      return e_uart_err_init_fail;
    }
    return e_uart_err_ok;
}

uart_err_t uart_deinit(obj_uart_t* objP_this)
{

}

uart_err_t uart_send(obj_uart_t* objP_this , uint8_t str[], uint16_t size)
{
    HAL_UART_Transmit_IT(&objP_this->uart_handler, str, size);
}
