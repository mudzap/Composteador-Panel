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
#include "eeprom.h"

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

/* Define a virtual addresses for config variables to store
 * These are filled automatically on init_flash()
 * NumbOfVar is defined in eeprom.h
 */
static uint16_t VirtAddVarTab[NumbOfVar];

typedef enum flash_error {
  FLASH_ALL_OK,
  FLASH_INIT_FAIL,
  FLASH_WRITE_FAIL,
  FLASH_READ_FAIL,
} flash_error;

flash_error init_flash();
flash_error write_flash(uint16_t* data);
flash_error read_flash(uint16_t* data);

#endif
