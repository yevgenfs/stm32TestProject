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

static obj_led_t led_arr[] =
{
		{
				.port       = GPIOA,
				.pin        = GPIO_PIN_1,
				.num        = e_led_num_1,
				.status     = e_led_status_disable,
				.new_state  = e_led_off,
				.curr_state = e_led_off,
		},
		{
		        .port       = GPIOA,
		        .pin        = GPIO_PIN_2,
		        .num        = e_led_num_2,
		        .status     = e_led_status_disable,
				.new_state  = e_led_off,
				.curr_state = e_led_off,
		},
		{
				.port       = GPIOA,
				.pin        = GPIO_PIN_3,
				.num        = e_led_num_3,
				.status     = e_led_status_disable,
				.new_state  = e_led_off,
				.curr_state = e_led_off,
		},
		{
				.port       = GPIOA,
				.pin        = GPIO_PIN_4,
				.num        = e_led_num_4,
		        .status     = e_led_status_disable,
		        .new_state  = e_led_off,
				.curr_state = e_led_off,
		},
};

led_err_t led_add(obj_led_t *objP_this)
{
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
//	init
	GPIO_InitStruct.Pin = objP_this->pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

led_err_t led_remove(obj_led_t *objP_this)
{
	//led remove setup
}

led_err_t led_init(void) {
	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOA_CLK_ENABLE();

}



led_err_t led_set_state(obj_led_t *objP_this, led_ctrl_t state)
{
	objP_this->new_state = state;
	return e_err_ok;
}

led_err_t led_control(led_num_t e_LedNum, led_ctrl_t type)
{
	for (int var = 0; var < e_led_num; ++var)
	{
		if (led_arr[var].num == e_LedNum)
		{
			HAL_GPIO_WritePin(led_arr[var].port, led_arr[var].pin,
					(type) ? SET : RESET);
			return e_err_ok;
		}
	}

	return e_err_not_found;
}

