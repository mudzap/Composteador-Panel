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
uint16_t usb_set_sample_time(const uint16_tss time)
{
  uint16_t new_time = time;

  if (new_time < MINIMUM_USB_SAMPLE_TIME)
    new_time = MINIMUM_USB_SAMPLE_TIME;

  if (new_time > MAXIMUM_USB_SAMPLE_TIME)
    new_time = MAXIMUM_USB_SAMPLE_TIME;

  usb_sample_time = new_time;

  //void* data_ptr = &new_time;
  //return write_flash((void*)data_ptr); //No es necesario, es mejor manejarlo desde la interfaz.

  return usb_sample_time;

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
  for(uint16_t i = 0; i < USB_DATA_VALUES; i++)
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

// Does this really need a function?
GPIO_PinState usb_detect_vbus()
{
  return HAL_GPIO_ReadPin(USB_VBUS_PORT, USB_VBUS_PIN);
}

// Ditto.
void usb_pullup_dp()
{
  HAL_GPIO_WritePin(USB_PULLUP_PORT, USB_PULLUP_PIN, 1);
}
void usb_set_high_impedance_dp()
{
  HAL_GPIO_WritePin(USB_PULLUP_PORT, USB_PULLUP_PIN, 0);
}
