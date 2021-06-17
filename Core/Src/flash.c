/**
 * @file 	flash.c
 * @brief	Abstracts read and write functionality of flash memory for configuration data
 *
 *  Created on: Jun 2, 2021
 *      Author: Iván Guillermo Peña Flores
 */

#include "flash.h"
#include "eeprom.h"

/* Define a virtual addresses for config variables to store
 * These are filled automatically on init_flash()
 * NumbOfVar is defined in eeprom.h
 */
uint16_t VirtAddVarTab[NumbOfVar];


/**
 * @brief	Initializes flash and eeprom emulation.
 *
 * @retval	Flash error
 */
flash_error init_flash()
{
  flash_error err = FLASH_ALL_OK;
  // Unlock flash for writing (EEPROM emulation)
  HAL_FLASH_Unlock();

  // Init EEPROM emulation
  if( EE_Init() != FLASH_COMPLETE)
  {
    err = FLASH_INIT_FAIL;
  }

  // Fill EEPROM variables addresses
  for(uint16_t i = 1; i <= NumbOfVar; i++)
  {
	  VirtAddVarTab[i-1] = i;
  }

  return err;
}


/**
 * @brief	Writes to flash.
 * @param	Pointer of 16 bit sized type where data is stored.
 * @retval	Flash error
 */
flash_error write_flash(uint16_t* data)
{
  flash_error err = FLASH_ALL_OK;
  for (i = 0; i < NumbOfVar; i++)
  {
	if((EE_WriteVariable(VirtAddVarTab[i], data[i])) != FLASH_COMPLETE)
	{
	  err = FLASH_WRITE_FAIL;
	}
  }

  return err;
}

/**
 * @brief	Reads from flash.
 * @param	Pointer of 16 bit sized type where data is stored.
 * @retval	Flash error
 */
flash_error read_flash(uint16_t* data)
{
  flash_error err = FLASH_ALL_OK;
  for (i = 0; i < NumbOfVar; i++)
  {
    if((EE_ReadVariable(VirtAddVarTab[i], &data[i])) != FLASH_COMPLETE)
   	{
      err = FLASH_READ_FAIL;
   	}
  }

  return err;
}
