#ifndef __GLCD_H__
#define __GLCD_H__

#define GLCD_CMD_SYNC	0xF8U
#define GLCD_DAT_SYNC	0xFAU

//Basic Commands
#define CLEAR					0x01U
#define HOME					0x02U
#define ENTRY_MODE				0x04U
#define DISPLAY_CONTROL			0x08U
#define CURSOR_DISPLAY_CONTROL	0x10U
#define FUNCTION_SET			0x20U
#define SET_CGRAM_ADDR			0x40U
#define SET_DDRAM_ADDR			0x80U

//Entry Mode Subcommands

#define ENTRY_SHIFT_DECREASE	0x01U
#define ENTRY_SHIFT_INCREASE	0x02U

//Display Control Subcommands
#define BLINK_ON		0x01U
#define CURSOR_ON		0x02U
#define DISPLAY_ON		0x04U

//Cursor Control Subcommands
#define CURSOR_SHIFT		0x08U
#define CURSOR_RIGHT		0x04U

//Function Subcommands
#define FUNCTION_8BIT		0x10U
#define FUNCTION_EXTENDED	0x04U

//Extended Function Subcommands
#define STAND_BY				0x01U
#define SET_SCROLL_OR_RAM		0x02U
#define REVERSE					0x04U
#define GLCD_SLEEP				0x08U
#define EXTENDED_FUNCTION_SET	0x20U
#define SET_SCROLL_OR_RAM_ADDR	0x40U
#define SET_GRAM_ADDR			0x80U

//Scroll Control
#define SCROLL_ENABLE		0x01U
#define RAM_ENABLE			0x00U

//Sleep Control

#define SLEEP_LEAVE		0x01U
#define SLEEP_ENTER		0x00U

//DDRAM Line Address

#define LINE_1			0x00U
#define LINE_2			0x10U
#define LINE_3			0x08U
#define LINE_4			0x18U

//DDRAM Line Control

#define DDRAM_L1		0x80U
#define DDRAM_L2		0x90U
#define DDRAM_L3		0x88U
#define DDRAM_L4		0x98U

//Extended Control Functions Subcommands

#define EXTENDED_8BIT		0x10U
#define EXTENDED_SET		0x04U
#define BASIC_SET			0x00U
#define GRAPHIC_DISPLAY		0x02U

//Graphic Coordinates

#define SET_Y			0x80U
#define SET_X1			0x80U
#define SET_X2			0x88U

class GLCD
{

	private:
		uint8_t sspin;
	public:

		GLCD();
		GLCD(uint8_t SSpin);

		void begin();
		void WriteCommand(uint8_t cmd);
		void WriteData(uint8_t data);
		void DibujaColumna(uint8_t columna, uint8_t *bufcol);
		void Dibuja(uint8_t *buffer);
		void SetSS(uint8_t pin);
		int GetSS();

};

#endif //__GLCD_H__