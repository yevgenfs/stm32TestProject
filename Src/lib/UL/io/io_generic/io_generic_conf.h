  #include "lib/UL/io/io_generic.h"
  
  static io_generic_config_t protocol_config[] =
  {
          {
                  .send_function    = send_to_uart,
                  .run_function     = io_uart_run,
                  .init_function    = io_uart_init,
          },
          {
                  .send_function    = send_to_spi,
                  .run_function     = io_spi_run,
                  .init_function    = io_spi_init,
          },
          {
                  .send_function    = send_to_i2c,
                  .run_function     = io_i2c_run,
                  .init_function    = io_i2c_init,
          },
  };
  size = sizeof(protocol_config)/ (protocol_config[0]);

#include <stdint.h>

typedef union unionType
{
  uint8_t led;
  io_generic_config_t btn;
} messageDataContainer_t;

typedef struct
{
  // messtype_enum
  // mess_cb
} ;

typedef void (mess_cb) (messageDataContainer_t message); 

void set_timeout(messageDataContainer_t message);

void set_timeout(messageDataContainer_t message)
{
  
}