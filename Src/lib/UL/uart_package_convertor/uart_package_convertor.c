/*
 * uart_package_convertor.c
 *
 *  Created on: 14 січ. 2021 р.
 *      Author: yevhen.surkov
 */
#include "uart_package_convertor.h"

#define POLY 0x8408

uint16_t crc16(uint8_t *data_p, uint8_t length)
{
      uint8_t i;
      uint8_t data;
      uint16_t crc = 0xffff;

      if (length == 0)
            return (~crc);

      do
      {
            for (i=0, data=(uint16_t)0xff & *data_p++;
                 i < 8;
                 i++, data >>= 1)
            {
                  if ((crc & 0x0001) ^ (data & 0x0001))
                        crc = (crc >> 1) ^ POLY;
                  else  crc >>= 1;
            }
      } while (--length);

      crc = ~crc;
      data = crc;
      crc = (crc << 8) | (data >> 8 & 0xff);

      return (crc);
}

e_uart_package_convertor_err_t convert_receive_package(uint8_t *receive_message, receive_package_t *receive_package, uint8_t array_size)
{
    if (receive_message != NULL)
    {
        receive_package->receive_header.length = receive_message[1];
        receive_package->receive_payload.period_ms = 0;
        for (int i = 2; i < receive_package->receive_header.length + 2 && i < array_size; i++)
        {
            receive_package->receive_payload.period_ms =
                    receive_package->receive_payload.period_ms
                            + receive_message[i];
            if (i != receive_package->receive_header.length + 1)
            {
                receive_package->receive_payload.period_ms =
                        receive_package->receive_payload.period_ms * 10;
            }
        }
        receive_package->receive_header.length = 0;
        return e_uart_package_convertor_err_ok;
    }
    return e_uart_package_convertor_err_invalid_argument;
}

e_uart_package_convertor_err_t convert_header(led_num_t led_num, send_package_t *send_package)
{
    send_package->send_header.led_num = (uint8_t) led_num;
    return e_uart_package_convertor_err_ok;
}

e_uart_package_convertor_err_t convert_payload(led_ctrl_t led_state, send_package_t *send_package)
{
    send_package->send_payload.led_status = led_state;
    return e_uart_package_convertor_err_ok;
}

e_uart_package_convertor_err_t convert_message(uint8_t *send_message, send_package_t send_package)
{
    *(send_message + 0) = send_package.send_header.led_num;
    *(send_message + 1) = send_package.send_payload.led_status;
    *(send_message + 2) = '\n';
    *(send_message + 3) = '\0';
    return e_uart_package_convertor_err_ok;
}
