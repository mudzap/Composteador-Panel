/**
 * @file	usb.h
 * @brief	Header file for usb.h
 *
 *  Created on: Jun 2, 2021
 *      Author: Iván Guillermo Peña Flores
 */

#ifndef INC_USB_H_
#define INC_USB_H_

#include "stm32f1xx_hal.h"
#include "flash.h"

// Para la transmision de datos es necesario conocer el numero de estos
#define USB_SENSOR_MODULES 2
#define USB_SENSORS_PER_MODULE 2
#define USB_DATA_VALUES USB_SENSOR_MODULES * USB_SENSORS_PER_MODULE

// Periodo de muestreo en segundos
#define DEFAULT_USB_SAMPLE_TIME 1
#define MINIMUM_USB_SAMPLE_TIME 1
#define MAXIMUM_USB_SAMPLE_TIME 3600
static int usb_sample_time = DEFAULT_USB_SAMPLE_TIME;

typedef enum usb_error {
  USB_ALL_OK,
  USB_TRANSMISSION_FAIL,
} usb_error;

flash_error usb_set_sample_time(const int time);

usb_error usb_send_data(float* data);

/* ... */

#endif
