/*
 * io_generic.h
 *
 *  Created on: 18 січ. 2021 р.
 *      Author: yevhen.surkov
 */

#ifndef SRC_LIB_UL_IO_I2C_IO_I2C_H_
#define SRC_LIB_UL_IO_I2C_IO_I2C_H_

#include "lib/UL/spinner/spinner.h"

#ifdef __cplusplus
extern "C" {
#endif

/// @brief e_io_spi_err_t enum which express io_i2c erorrs
typedef enum
{
    e_io_i2c_err_ok,
    e_io_i2c_err_not_found,
    e_io_i2c_err_not_init,
    e_io_i2c_err_not_deinit,
    e_io_i2c_err_not_impemented,
    e_io_i2c_err_invalid_argument
} e_io_i2c_err_t;

/**
 @brief function which init io_i2c

 @return return type of error or ok if work correctly
*/
e_io_i2c_err_t io_i2c_init();

/**
 @brief function which deinit io_i2c

 @return return type of error or ok if work correctly
*/
e_io_i2c_err_t io_i2c_deinit();

/**
 @brief function which send led data to i2c

 @return return type of error or ok if work correctly
*/
e_io_i2c_err_t send_to_i2c(led_num_t led_num, led_ctrl_t led_state);

/**
 @brief function which manage receive data from i2c

 @return return type of error or ok if work correctly
*/
e_io_i2c_err_t io_i2c_run(void);

#ifdef __cplusplus
}
#endif
#endif /* SRC_LIB_UL_IO_GENERIC_IO_GENERIC_H_ */
