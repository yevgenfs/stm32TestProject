/*
 * dl_led.c
 *
 *  Created on: Oct 13, 2020
 *      Author: yevhen.surkov
 *
 * @file
 * @brief Source file with function realization
 * dl_leds.сpp - Library realization  for interaction with leds on DL level.
 */

#include "led.h"

led_err_t led_add(obj_led_t *objP_this)
{
    if (objP_this != NULL)
    {
        GPIO_InitTypeDef GPIO_InitStruct = { 0 };
    //  init
        GPIO_InitStruct.Pin = objP_this->pin;
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
        objP_this->status = e_led_status_enable;
    }
    return e_led_err_NULL;
}

led_err_t led_remove(obj_led_t *objP_this)
{
    //led remove setup
    if (objP_this != NULL)
    {
        return e_led_err_ok;
        objP_this->status = e_led_status_disable;
    }
    return e_led_err_NULL;
}

led_err_t led_init(void) 
{
    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOA_CLK_ENABLE();

    return e_led_err_ok;
}

led_err_t led_set_state(obj_led_t *objP_this, led_ctrl_t state)
{
    if (objP_this != NULL)
    {
        objP_this->led_state = state;
        return e_led_err_ok;
    }
    return e_led_err_NULL;
}

led_err_t led_toggle(obj_led_t *objP_this)
{
    if (objP_this != NULL)
    {
        led_control(objP_this, (objP_this->led_state == e_led_off) ? e_led_on
                : e_led_off);

        return e_led_err_ok;
    }
    return e_led_err_NULL;
}

led_err_t led_control(obj_led_t *objP_this, led_ctrl_t state)
{
    if (objP_this != NULL)
    {
        HAL_GPIO_WritePin(objP_this->port, objP_this->pin, (state == e_led_on) ? SET : RESET);
        objP_this->led_state = state;
        return e_led_err_ok;
    }
    return e_led_err_NULL;
}

