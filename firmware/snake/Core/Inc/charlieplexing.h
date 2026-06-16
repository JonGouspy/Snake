/*
 * charlieplexing.h
 *
 *  Created on: Jun 10, 2026
 *      Author: jongo
 */

#ifndef INC_CHARLIEPLEXING_H_
#define INC_CHARLIEPLEXING_H_

#include "main.h"
#include <stdbool.h>

#define NB_ROW     7
#define NB_COLUMN  6
#define LED_COUNT  (NB_ROW * NB_COLUMN)

typedef struct
{
  uint16_t anode;
  uint16_t cathode;
} led_info;

extern led_info LEDS[LED_COUNT];

void clear(void);
void leds_init(void);
void print_matrix(const bool number[LED_COUNT]);
void light_up(led_info *led);
void turn_off(led_info *led);

#endif /* INC_CHARLIEPLEXING_H_ */
