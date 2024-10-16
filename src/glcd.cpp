#include <stdint.h>
#include <Arduino.h>
#include <SPI.h>
#include "glcd.h"



GLCD::GLCD():
	sspin(SS)
{
	digitalWrite(GetSS(), LOW); //CS is Positive
}

GLCD::GLCD(uint8_t SSpin):
	sspin(SSpin)
{
	digitalWrite(GetSS(), LOW); //CS is Positive
}

void GLCD::begin()
{
	delay(100);
	WriteCommand(FUNCTION_SET | FUNCTION_8BIT);
	WriteCommand(DISPLAY_CONTROL | DISPLAY_ON);
	WriteCommand(CLEAR);
	WriteCommand(ENTRY_MODE | ENTRY_SHIFT_INCREASE);	
}

void GLCD::WriteCommand(uint8_t cmd)
{
	uint8_t buf[3];
	buf[0] = GLCD_CMD_SYNC;
	buf[1] = cmd & 0xF0U;
	buf[2] = (cmd << 4) & 0xF0U;

	digitalWrite(GetSS(), HIGH); //CS is Positive
	SPI.transfer(buf, 3);
	digitalWrite(GetSS(), LOW);
	
	delay(1);
}

void GLCD::WriteData(uint8_t data)
{
	uint8_t buf[3];
	buf[0] = GLCD_DAT_SYNC;
	buf[1] = data & 0xF0U;
	buf[2] = (data << 4) & 0xF0U;

	digitalWrite(GetSS(), HIGH); //CS is Positive
	SPI.transfer(buf, 3);
	digitalWrite(GetSS(), LOW);

	delay(1);
}

void GLCD::DibujaColumna(uint8_t columna, uint8_t *bufcol)
{
	WriteCommand(FUNCTION_SET | FUNCTION_8BIT | FUNCTION_EXTENDED);
	WriteCommand(EXTENDED_FUNCTION_SET | EXTENDED_8BIT | EXTENDED_SET | GRAPHIC_DISPLAY);

	if(columna < 32)
	{
		WriteCommand(SET_Y | columna);
		WriteCommand(SET_X1);
	}
	else
	{
		WriteCommand(SET_Y | (columna - 32));
		WriteCommand(SET_X2);
	}

	WriteCommand(EXTENDED_FUNCTION_SET | EXTENDED_8BIT | GRAPHIC_DISPLAY);

	for(int i = 0; i < 16; i++)
		WriteData(*bufcol++);
}

void GLCD::Dibuja(uint8_t *buffer)
{
	uint8_t col;
	uint8_t aux;
	for(col = 0, aux = 0; col < 64; col++, aux+=16);
		DibujaColumna(col, &buffer[aux]);
}

void GLCD::SetSS(uint8_t pin)
{
	sspin = pin;
}

int GLCD::GetSS()
{
	return sspin;
}