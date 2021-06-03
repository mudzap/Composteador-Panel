/**
 * @file 	flash.c
 * @brief	Abstracts read and write functionality of flash memory for configuration data
 *
 *  Created on: Jun 2, 2021
 *      Author: Iván Guillermo Peña Flores
 */

#include "flash.h"

/**
 * @brief	Summary
 * @param	Arguments
 *
 * @retval	Return
 */

flash_error write_flash(flash_args args, void* data)
{
  flash_error err = FLASH_ALL_OK;
  //Escribir

  if(0)
    err = FLASH_WRITE_FAIL;

  return err;
}

flash_error read_flash(flash_args args, void* data)
{
  flash_error err = FLASH_ALL_OK;

  //Leer
  if(0)
    err = FLASH_READ_FAIL;

  return err;
}
