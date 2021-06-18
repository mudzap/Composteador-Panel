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

/* Establishes last flash memory page address depending on device memory density (See datasheet)*/
/* This will ensure there is no overflow when reading or writing */

/* Page size is in bytes */
/*
#define MEDIUM_DENSITY
#if defined(LOW_DENSITY)
	#define FLASH_LAST_PAGE_ADDR 0x08007C00
	#define FLASH_PAGE_SIZE 0x1024
#elif defined(MEDIUM_DENSITY)
	#define FLASH_LAST_PAGE_ADDR 0x0801FC00
	#define FLASH_PAGE_SIZE 0x1024
#elif defined(HIGH_DENSITY)
	#define FLASH_LAST_PAGE_ADDR 0x0807F800
	#define FLASH_PAGE_SIZE 0x2048
#else
	#error FLASH DENSITY NOT DEFINED AT flash.h
#endif
*/

#define BYTE_DATA_LENGTH 8*4
#define NUMBER_OF_DATA_BYTES 112
#define FLASH_STRING_CONSTANT "DICyT"
#define HEADER_CONSTANT_INDEX 0
#define LENGTH_INDEX 2
#define CRC_INDEX 3
#define DATA_INDEX 4

typedef enum flash_error {
  FLASH_ALL_OK,
  FLASH_INIT_FAIL,
  FLASH_WRITE_FAIL,
  FLASH_READ_FAIL,
  FLASH_IS_PROGRAM,
  FLASH_IS_CORRUPT,
} flash_error;

flash_error init_flash();
flash_error write_flash(CRC_HandleTypeDef* hcrc, uint32_t* data);
flash_error read_flash(CRC_HandleTypeDef* hcrc, uint32_t* data);

#endif
