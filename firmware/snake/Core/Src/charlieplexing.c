/*
 * charlieplexing.c
 *
 *  Created on: Jun 10, 2026
 *      Author: jongo
 */

#include "charlieplexing.h"

static const uint16_t pins[NB_ROW] =
{
    GPIO_PIN_0,
    GPIO_PIN_1,
    GPIO_PIN_2,
    GPIO_PIN_3,
    GPIO_PIN_4,
    GPIO_PIN_5,
    GPIO_PIN_6
};

led_info LEDS[LED_COUNT];

static void pin_hiz(uint16_t pin)
{
    GPIO_InitTypeDef cfg = {0};

    cfg.Pin = pin;
    cfg.Mode = GPIO_MODE_INPUT;
    cfg.Pull = GPIO_NOPULL;

    HAL_GPIO_Init(GPIOA, &cfg);
}

static void pin_output(uint16_t pin)
{
    GPIO_InitTypeDef cfg = {0};

    cfg.Pin = pin;
    cfg.Mode = GPIO_MODE_OUTPUT_PP;
    cfg.Pull = GPIO_NOPULL;
    cfg.Speed = GPIO_SPEED_FREQ_HIGH;

    HAL_GPIO_Init(GPIOA, &cfg);
}

void clear(void)
{
    for(int i = 0; i < NB_ROW; ++i)
    {
        pin_hiz(pins[i]);
    }
}

void leds_init(void)
{
    for(int i=0;i<NB_ROW;i++)
    {
        for(int j = 0; j < i; ++j)
        {
            LEDS[i*NB_COLUMN+j].anode   = pins[i];
            LEDS[i*NB_COLUMN+j].cathode = pins[j];
        }

        for(int j= i+1 ; j < NB_COLUMN+1; ++j)
        {
            LEDS[i*NB_COLUMN+j-1].anode   = pins[i];
            LEDS[i*NB_COLUMN+j-1].cathode = pins[j];
        }
    }
}

void light_up(led_info *led)
{
    pin_output(led->anode);
    HAL_GPIO_WritePin(GPIOA, led->anode, GPIO_PIN_SET);

    pin_output(led->cathode);
    HAL_GPIO_WritePin(GPIOA, led->cathode, GPIO_PIN_RESET);
}

void turn_off(led_info *led)
{
    pin_hiz(led->anode);
    pin_hiz(led->cathode);
}

void print_matrix(const bool number[LED_COUNT])
{
    led_info prev = LEDS[LED_COUNT-1];

    for(int i = 0; i < LED_COUNT; ++i)
    {
        led_info curr = LEDS[i];

        if(number[i])
        {
            turn_off(&prev);

            light_up(&curr);

            prev = curr;

            HAL_Delay(1);
        }
    }

    turn_off(&prev);
}
