/*
 * button_controler.h
 *
 *  Created on: 2 груд. 2020 р.
 *      Author: yevhen.surkov
 */

#ifndef SRC_LIB_UL_BUTTON_CONTROLER_BUTTON_CONTROLER_H_
#define SRC_LIB_UL_BUTTON_CONTROLER_BUTTON_CONTROLER_H_

#include "lib/drivers/button/button.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
    e_button_controler_err_ok,
    e_button_controler_err_not_init,
} e_button_controler_err_t;

/**
 @brief function which init button_controler

 @return return type of error or ok if work correctly
 */
e_button_controler_err_t button_controler_init(void);

/**
 @brief function which run button_controler

 @return return type of error or ok if work correctly
 */
e_button_controler_err_t button_controler_run(void);

#ifdef __cplusplus
}
#endif
#endif /* SRC_LIB_UL_BUTTON_CONTROLER_BUTTON_CONTROLER_H_ */
