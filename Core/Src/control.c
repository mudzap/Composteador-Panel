/**
 * @file 	control.c
 * @brief	Abstracts mostly trivial inputs, outputs and processing for the control system
 *
 *  Created on: Jun 2, 2021
 *      Author: Iván Guillermo Peña Flores
 */

#include "control.h"


/**
 * @brief	Initializes control
 *
 * @retval	Controller error
 */
control_error control_init()
{

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

  HAL_GPIO_WritePin(LOAD_GPIO_PORT, LOAD_GPIO_INITIAL_PIN + i, state);

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
