#include <REGX51.H>
#include <stdio.h>

char putchar(char);
void delay(unsigned int);

unsigned short buffer;

sbit CLK = P2^0;
sbit DIN = P2^1;
sbit DOUT = P2^2;

void main()
{
	unsigned int i;
	SCON = 0x50;
	TMOD = 0x20;
	TCON = 0x40;
	TH1 = 243; //baud rate 2400
	TR1 = 1;
	ES = 1;
	RI = 1;
	TI = 1;
	
	CLK = 0;
	DIN = 0;
	while(1)
	{
		buffer = 0;
		for(i = 0; i < 12; i++)
		{
			buffer |= ((DOUT & 0xFF) << (11-i));
			CLK = 1;
			delay(5);
			CLK = 0;
			delay(5);
		}
		printf("%hu\n\r", buffer);
		delay(10);
	}
}

char putchar(char c)
{
	SBUF = c;
	while(!TI);
	TI = 0;
	return c;
}

void delay(unsigned int t)
{
	unsigned int i;
	unsigned char j;
	for(i = 0; i < t; i++)
	{
		for(j = 0; j < 255; j++);
	}
}