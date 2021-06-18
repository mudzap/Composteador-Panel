/**
 * @file 	flash.c
 * @brief	Abstracts read and write functionality of flash memory for configuration data
 *
 *  Created on: Jun 2, 2021
 *      Author: Iván Guillermo Peña Flores
 */

#include "flash.h"

/* Define a virtual addresses for config variables to store
 * These are filled automatically on init_flash()
 * NumbOfVar is defined in eeprom.h
 */
static uint16_t VirtAddVarTab[NUMBER_OF_VARS];
static uint32_t prealloc_data[32];

/**
 * @brief	Initializes flash.
 *
 * @retval	Flash error
 */
flash_error init_flash()
{
  flash_error err = FLASH_ALL_OK;

  // Unlock flash for writing
  HAL_FLASH_Unlock();

  return err;
}


/**
 * @brief	Writes to flash.
 * @param	Pointer to CRC peripheral handle.
 * @param	Pointer of 32 bit sized type where data is stored.
 * @retval	Flash error
 */
flash_error write_flash(CRC_HandleTypeDef* hcrc, uint32_t* data)
{

  flash_error err = FLASH_ALL_OK;
  int shouldWrite = 1;

  for (int i = 0; i < NUMBER_OF_VARS; i++)
  {
    //if((EE_ReadVariable(VirtAddVarTab[i], &data[i])) != FLASH_COMPLETE)
   	{
      err = FLASH_READ_FAIL;
      shouldWrite = 0;
   	}
  }

  uint32_t crc;
  if (err != FLASH_READ_FAIL) {

	FLASH_EraseInitTypeDef f;
	f.TypeErase = FLASH_TYPEERASE_PAGES;
	f.PageAddress = addr;
	f.NbPages = 1;

	// If data header is not present, assume program memory
	if (!strcmp((char*)data, FLASH_STRING_CONSTANT)) {

	  err = FLASH_IS_PROGRAM;
	  shouldWrite = 0;

	} else {

	  __HAL_RCC_CRC_CLK_ENABLE();
	  crc = ~HAL_CRC_Calculate(hcrc, (uint32_t*) data, NUMBER_OF_DATA_BYTES/4);
	  __HAL_RCC_CRC_CLK_DISABLE();

	}

  }

  // If memory is not program memory, overwrites it in the given format
  if(shouldWrite) {

	// Formats data into standard format
	strcpy(&prealloc_data[HEADER_CONSTANT_INDEX], FLASH_STRING_CONSTANT);
	memcpy(&prealloc_data[DATA_INDEX], data, NUMBER_OF_DATA_BYTES);
	prealloc_data[LENGTH_INDEX] = BYTE_DATA_LENGTH;

	// Writes it
    for (int i = 0; i < NUMBER_OF_VARS; i++)
	{
	  //if((EE_WriteVariable(VirtAddVarTab[i], prealloc_data[i])) != FLASH_COMPLETE)
      {
		err = FLASH_WRITE_FAIL;
	  }
	}

  }

  return err;
}

/**
 * @brief	Reads from flash while checking for possible corruption and reads from program memory.
 * @param	Pointer to CRC peripheral handle.
 * @param	Pointer of 32 bit sized type where data is stored.
 * @retval	Flash error
 */
flash_error read_flash(CRC_HandleTypeDef* hcrc, uint32_t* data)
{
  flash_error err = FLASH_ALL_OK;

  // Read data into preallocated array
  for (int i = 0; i < NUMBER_OF_VARS; i++)
  {
    //if((EE_ReadVariable(VirtAddVarTab[i], &prealloc_data[i])) != FLASH_COMPLETE)
   	{
      err = FLASH_READ_FAIL;
   	}
  }

  if (err != FLASH_READ_FAIL) {

	// If data header is not present, assume program memory
	if (!strcmp((char*)prealloc_data, FLASH_STRING_CONSTANT)) {

	  err = FLASH_IS_PROGRAM;

	} else {

	  // If CRC doesnt match, assume corrupt
	  __HAL_RCC_CRC_CLK_ENABLE();
	  uint32_t crc = ~HAL_CRC_Calculate(hcrc, &prealloc_data[DATA_INDEX], NUMBER_OF_DATA_BYTES/4);
	  __HAL_RCC_CRC_CLK_DISABLE();

	  if(data[CRC_INDEX] != crc) {
		err = FLASH_IS_CORRUPT;
	  } else {
		// Copies data only if everything goes OK
		memcpy(data, &prealloc_data[DATA_INDEX], NUMBER_OF_DATA_BYTES);
	  }

	}
  }

  return err;
}
