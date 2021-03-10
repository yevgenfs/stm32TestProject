/*
 * io_generic.h
 *
 *  Created on: 18 січ. 2021 р.
 *      Author: yevhen.surkov
 */

#ifndef SRC_LIB_UL_IO_SPI_IO_SPI_H_
#define SRC_LIB_UL_IO_SPI_IO_SPI_H_

#include "lib/UL/spinner/spinner.h"

#ifdef __cplusplus
extern "C" {
#endif

/// @brief e_io_spi_err_t enum which express io_spi erorrs
typedef enum
{
    e_io_spi_err_ok,
    e_io_spi_err_not_found,
    e_io_spi_err_not_init,
    e_io_spi_err_not_deinit,
    e_io_spi_err_not_impemented,
    e_io_spi_err_invalid_argument
} e_io_spi_err_t;

/**
 @brief function which init io_spi

 @return return type of error or ok if work correctly
*/
e_io_spi_err_t io_spi_init();

/**
 @brief function which deinit io_spi

 @return return type of error or ok if work correctly
*/
e_io_spi_err_t io_spi_deinit();

/**
 @brief function which send led data to spi

 @return return type of error or ok if work correctly
*/
e_io_spi_err_t send_to_spi(led_num_t led_num, led_ctrl_t led_state);

/**
 @brief function which manage receive data from spi

 @return return type of error or ok if work correctly
*/
e_io_spi_err_t io_spi_run(void);

#ifdef __cplusplus
}
#endif
#endif /* SRC_LIB_UL_IO_GENERIC_IO_GENERIC_H_ */
