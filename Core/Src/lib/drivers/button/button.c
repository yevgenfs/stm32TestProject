/*
 * button.c
 *
 *  Created on: 13 лист. 2020 р.
 *      Author: yevhen.surkov
 */
#include "button.h";
#define MIN_PRESSED_TIME_BORDER_MS 0
#define MAX_PRESSED_TIME_BORDER_MS 32000
#define DEBOUNCER_TIME_MS 50

static button_t   button = {GPIOA, GPIO_PIN_5};
static buttonCb_t objS_buttonCb;
static uint32_t   pressed_time_ms = 0;
static uint32_t   timeout = 0;


button_err_t button_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct =
    { 0 };
    //  init
    GPIO_InitStruct.Pin = button.pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    return e_button_err_ok;
}

button_err_t button_deinit(void)
{
    return e_button_err_ok;
}

button_err_t button_reg_callback(buttonCb_t callback)
{
    if(callback != NULL)
    {
        if(objS_buttonCb == NULL)
        {
            objS_buttonCb = callback;
            return e_button_err_ok;
        }
        return e_button_err_callback_exist;
    }
    return e_button_err_invalid_argument;
}

button_err_t button_unreg_callback(void)
{
    if(objS_buttonCb != NULL)
    {
        objS_buttonCb = NULL;
        return e_button_err_ok;
    }
    return e_button_err_callback_already_NULL;
}

void button_run(void)
{
    if (pressed_time_ms >= timeout )
    {
        objS_buttonCb(e_event_timeout);
    }

    if ((HAL_GPIO_ReadPin(button.port, button.pin))
            && (pressed_time_ms < MAX_PRESSED_TIME_BORDER_MS))
    {
        pressed_time_ms++;
        objS_buttonCb(e_event_pressed);
    }
    else if (!(HAL_GPIO_ReadPin(button.port, button.pin))
            && (pressed_time_ms > MIN_PRESSED_TIME_BORDER_MS))
    {
        pressed_time_ms--;
        objS_buttonCb(e_event_unpressed);
    }
}

button_err_t button_set_timeout(uint32_t timeout_ms)
{
    if (timeout_ms > 0)
    {
        timeout = timeout_ms + DEBOUNCER_TIME_MS;
        return e_button_err_ok;
    }
    return e_button_err_invalid_argument;
}

uint32_t button_get_timeout_with_debouncer(void)
{
    return timeout;
}

uint32_t button_get_pressed_time(void)
{
    return pressed_time_ms;
}

button_err_t button_pressed_time_reset(void)
{
    pressed_time_ms = 0;
    return e_button_err_ok;
}
