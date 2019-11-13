/**
 ****************************************************************
 @file   sk9822.c
 ****************************************************************
 @brief  driver for the SK9822 LED-Strip
 ****************************************************************
 @author  Edwin Koch
 @version 1.0
 @date    2019-10-22
 ******************************************************************/
#include "sk9822.h"
#include <stdint.h>
#include <stdbool.h>

static fptr_U8_t spi_tx = NULL_POINTER;
static led_color_t led_strip_buff[N_LED];	//!< LED buffer init	

/*
 ****************************************************************
 @brief  start sequence for addressing SK9822 LEDs. See datasheet
	     for more information.
 @param  -
 @return -
 ****************************************************************
 */
void _start_sequence()
{
	spi_tx(0x00);
	spi_tx(0x00);
	spi_tx(0x00);
	spi_tx(0x00);
}

/*
 ****************************************************************
 @brief  stop sequence for addressing SK9822 LEDs. See datasheet
	     for more information.
 @param  -
 @return -
 ****************************************************************
 */
void _stop_sequence()
{
	spi_tx(0xFF);
	spi_tx(0xFF);
	spi_tx(0xFF);
	spi_tx(0xFF);
}

/*
 ****************************************************************
 @brief  writes the entire LED settings buffer to the LEDs.
 @param  -
 @return -
 ****************************************************************
 */
void _writeLEDs()
{
	uint8_t i = 0;
	_start_sequence();
	for(i = 0; i < N_LED ; i++) {
		spi_tx(led_strip_buff[i].brightness | 0xE0);
		spi_tx(led_strip_buff[i].blue);
		spi_tx(led_strip_buff[i].green);
		spi_tx(led_strip_buff[i].red);
	}
	_stop_sequence();
}

/*
 ****************************************************************
 @brief  shifts all LEDs once in the desired direction determined
		 by dir.
		 Data shifted over border is lost!
 @param  dir true: right , false: left
 @bug
 @return -
 ****************************************************************
 */
void _shift_all_once(bool dir)
{
	uint8_t i = 0;
	led_color_t zero={
		.brightness = 0,
		.red = 0,
		.green = 0,
		.blue = 0
	};
	if(dir){
		for(i = (N_LED - 1); i > 0; i--){
			led_strip_buff[i] = led_strip_buff[i-1];
		}
		led_strip_buff[0] = zero;
	}else{
		for(i = 0; i < (N_LED - 1); i++){
			led_strip_buff[i] = led_strip_buff[i+1];	
		}
		led_strip_buff[N_LED - 1] = zero;
	}
}

/*
 ****************************************************************
 @brief  ring shifts all LEDs once in the desired direction determined
		 by dir.
		 Data shifted over border is attached on the opposite border!
 @param  dir true: right , false: left
 @return -
 ****************************************************************
 */
void _ringshift_all_once(bool dir)
{
	uint8_t i = 0;
	led_color_t buff;
	if(dir){
		buff = led_strip_buff[N_LED - 1];
		for(i = (N_LED - 1); i > 0; i--){
			led_strip_buff[i] = led_strip_buff[i-1];
		}
		led_strip_buff[0] = buff;
	}else{
		buff = led_strip_buff[0];
		for(i = 0; i < (N_LED - 1); i++){
			led_strip_buff[i] = led_strip_buff[i+1];	
		}
		led_strip_buff[N_LED - 1] = buff;
	}
}

/*
 ****************************************************************
 @brief  initializes the ledstrip driver
		 the spi init function is called here and the callbacks
		 for chipselect and for the spi transmission are
		 implemented
 @param  spi_init spi init function pointer
 @param  spi_transmit spi transmit function pointer
 @param  chipselect function containing containing the gpio related
         actions to select/deselect the ledstrip
 @return -
 ****************************************************************
 */
void sk9822_init(fptr_U8_t spi_transmit)
{
	spi_tx = spi_transmit;
}

/*
 ****************************************************************
 @brief  updates one LEDs color 
         The buffer is updated and all its content is written to the strip
 @param  n_led led number
 @param  color color_t 
 @return -
 ****************************************************************
 */
