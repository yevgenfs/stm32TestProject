/*
 * io_config.h
 *
 *  Created on: 29 січ. 2021 р.
 *      Author: yevhen.surkov
 */

#ifndef SRC_LIB_UL_IO_IO_CONFIG_IO_CONFIG_H_
#define SRC_LIB_UL_IO_IO_CONFIG_IO_CONFIG_H_

/// @brief e_io_config_err_t enum which express io_config erorrs
typedef enum
{
    e_io_config_err_ok,
    e_io_config_err_not_init,
} e_io_config_err_t;

/**
 @brief function which configure io_generic

 @return return type of error or ok if work correctly
*/
e_io_config_err_t io_configurate();

#endif /* SRC_LIB_UL_IO_IO_CONFIG_IO_CONFIG_H_ */
