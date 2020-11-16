/*
 * button.c
 *
 *  Created on: 13 лист. 2020 р.
 *      Author: yevhen.surkov
 */
#include "button.h";

#define MAX_COUNTER_BORDER 300
#define MIN_COUNTER_BORDER 0
#define SHORT_PRESS_COUNTER_BORDER 90
#define LONG_PRESS_COUNTER_BORDER 270
#define DELAY_FOR_BUTTON_READ 1

button_err_t button_init(button_t *ptr_button)
{
    if (ptr_button != NULL)
    {
        GPIO_InitTypeDef GPIO_InitStruct =
        { 0 };
        //  init
        GPIO_InitStruct.Pin = ptr_button->pin;
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
        ptr_button->status = cs_NO_PRESS;
        ptr_button->counter = MIN_COUNTER_BORDER;
        return e_button_err_ok;
    }
    return e_button_err_NULL;
}

button_err_t button_handler(button_t *ptr_button)
{
    if (ptr_button != NULL)
    {
        if ((HAL_GPIO_ReadPin(ptr_button->port, ptr_button->pin))
                && (ptr_button->counter < MAX_COUNTER_BORDER))
        {
            ptr_button->counter++;
        } else if (!(HAL_GPIO_ReadPin(ptr_button->port, ptr_button->pin))
                && (ptr_button->counter > MIN_COUNTER_BORDER))
        {
            ptr_button->counter--;
        }
        if ((ptr_button->counter > SHORT_PRESS_COUNTER_BORDER)
                && (ptr_button->status == cs_NO_PRESS))
        {
            ptr_button->status = cs_SHORT_PRESS;
        }
        if ((ptr_button->counter > LONG_PRESS_COUNTER_BORDER))
        {
            ptr_button->status = cs_LONG_PRESS;
        }
        return e_button_err_ok;
    }
    return e_button_err_NULL;
}

click_status_t button_get_press_type(button_t *ptr_button)
{
    click_status_t is_button_press = cs_NO_PRESS;
    if ((ptr_button->status == cs_SHORT_PRESS)
            && (ptr_button->counter < SHORT_PRESS_COUNTER_BORDER))
    {
        is_button_press = cs_SHORT_PRESS;
        if (ptr_button->counter
                <= SHORT_PRESS_COUNTER_BORDER - DELAY_FOR_BUTTON_READ)
        {
            ptr_button->status = cs_NO_PRESS;
            ptr_button->counter = MIN_COUNTER_BORDER;
        }
    } else if ((ptr_button->status == cs_LONG_PRESS)
            && (ptr_button->counter < LONG_PRESS_COUNTER_BORDER))
    {
        is_button_press = cs_LONG_PRESS;
        if (ptr_button->counter
                <= LONG_PRESS_COUNTER_BORDER - DELAY_FOR_BUTTON_READ)
        {
            ptr_button->status = cs_NO_PRESS;
            ptr_button->counter = MIN_COUNTER_BORDER;
        }
    }
    return is_button_press;
}

static buttonCb_t objS_buttonCb;
static uint32_t pressed_time;
static int32_t timeout;

err_t button_reg_callback(buttonCb_t callback)
{
    // error if callback is NULL
    // error if callback is already registered 

    // register callback 
    objS_buttonCb = callback;
}

err_t button_unreg_callback(void)
{
    // if ...

    objS_buttonCb = NULL;

    // ret success
}

void button_run(void)
{
    // process timeouts and events



    /* throw callback example 
     * objS_buttonCb(e_event_timeout);
     */
}

err_t button_set_timeout(uin32_t timeout_ms)
{
    // set timeout
}

uint32_t button_get_pressed_time(void)
{
    // return how much time button is pressed pressed_time
}
