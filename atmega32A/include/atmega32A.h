#ifndef REAL_TIME
#define REAL_TIME

#define YEAR 16
#define MONTH 8
#define DAY 25
#define HOUR 12 
#define MIN 6
#define SEC 0

//#define F_CPU 8000000UL

typedef struct 
{
	char sec;
	char min;
	char hour;
	char day;
	char month;
	char year;
} my_time;

char time[16];

void board_init(); //Set up the MK

#endif //REAL_TIME 
