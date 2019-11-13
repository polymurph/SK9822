/**
 ****************************************************************
 @file   sk9822.h
 ****************************************************************
 @brief  driver for the SK9822 LED-Strip
 ****************************************************************
 @note   SPI: MSB first
		 MSB furthest left
		 LSB furthest right
 ****************************************************************
 @author  Edwin Koch
 @version 1.0
 @date    2019-10-22
 ******************************************************************/

#ifndef _LEDSTRIP_H_
#define _LEDSTRIP_H_

#include <stdint.h>
#include <stdbool.h>

//defines
#define NULL_POINTER 0	//!< define the NULL pointer for your target device
#define N_LED 26		//!< define the number of LEDs on the strip

typedef void (*fptr_U8_t)(uint8_t);  //!< function pointer with uint8_t parameter

/** @struct led_color_t
   *
   *  @var led_color_t::brightness
   *    color brightness uint8_t range 0 - 31 (0x1F)
   *  @var led_color_t::red
   *    red color uint8_t
   *  @var led_color_t::green
   *    green color uint8_t
   *  @var led_color_t::blue
   *    blue color uint8_t
   */
typedef struct{
	uint8_t brightness;	
	uint8_t red;
	uint8_t green;
	uint8_t blue;
}led_color_t;

void sk9822_init(fptr_U8_t spi_transmit);

void sk9822_set_LED_color(uint8_t n_led,led_color_t color);

void sk9822_set_LED_rgb(uint8_t n_led, uint8_t level, uint8_t r, uint8_t g, uint8_t b);

void sk9822_set_color_all(led_color_t color);

void sk9822_set_rgb_all(uint8_t level, uint8_t r, uint8_t g, uint8_t b);

void sk9822_pending_set_LED_color(uint8_t led_n, led_color_t color);

void sk9822_update_all();

void sk9822_ring_shift_all(bool dir,uint8_t n_position);

#endif // 