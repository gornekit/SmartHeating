/*
 * ds18b20.h
 *
 * Created: 07.09.2016 21:30:06
 *  Author: Дом
 */ 


#ifndef DS18B20_H_
#define DS18B20_H_

#include <avr/io.h>

#define F_CPU 8000000

#ifndef F_CPU
#error "Please define F_CPU"
#endif

#define PORT_TEMP PORTD
#define PIN_TEMP PIND
#define DDR_TEMP DDRD
#define P1_TEMP 6
#define P2_TEMP 5

#define INPUT_MODE(P_TEMP) (DDR_TEMP &= ~(1<<P_TEMP))
#define OUTPUT_MODE(P_TEMP) (DDR_TEMP |= (1<<P_TEMP))
#define SEND_HIGH_LVL(P_TEMP) (PORT_TEMP |= (1<<P_TEMP))
#define SEND_LOW_LVL(P_TEMP) (PORT_TEMP &= ~(1<<P_TEMP))

#define CMD_CONVERTTEMP 0x44
#define CMD_RSCRATCHPAD 0xbe
#define CMD_WSCRATCHPAD 0x4e
#define CMD_CPYSCRATCHPAD 0x48
#define CMD_RECEEPROM 0xb8
#define CMD_RPWRSUPPLY 0xb4
#define CMD_SEARCHROM 0xf0
#define CMD_READROM 0x33
#define CMD_MATCHROM 0x55
#define CMD_SKIPROM 0xcc
#define CMD_ALARMSEARCH 0xec

#define THERM_DECIMAL_STEPS_12BIT 625 //.0625

 char temp_reset(char sensor);
 void send_bit (char bit, char sensor);
 char read_bit(char sensor);
 char read_byte(char sensor);
 void send_byte(char byte, char sensor);
 void temp_read_temperature(char *buffer, char sensor);




#endif /* DS18B20_H_ */
