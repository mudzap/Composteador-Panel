/**
 * @file	control.h
 * @brief	Header file for control.h
 *
 *  Created on: Jun 2, 2021
 *      Author: Iván Guillermo Peña Flores
 */

#ifndef INC_CONTROL_H_
#define INC_CONTROL_H_

#include "stm32f1xx_hal.h"

/* Define number of loads for iteration and index boundary checking */
#define NUMBER_OF_LOADS 3

/* Define port and initial pin, for example: GPIOA, GPIO_PIN_8 and 3 loads implies that pins A8, A9 and A10 will be utilized */
/* The same applies for loads and error signals */
/* Remember: GPIO_PIN_8 + 1 = GPIO_PIN_9 */
#define ERROR_GPIO_PORT GPIOA
#define ERROR_GPIO_INITIAL_PIN GPIO_PIN_8
#define LOAD_GPIO_PORT GPIOB
#define LOAD_GPIO_INITIAL_PIN GPIO_PIN_12

typedef enum control_error {
  CONTROL_ALL_OK,
  CONTROL_INIT_FAIL,
} control_error;

/* Variables to store thresholds */
extern float temp_ut;
extern float temp_lt;
extern float hum_ut;
extern float hum_lt;

#define DEFAULT_TEMP_UT 0.f
#define DEFAULT_TEMP_LT 0.f
#define DEFAULT_HUM_UT 	0.f
#define DEFAULT_HUM_LT 	0.f

control_error control_init();
void set_load_states(GPIO_PinState* states);
void set_load_state(uint8_t load_index, GPIO_PinState state);
void get_error_states(GPIO_PinState* states);
GPIO_PinState get_error_state(uint8_t error_index);

#endif
