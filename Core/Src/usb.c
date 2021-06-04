/**
 * @file 	usb.c
 * @brief	Abstracts communication with an external computer
 *
 *  Created on: Jun 2, 2021
 *      Author: Iván Guillermo Peña Flores
 */

#include "usb.h"

/**
 * @brief	Function called by interface for setting data transmission rate (for usb).
 * @param	New Sampling time
 *
 * @retval	Return
 */
// Llamada por interfaz
// A traves de un callback, al establecer el tiempo especifico
// El checkeo del tiempo minimo y maximo se realiza de forma
// redundante, este debe de ser revisado en la interfaz
// pero ofrece proteccion adicional de malos programadores (:-))
flash_error usb_set_sample_time(const int time)
{
  int new_time = time;

  if (new_time < MINIMUM_USB_SAMPLE_TIME)
    new_time = MINIMUM_USB_SAMPLE_TIME;

  if (new_time > MAXIMUM_USB_SAMPLE_TIME)
    new_time = MAXIMUM_USB_SAMPLE_TIME;

  usb_sample_time = new_time;

  flash_args f_args = {0}; // = blah blah
  int* data_ptr = &new_time;
  return write_flash(f_args, (void*)data_ptr);

}

// Envia los datos por USB
// Los datos se encuentran en forma de floats
// Formato propuesto:
// |  Dato  | T1 | H1 | T2 | H2 |
// |--------+----+----+----+----|
// | Bytes  | 4  | 4  | 4  | 4  |
//
// Con un total de 32 bytes por dato
usb_error usb_send_data(float* data)
{

  // Crear mutex de los datos

  // Copia los datos para librar el mutex y seguir trabajando
  float fixed_data[USB_DATA_VALUES];
  for(int i = 0; i < USB_DATA_VALUES; i++)
  {
    fixed_data[i] = data[i];
  }

  // Libera mutex

  // Transmite datos
  usb_error err = USB_ALL_OK;

  const uint8_t* tx_data = (uint8_t*)fixed_data;
  const uint16_t length = USB_DATA_VALUES*4;
  if(CDC_Transmit_FS(tx_data, length) != USBD_OK) {
    err = USB_TRANSMISSION_FAIL;
  }

  return err;

}