void sk9822_set_LED_color(uint8_t n_led,led_color_t color)
{
	if(n_led > N_LED) return;
	color.brightness |= 0xE0;
	led_strip_buff[n_led] = color;
	_writeLEDs();
}

/*
 ****************************************************************
 @brief  updates rgb of one LED
		 The buffer is updated and all its content is written to the strip
 @param  n_led led number
 @param  r red
 @param  g green
 @param  b blue
 @return -
 ****************************************************************
 */
void sk9822_set_LED_rgb(uint8_t n_led,uint8_t level, uint8_t r, uint8_t g, uint8_t b)
{
	led_color_t color = {
		.brightness = level | 0xE0,
		.red = r,
		.green = g,
		.blue = b,
	};
	ledstrip_set_LED_color(n_led, color);
}

/*
 ****************************************************************
 @brief  updates all LED color 
         The buffer is updated and all its content is written to the strip
 @param  color color_t 
 @return -
 ****************************************************************
 */
void sk9822_set_color_all(led_color_t color)
{
	uint8_t i = 0;
	_start_sequence();
	for(i = 0; i < N_LED ; i++) {
		led_strip_buff[i] = color;
		spi_tx(led_strip_buff[i].brightness);
		spi_tx(led_strip_buff[i].blue);
		spi_tx(led_strip_buff[i].green);
		spi_tx(led_strip_buff[i].red);
	}
	_stop_sequence();
}

void sk9822_set_rgb_all(uint8_t level, uint8_t r, uint8_t g, uint8_t b)
{
	led_color_t color = {
		.brightness = level | 0xE0,
		.red = r,
		.green = g,
		.blue = b
	};
	ledstrip_set_color_all(color);
}


/*
 ****************************************************************
 @brief  updates one LEDs color 
         The buffer is updated but its content is only written to the strip
		 when ledstrip_update_all() is called.
 @param  n_led led number
 @param  color color_t 
 @return -
 ****************************************************************
 */
void sk9822_pending_set_LED_color(uint8_t led_n, led_color_t color)
{
	if(led_n > N_LED) return;
	color.brightness |= 0xE0;
	led_strip_buff[led_n] = color;
}

/*
 ****************************************************************
 @brief  updates rgb of one LED
		 The buffer is updated but its content is only written to the strip
		 when ledstrip_update_all() is called.
 @param  n_led led number
 @param  r red
 @param  g green
 @param  b blue
 @return -
 ****************************************************************
 */
void sk9822_pending_set_LED_rgb(uint8_t led_n, uint8_t level, uint8_t r, uint8_t g, uint8_t b)
{
	if(led_n > N_LED) return;
	led_strip_buff[led_n].brightness = level | 0xE0;
	led_strip_buff[led_n].blue = b;
	led_strip_buff[led_n].red = r;
	led_strip_buff[led_n].green = g;
}

/*
 ****************************************************************
 @brief  updates all LEDs with the buffer content
		 All settings made in the buffer by the pending functions
		 are written to the LEDs.
 @param  -
 @return -
 ****************************************************************
 */
void sk9822_update_all()
{
	_writeLEDs();
}

/*
 ****************************************************************
 @brief  Shift all LED settings n positions in direction
		 determined by dir.
		 Data pushed over the border is lost!
 @param  dir true : Right , false : left
 @param  n_position shift n positions in direction determined by dir
 @return -
 ****************************************************************
 */
void sk9822_shift_all(bool dir,uint8_t n_position)
{
	uint8_t i = 0;
	for(i = 0; i<n_position;i++)_shift_all_once(dir);
	_writeLEDs();
}

/*
 ****************************************************************
 @brief  ring shift all LED settings n positions in direction
		 determined by dir.
		 Data pushed over the border is attached to the opposite border.
 @param  dir true : Right , false : left
 @param  n_position shift n positions in direction determined by dir
 @return -
 ****************************************************************
 */
void sk9822_ring_shift_all(bool dir,uint8_t n_position)
{
	uint8_t i = 0;
	for(i = 0; i<n_position;i++)_ringshift_all_once(dir);
	_writeLEDs();
}
