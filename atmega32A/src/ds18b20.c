/*
 * ds18b20.c
 *
 * Created: 07.09.2016 21:28:06
 *  Author: Дом
 */ 

#include "ds18b20.h"
#include <util/delay.h>
#include <stdio.h>

 char temp_reset(char sensor)
 {
	 char res;
	 OUTPUT_MODE(sensor);
	 SEND_LOW_LVL(sensor);
	 _delay_us(480);
	 
	 INPUT_MODE(sensor);
	 _delay_us(60);
	 res = (PIN_TEMP & (1 << sensor));
	 _delay_us(420);
	 
	 return res;
 }
 
 void send_bit (char bit, char sensor)
 {
	 OUTPUT_MODE(sensor);
	 SEND_LOW_LVL(sensor);
	 _delay_us(1);
	 
	 if(bit)
		INPUT_MODE(sensor);
	_delay_us(60);
	INPUT_MODE(sensor);
		
 }
 
 char read_bit(char sensor)
 {
	 char bit = 0;
	 OUTPUT_MODE(sensor);
	 SEND_LOW_LVL(sensor);
	 _delay_us(1);
	 
	 INPUT_MODE(sensor);
	 _delay_us(14);
	 
	 if(PIN_TEMP & (1 << sensor))
		bit = 1;
	
	_delay_us(45);
	return bit;
 }
 
 char read_byte(char sensor)
 {
	 char byte = 0;
	 char i = 8;
	 
	 while(i--)
	 {
		 byte >>= 1;
		 byte |= (read_bit(sensor) << 7);
	 }
	 return byte;
 }
 
 void send_byte(char byte, char sensor)
 {
	 char i = 8;
	 while(i--)
	 {
		 send_bit(byte & 1, sensor);
		 byte >>= 1;
	 }
 }
 
 void temp_read_temperature(char *buffer, char sensor)
{
	 uint8_t temperature[2];
	 int8_t digit;
	 uint16_t decimal;
	 
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
	 
	 digit=temperature[0]>>4;
	 digit|=(temperature[1]&0x7)<<4;
	 
	 decimal = temperature[0]&0xf;
	 decimal *= THERM_DECIMAL_STEPS_12BIT;
	 decimal /= 100;
	 
	 //PORTA = digit;
	 //PORTB = decimal >> 8;
	 
	 sprintf(buffer, "%d.%02u C", digit, decimal);
 }
