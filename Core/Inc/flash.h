/**
 * @file	flash.h
 * @brief	Header file for flash.h
 *
 *  Created on: Jun 2, 2021
 *      Author: Iván Guillermo Peña Flores
 */

#ifndef INC_FLASH_H_
#define INC_FLASH_H_

#include "stm32f1xx_hal.h"

typedef enum flash_error {
  FLASH_ALL_OK,
  FLASH_WRITE_FAIL,
  FLASH_READ_FAIL,
} flash_error;

typedef struct flash_args {
  int foo;
} flash_args;

flash_error write_flash(flash_args args, void* data);

flash_error read_flash(flash_args args, void* data);

#endif
