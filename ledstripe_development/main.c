/*
 * ledstripe_development.c
 *
 * Created: 22-Oct-19 18:56:08
 * Author : Edwin
 */ 

#include <avr/io.h>
#include <stdint.h>
#include "ledstripe.h"
#include "hal_spi.h"
#define F_CPU 16000000UL
#include <util/delay.h>
#include <stdbool.h>


led_color_t red = {
	.brightness = 255,
	.red = 255,
	.green = 0,
	.blue = 0
};
led_color_t green = {
	.brightness = 255,
	.red = 0,
	.green = 255,
	.blue = 0
};
led_color_t blue = {
	.brightness = 255,
	.red = 0,
	.green = 0,
	.blue = 255
};

led_color_t A = {
	.brightness = 255,
	.red = 255,
	.green = 255,
	.blue = 255
};

led_color_t B = {
	.brightness = 255,
	.red = 255,
	.green = 255,
	.blue = 255
};

led_color_t C = {
	.brightness = 255,
	.red = 255,
	.green = 255,
	.blue = 255
};


#define Laufliechtli

#ifdef Laufliechtli
int main(void)
{
	uint8_t i = 0;
	//uint8_t toggle = 0;
	uint8_t brightness_level = 255;
	bool toggle = true;
		
	hal_SPI_enableModule();
	hal_SPI_dissableInterrupt();
	// mode must set before enabling transmission!
	hal_SPI_setMode(MASTER);
	hal_SPI_setClockRate(clk_CLK_DIV_8);
	hal_SPI_dataDirectionOrder(MSB_FIRST);
	hal_SPI_setClockPolarity(NONINVERTED);
	hal_SPI_setClockPhase(SAMPLE_ON_RISING_EDGE);
	hal_SPI_enable_TRX();
	
	ledstrip_init(hal_SPI_trx);
	
	ledstrip_set_rgb_all(0,0,0,0);
	
	
	
	ledstip_pending_set_LED_color(0,red);
	ledstip_pending_set_LED_color(1,red);
	ledstip_pending_set_LED_color(2,red);
	ledstip_pending_set_LED_color(3,red);
	
	ledstip_pending_set_LED_color(10,blue);
	ledstip_pending_set_LED_color(11,blue);
	ledstip_pending_set_LED_color(12,blue);
	ledstip_pending_set_LED_color(13,blue);
	
	ledstip_pending_set_LED_color(20,green);
	ledstip_pending_set_LED_color(21,green);
	ledstip_pending_set_LED_color(22,green);
	ledstip_pending_set_LED_color(23,green);
	
	/*
	ledstip_pending_set_LED_rgb(0,brightness_level,0,0,255);
	ledstip_pending_set_LED_rgb(2,brightness_level,0,0,255);
	ledstip_pending_set_LED_rgb(4,brightness_level,0,0,255);
	ledstip_pending_set_LED_rgb(6,brightness_level,0,0,255);
	
	ledstip_pending_set_LED_rgb(10,brightness_level,0,255,0);
	ledstip_pending_set_LED_rgb(11,brightness_level,0,255,0);
	ledstip_pending_set_LED_rgb(12,brightness_level,0,255,0);
	ledstip_pending_set_LED_rgb(13,brightness_level,0,0,255);
	*/
	ledstrip_update_all();
	
	while(1)
	{
		
		
		//ledstrip_shift_all(true,1);
		
		
		
		if(toggle)
		{
			ledstrip_ring_shift_all(true,1);
			i++;
			if(i == 225){
				i = 0;
				ledstip_pending_set_LED_color(0,red);
				ledstip_pending_set_LED_color(1,red);
				ledstip_pending_set_LED_color(2,red);
				ledstip_pending_set_LED_color(3,red);
	
				ledstip_pending_set_LED_color(10,blue);
				ledstip_pending_set_LED_color(11,blue);
				ledstip_pending_set_LED_color(12,blue);
				ledstip_pending_set_LED_color(13,blue);
	
				ledstip_pending_set_LED_color(20,green);
				ledstip_pending_set_LED_color(21,green);
				ledstip_pending_set_LED_color(22,green);
				ledstip_pending_set_LED_color(23,green);
				ledstrip_update_all();
				toggle = false;
			}
		} else{
			ledstrip_ring_shift_all(false,1);
			i++;
			if(i == 225){
				i = 0;
				ledstip_pending_set_LED_color(0,A);
				ledstip_pending_set_LED_color(1,A);
				ledstip_pending_set_LED_color(2,A);
				ledstip_pending_set_LED_color(3,A);
	
				ledstip_pending_set_LED_color(10,B);
				ledstip_pending_set_LED_color(11,B);
				ledstip_pending_set_LED_color(12,B);
				ledstip_pending_set_LED_color(13,B);
	
				ledstip_pending_set_LED_color(20,C);
				ledstip_pending_set_LED_color(21,C);
				ledstip_pending_set_LED_color(22,C);
				ledstip_pending_set_LED_color(23,C);
				ledstrip_update_all();
				toggle = true;
			}
		}
		_delay_ms(20);
	}
}
#endif

