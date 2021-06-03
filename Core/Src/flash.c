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
  // La escritura se realiza por half-word, word o double word.
  // Es deseable no realizar muchas lecturas, solamente durante configuración
  // Por ende, se recomienda desactivar las funciones de control al programar la memoria flash
  // Adicionalmente, para prevenir el inaccionamiento accidental del panel de control
  // considerese el uso de un timeout con un timer.
  // Word: 32 bits. En gran parte de los casos, necesitamos escribir 32 bits, asi que
  // la programación se realizara asi.

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
