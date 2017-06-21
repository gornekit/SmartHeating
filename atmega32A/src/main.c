/*
 * RealTime.c
 *
 * Created: 15.08.2016 10:55:31
 * Author : Дом
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include "atmega32A.h"
#include "n5110.h"
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>
#include "ds18b20.h"
#include <avr/eeprom.h>

int k = 0;
char last_min =  0;
char temp1[15] = {'1', ' ', 'f', 'l', '.', ' '};
char temp2[15] = {'2', ' ', 'f', 'l', '.', ' '};
char last_sec;
uint8_t tempetature[2];
uint8_t data[500];
uint8_t e_data[500] EEMEM;

int counter = 0;
int iter = 0;

void add_sec();
void print_time(const my_time m_time);
void convert(const char data, char * buff, char position);
void read_uint8_temperature(uint8_t * data, char sensor);

my_time cur_time;

ISR (TIMER2_COMP_vect)
{
	asm("cli");
	if(k == 0)
	{
		PORTC |= (1<<1);
		k = 1;
	}
	else
	{
		PORTC &= ~(1<<1);
		k = 0;
	}
	add_sec();

	asm("sei");
}
	
int main(void)
{
    board_init();
   
    while (1) 
    {	
		if(last_sec != cur_time.sec)
		{
			print_time(cur_time);
			last_sec = cur_time.sec;
            if(iter == 9)
            {
                read_uint8_temperature(&data[counter], P1_TEMP);
                eeprom_write_byte(&e_data[counter], data[counter]);
                counter++;
                iter = 0;
            }
            iter++;
		}
		asm("nop"); 
	}
}

//////////////////////////////////////////////////////////////////////////
//Functions

void board_init()
{
	//Set up Timer 2
	ASSR = (1<<3);
	TCCR2 |= (1<<WGM21) | (1<<CS22) | (1<<CS21) | (1<<CS20);
	OCR2 = 192;
		
	cur_time.year = YEAR;
	cur_time.month = MONTH;
	cur_time.day = DAY;
	cur_time.hour = HOUR;
	cur_time.min = MIN;
	cur_time.sec = SEC;
	last_min = cur_time.min;
	last_sec = cur_time.sec;
	
	while( (ASSR & ~(1<<AS2)) )
	{
		asm("nop");
	}
	TIMSK |= (1<<OCIE2);
	
	//Set up the led
	DDRC |= (1<<1);
	
	//eeprom_write_byte(&e_h1, h1);
	//eeprom_write_byte(&e_h2, h2);
	//eeprom_write_byte(&e_h3, h3);

	
	//Set up the display
	Lcd_init();
	_delay_ms(1000);
	
	print_time(cur_time);
	
	asm("sei");
}

void add_sec()
{
	cur_time.sec = cur_time.sec + 6 ;
	if(cur_time.sec == 60)
	{
		cur_time.sec = 0;
		cur_time.min = cur_time.min + 1;
		if(cur_time.min == 60)
		{
			cur_time.min = 0;
			cur_time.hour = cur_time.hour + 1;
			if(cur_time.hour == 24)
			{
				cur_time.hour = 0;
				cur_time.day = cur_time.day + 1;
				if(cur_time.day == 31)
				{
					cur_time.day = 1;
					cur_time.month = cur_time.month + 1;
					if(cur_time.month == 12)
					{
						cur_time.month = 1;
						cur_time.year++; 						
					}	
				}
			}
		}
	}
}


void print_time(const my_time m_time)
{
	Lcd_clear();
	
	temp_read_temperature(temp1 + 6, P1_TEMP);
	temp_read_temperature(temp2 + 6, P2_TEMP);
	
	convert(m_time.hour, time, 0);
	convert(m_time.min, time, 3);
	convert(m_time.day, time, 6);
	convert(m_time.month, time, 9);
	convert(m_time.year, time, 12);
	
	time[2] = ':';
	time[5] = ' ';
	time[8] = '.';
	time[11] = '.';
	time[15] = '\0';
	
	Lcd_print(0, 0, FONT_1X, (byte *) time);
	Lcd_print(0, 2, FONT_1X, (byte *) temp1);
	Lcd_print(0, 3, FONT_1X, (byte *) temp2);

	Lcd_update();
	
}

void convert(const char data, char * buff, char position)
{
	char temp = data;
	char dec = 0;
	while(temp >= 10)
	{
		temp -=10;
		++dec;
	}
	
	buff[(int)position] = dec + '0';
    buff[(int)(position + 1)] = temp + '0';
}

void read_uint8_temperature(uint8_t * data, char sensor)
{
	uint8_t temperature[2];
	uint8_t digit;
	
	temp_reset(sensor);
	send_byte(CMD_SKIPROM, sensor);
	send_byte(CMD_CONVERTTEMP, sensor);
	while(read_bit(sensor));
	temp_reset(sensor);
	send_byte(CMD_SKIPROM, sensor);
	send_byte(CMD_RSCRATCHPAD, sensor);
	
	temperature[0] = read_byte(sensor);
	temperature[1] = read_byte(sensor);
	temp_reset(sensor);
	
	digit = temperature[0] >> 4;
	digit |= (temperature[1]&0x7) << 4;
	*data = digit;
};