#ifdef twinkle_stars
int main(void)
{
	uint8_t i = 0;
	uint8_t toggle = 0;
	uint8_t brightness_level = 255;
	
	hal_SPI_enableModule();
	hal_SPI_dissableInterrupt();
	// mode must set before enabling transmission!
	hal_SPI_setMode(MASTER);
	hal_SPI_setClockRate(clk_CLK_DIV_8);
	hal_SPI_dataDirectionOrder(MSB_FIRST);
	hal_SPI_setClockPolarity(NONINVERTED);
	hal_SPI_setClockPhase(SAMPLE_ON_RISING_EDGE);
	hal_SPI_enable_TRX();
	
	ledstrip_init(hal_SPI_trx);
	
	ledstrip_set_rgb_all(0,0,0,0);
	
	ledstrip_update_all();
	while(1)
	{
		/*
		hal_SPI_trx(0xE0);
		hal_SPI_trx(0xFF);
		hal_SPI_trx(0x00);
		hal_SPI_trx(0x00);
		
		hal_SPI_trx(0xE4);
		hal_SPI_trx(0x00);
		hal_SPI_trx(0x00);
		hal_SPI_trx(0xFF);
		
		hal_SPI_trx(0xF8);
		hal_SPI_trx(0xFF);
		hal_SPI_trx(0x00);
		hal_SPI_trx(0x00);
		*/
		//ledstrip_set_rgb_all(0xFF,i,i,i);
		
		ledstip_pending_set_LED_rgb(18,brightness_level,i,0,0);
		ledstip_pending_set_LED_rgb(19,brightness_level,~i,i,0);
		ledstip_pending_set_LED_rgb(20,brightness_level,~i,0,i);
		ledstip_pending_set_LED_rgb(21,brightness_level,i,i,i);
		
		ledstip_pending_set_LED_rgb(1,brightness_level,i,0,0);
		ledstip_pending_set_LED_rgb(2,brightness_level,~i,i,0);
		ledstip_pending_set_LED_rgb(3,brightness_level,~i,0,i);
		ledstip_pending_set_LED_rgb(4,brightness_level,i,i,i);
		
		ledstip_pending_set_LED_rgb(5,brightness_level, ~i,0,0);
		ledstip_pending_set_LED_rgb(6,brightness_level,~i,i,0);
		ledstip_pending_set_LED_rgb(7,brightness_level,i,0,~i);
		ledstip_pending_set_LED_rgb(8,brightness_level,~i,~i,~i);
		
		ledstip_pending_set_LED_rgb(10,brightness_level,i,0,0);
		ledstip_pending_set_LED_rgb(11,brightness_level,~i,i,0);
		ledstip_pending_set_LED_rgb(12,brightness_level,~i,0,i);
		ledstip_pending_set_LED_rgb(13,brightness_level,i,i,i);
		
		ledstip_pending_set_LED_rgb(24,brightness_level,255,127,10);
		
		ledstip_pending_set_LED_rgb(25,brightness_level,i,~i,~i);
		ledstrip_update_all();
		_delay_ms(5);
		
		if(toggle == 0){	
			i++;
			if(i == 0xFF) toggle = 1;
		} else {
			i--;
			if(i == 0) toggle = 0;
		}
		//brightness_level++;
		
	}
}
#endif //twinkle_stars

#if 0
void chipselect_init();
void chipselect(uint8_t sel);

int main(void)
{
	/*
	hal_SPI_enableModule();
	hal_SPI_dataDirectionOrder(LSB_FIST);
	hal_SPI_setClockPhase(SAMPLE_ON_RISING_EDGE);
	hal_SPI_setCLK_HIGH();
	hal_SPI_enable_TRX();
	hal_SPI_setMode(MASTER);
	hal_SPI_setClockRate(clk_CLK_DIV_64);
	*/
	
	hal_SPI_enableModule();
	//hal_SPI_dissableModule();
	hal_SPI_dissableInterrupt();
	// mode must set before enabling transmission!
	hal_SPI_setMode(MASTER);
	//hal_SPI_enable_TRX();
	
	hal_SPI_setClockRate(clk_CLK_DIV_128);
	
	hal_SPI_dataDirectionOrder(MSB_FIRST);
	hal_SPI_setClockPolarity(NONINVERTED);
	hal_SPI_setClockPhase(SAMPLE_ON_RISING_EDGE);
	
	hal_SPI_enable_TRX();
	
    ledstrip_init(hal_SPI_trx,0,chipselect);
	
	ledstrip_set_rgb_all(255,255,255);
    while (1) 
    {
		ledstrip_set_rgb_all(255,255,255);
    }
}

void chipselect_init()
{
	DDRD |= (1 << PIND0);
	PORTD &= ~(1 << PIND0);
}

void chipselect(uint8_t sel)
{
	if(sel){
		PORTD |= (1 << PIND0);
	} else {
		PORTD &= ~(1 << PIND0);
	}
}

#endif