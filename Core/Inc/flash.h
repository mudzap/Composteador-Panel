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

/* Virtual address for variables to store */
#define USB_SAMPLE_RATE_ADDR = 0x0000
#define CAN_SAMPLE_RATE_ADDR = 0x0400
#define MIN_HUMIDITY_ADDR = 0x0800
#define MAX_HUMIDITY_ADDR = 0x0C00
#define MIN_TEMP_ADDR = 0x1000
#define MAX_TEMP_ADDR = 0x1400
// And so on, as required

/*
typedef struct eeprom_data {
  uint16 usb_sample_rate;
  float can_sample_rate;
  float humidity_lower_thresh;
  float humidity_upper_thresh;
  float temperature_lower_thresh;
  float temperature_upper_thresh;
} eeprom_data;
*/

/* Define a virtual addresses for config variables to store */
/* NumbOfVar is defined in eeprom.h */
static uint16_t VirtAddVarTab[NumbOfVar] = {0x0000, 0x1000};

/* Flash redundancy pages */
/* MAKE SURE */
/*
#define FLASH_REDUNDANCY_PAGES 5
#if (FLASH_REDUNDANCY_PAGES < 0)
	#warning FLASH: NO REDUNDANT PAGES AVAILABLE FOR FLASH MEMORY, FLASH DATA MIGHT BE COMPROMISED
#endif
*/

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
