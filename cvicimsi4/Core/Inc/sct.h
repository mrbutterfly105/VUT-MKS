/*
 * sct1.h
 *
 *  Created on: Oct 10, 2024
 *      Author: topsecret
 */

#ifndef INC_SCT_H_
#define INC_SCT_H_

#include "main.h"

void sct_init(void);

void sct_led(uint32_t value);

void sct_value(uint16_t value, uint8_t led, uint8_t dot);

void sct_baragraph(uint8_t led);

void sct_baragraph_value(uint8_t led_binary_index, uint16_t value, uint8_t dot);

#endif /* INC_SCT_H_ */
