/**
 * @file 	control.c
 * @brief	Abstracts mostly trivial inputs, outputs and processing for the control system
 *
 *  Created on: Jun 2, 2021
 *      Author: Iván Guillermo Peña Flores
 */

#include "control.h"
#include "usb.h"
#include "flash.h"

static GPIO_PinState defaultStates[NUMBER_OF_LOADS];

/* Variables to store thresholds */
float temp_ut = DEFAULT_TEMP_UT;
float temp_lt = DEFAULT_TEMP_LT;
float hum_ut = DEFAULT_HUM_UT;
float hum_lt = DEFAULT_HUM_LT;

/**
 * @brief	Helper function for transforming 2 16 bit data into a 32 bit float
 * @param 	Pointer to 16 bit data
 *
 * @retval  Float
 */
static float uint16_to_float(uint16_t* data)
{
  /* Little-endian is the default memory format for ARM processors. */
  /* If big-endianness were to be used, then the data indexes should be swapped */
  //const uint16_t lsb = data[0];
  //const uint16_t msb = data[1];
  //return (float)( (uint32_t)(msb << 16) | (uint32_t)(lsb) );
  return (float)*(float*)data;
}

/**
 * @brief	Initializes control
 *
 * @retval	Controller error
 */
control_error control_init()
{
  control_error err = CONTROL_ALL_OK;

  // Turn loads off for safety purposes
  for(uint8_t i = 0; i < NUMBER_OF_LOADS; i++)
  {
  	defaultStates[i] = 0;
  }
  set_load_states(defaultStates);

  // Read stored values
  uint16_t stored_vars[NUMBER_OF_VARS];

  if(read_flash(stored_vars) != FLASH_ALL_OK)
  {
	  temp_ut = DEFAULT_TEMP_UT;
	  temp_lt = DEFAULT_TEMP_LT;
	  hum_ut = DEFAULT_HUM_UT;
	  hum_lt = DEFAULT_HUM_LT;
	  usb_sample_time = DEFAULT_USB_SAMPLE_TIME;
	  err = CONTROL_INIT_FAIL;
  }
  else
  {
	  /* These values are speculative and should be defined according to how variables in flash are defined */
	  temp_ut = uint16_to_float(&stored_vars[0]);
	  temp_lt = uint16_to_float(&stored_vars[2]);
	  hum_ut = uint16_to_float(&stored_vars[4]);
	  hum_lt = uint16_to_float(&stored_vars[6]);
	  usb_sample_time = stored_vars[8];
  }

  return err;

}


/**
 * @brief	Sets all loads states, states are given in an array.
 * @param	State array pointer
 *
 */
void set_load_states(GPIO_PinState* states)
{
  for(uint8_t i = 0; i < NUMBER_OF_LOADS; i++)
  {
	HAL_GPIO_WritePin(LOAD_GPIO_PORT, LOAD_GPIO_INITIAL_PIN + i, states[i]);
  }

}


/**
 * @brief	Sets a specific load state
 * @param	Index for specific load (from 0 to NUM_OF_LOADS-1)
 * @param	New state for specified load
 *
 */
void set_load_state(uint8_t load_index, GPIO_PinState state)
{
  if(load_index >= NUMBER_OF_LOADS)
  {
	return; // If unspecified, don't write anything
  }

  HAL_GPIO_WritePin(LOAD_GPIO_PORT, LOAD_GPIO_INITIAL_PIN + load_index, state);

}


/**
 * @brief	Gets error states and stores them into given array
 * @param	Pointer to state array
 *
 */
void get_error_states(GPIO_PinState* states)
{
	for(uint8_t i = 0; i < NUMBER_OF_LOADS; i++)
	{
	  states[i] = HAL_GPIO_ReadPin(ERROR_GPIO_PORT, ERROR_GPIO_INITIAL_PIN + i);
	}
}

/**
 * @brief	Gets a specific error state
 * @param	Error state index
 * @param	Pointer on where to store the specified error state
 *
 * @retval	Error state (RESET / SET)
 */
GPIO_PinState get_error_state(uint8_t error_index)
{
  if(error_index >= NUMBER_OF_LOADS)
  {
	return 1; //If can't read, assume error
  }

  return HAL_GPIO_ReadPin(ERROR_GPIO_PORT, ERROR_GPIO_INITIAL_PIN + error_index);

}
