/**
 *****************************************************************************************
  * @file    ili9163.c
  * @brief   This code has been ported from the ili9163lcd library for avr made
  *			 by Simon Inns, to run on a msp430 and modified to HAL version by I.Trepacova
  ****************************************************************************************
  *
  * @author Simon Inns <simon.inns@gmail.com>
  * @author Christopher Vagnetoft (NoccyLabs)
  *	@copyright (C) 2012 Simon Inns
  * @copyright parts (C) 2012 NoccyLabs
  *
  *
  */

#ifndef ILI9163_C_
#define ILI9163_C_


#include "ili9163.h"
#include "font.h"

#include <string.h>

/**
 * @brief Function is used to register a callback to transmit function for SPI communication - separation of software and hardware parts\n
*/
void ILI9163_RegisterCallback(uint8_t *callback1) {

	if(callback1 != 0){
		ILI9163_SPI_TransmitData = callback1;
	}
}
/**
 * @brief Function is used to reset the display hardware\n
*/
void lcdReset(void)
{
	HAL_GPIO_WritePin(DISPLAY_RESET_PIN_GPIO_Port, DISPLAY_RESET_PIN_Pin, GPIO_PIN_RESET);
	HAL_Delay(100);

	HAL_GPIO_WritePin(DISPLAY_RESET_PIN_GPIO_Port, DISPLAY_RESET_PIN_Pin, GPIO_PIN_SET);
	HAL_Delay(100);
}
/**
 * @brief Function is used to write command to display.\n
 * @note Communication is done through the SPI interface.
*/
void lcdWriteCommand(uint8_t address)
{
	HAL_GPIO_WritePin(DISPLAY_CD_PIN_GPIO_Port, DISPLAY_CD_PIN_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(DISPLAY_CS_PIN_GPIO_Port, DISPLAY_CS_PIN_Pin, GPIO_PIN_RESET);
	ILI9163_SPI_TransmitData(&SD_SPI_HANDLE, &address, 1);
	HAL_GPIO_WritePin(DISPLAY_CS_PIN_GPIO_Port, DISPLAY_CS_PIN_Pin, GPIO_PIN_SET);
}

/**
 * @brief The function is used to write the command parameter to the display.\n
 * @note Communication is done through the SPI interface.
*/
void lcdWriteParameter(uint8_t parameter)
{
	HAL_GPIO_WritePin(DISPLAY_CD_PIN_GPIO_Port, DISPLAY_CD_PIN_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(DISPLAY_CS_PIN_GPIO_Port, DISPLAY_CS_PIN_Pin, GPIO_PIN_RESET);
	ILI9163_SPI_TransmitData(&SD_SPI_HANDLE, &parameter, 1);
	HAL_GPIO_WritePin(DISPLAY_CS_PIN_GPIO_Port, DISPLAY_CS_PIN_Pin, GPIO_PIN_SET);
}

/**
 * @brief The function is used to write the command data to the display.\n
 * @note Communication is done through the SPI interface.
*/
void lcdWriteData(uint8_t dataByte1, uint8_t dataByte2)
{
	HAL_GPIO_WritePin(DISPLAY_CD_PIN_GPIO_Port, DISPLAY_CD_PIN_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(DISPLAY_CS_PIN_GPIO_Port, DISPLAY_CS_PIN_Pin, GPIO_PIN_RESET);
	ILI9163_SPI_TransmitData(&SD_SPI_HANDLE, &dataByte1, 1);
	ILI9163_SPI_TransmitData(&SD_SPI_HANDLE, &dataByte2, 1);
	HAL_GPIO_WritePin(DISPLAY_CS_PIN_GPIO_Port, DISPLAY_CS_PIN_Pin, GPIO_PIN_SET);
}


/**
 * @brief The function is used to initialise display.\n
 * @param[in] orientation -> Display orientation
*/
void lcdInitialise(uint8_t orientation)
{

	// Hardware reset the LCD
	lcdReset();

    lcdWriteCommand(EXIT_SLEEP_MODE);
    HAL_Delay(100); //Delay(10000); // Wait for the screen to wake up

    lcdWriteCommand(SET_PIXEL_FORMAT);
    lcdWriteParameter(0x05); // 16 bits per pixel

    lcdWriteCommand(SET_GAMMA_CURVE);
    lcdWriteParameter(0x04); // Select gamma curve 3

    lcdWriteCommand(GAM_R_SEL);
    lcdWriteParameter(0x01); // Gamma adjustment enabled

    lcdWriteCommand(POSITIVE_GAMMA_CORRECT);
    lcdWriteParameter(0x3f); // 1st Parameter
    lcdWriteParameter(0x25); // 2nd Parameter
    lcdWriteParameter(0x1c); // 3rd Parameter
    lcdWriteParameter(0x1e); // 4th Parameter
    lcdWriteParameter(0x20); // 5th Parameter
    lcdWriteParameter(0x12); // 6th Parameter
    lcdWriteParameter(0x2a); // 7th Parameter
    lcdWriteParameter(0x90); // 8th Parameter
    lcdWriteParameter(0x24); // 9th Parameter
    lcdWriteParameter(0x11); // 10th Parameter
    lcdWriteParameter(0x00); // 11th Parameter
    lcdWriteParameter(0x00); // 12th Parameter
    lcdWriteParameter(0x00); // 13th Parameter
    lcdWriteParameter(0x00); // 14th Parameter
    lcdWriteParameter(0x00); // 15th Parameter

    lcdWriteCommand(NEGATIVE_GAMMA_CORRECT);
    lcdWriteParameter(0x20); // 1st Parameter
    lcdWriteParameter(0x20); // 2nd Parameter
    lcdWriteParameter(0x20); // 3rd Parameter
    lcdWriteParameter(0x20); // 4th Parameter
    lcdWriteParameter(0x05); // 5th Parameter
    lcdWriteParameter(0x00); // 6th Parameter
    lcdWriteParameter(0x15); // 7th Parameter
    lcdWriteParameter(0xa7); // 8th Parameter
    lcdWriteParameter(0x3d); // 9th Parameter
    lcdWriteParameter(0x18); // 10th Parameter
    lcdWriteParameter(0x25); // 11th Parameter
    lcdWriteParameter(0x2a); // 12th Parameter
    lcdWriteParameter(0x2b); // 13th Parameter
    lcdWriteParameter(0x2b); // 14th Parameter
    lcdWriteParameter(0x3a); // 15th Parameter

    lcdWriteCommand(FRAME_RATE_CONTROL1);
    lcdWriteParameter(0x08); // DIVA = 8
    lcdWriteParameter(0x08); // VPA = 8

    lcdWriteCommand(DISPLAY_INVERSION);
    lcdWriteParameter(0x07); // NLA = 1, NLB = 1, NLC = 1 (all on Frame Inversion)

    lcdWriteCommand(POWER_CONTROL1);
    lcdWriteParameter(0x0a); // VRH = 10:  GVDD = 4.30
    lcdWriteParameter(0x02); // VC = 2: VCI1 = 2.65

    lcdWriteCommand(POWER_CONTROL2);
    lcdWriteParameter(0x02); // BT = 2: AVDD = 2xVCI1, VCL = -1xVCI1, VGH = 5xVCI1, VGL = -2xVCI1

    lcdWriteCommand(VCOM_CONTROL1);
    lcdWriteParameter(0x50); // VMH = 80: VCOMH voltage = 4.5
    lcdWriteParameter(0x5b); // VML = 91: VCOML voltage = -0.225

    lcdWriteCommand(VCOM_OFFSET_CONTROL);
    lcdWriteParameter(0x40); // nVM = 0, VMF = 64: VCOMH output = VMH, VCOML output = VML

    lcdWriteCommand(SET_COLUMN_ADDRESS);
    lcdWriteParameter(0x00); // XSH
    lcdWriteParameter(0x00); // XSL
    lcdWriteParameter(0x00); // XEH
    lcdWriteParameter(0x7f); // XEL (128 pixels x)

    lcdWriteCommand(SET_PAGE_ADDRESS);
    lcdWriteParameter(0x00);
    lcdWriteParameter(0x00);
    lcdWriteParameter(0x00);
    lcdWriteParameter(0x7f); // 128 pixels y

	// Select display orientation
    lcdWriteCommand(SET_ADDRESS_MODE);
	lcdWriteParameter(orientation);

	// Set the display to on
    lcdWriteCommand(SET_DISPLAY_ON);
    lcdWriteCommand(WRITE_MEMORY_START);
}

// LCD graphics functions -----------------------------------------------------------------------------------
/**
 * @brief The function is used to clear the display and change the colour of background.\n
 * @param[in] colour -> background colour
*/
void lcdClearDisplay(uint16_t colour)
{
	uint16_t pixel;

	// Set the column address to 0-127
	lcdWriteCommand(SET_COLUMN_ADDRESS);
	lcdWriteParameter(0x00);
	lcdWriteParameter(0x00);
	lcdWriteParameter(0x00);
	lcdWriteParameter(0x7f);

	// Set the page address to 0-127
	lcdWriteCommand(SET_PAGE_ADDRESS);
	lcdWriteParameter(0x00);
	lcdWriteParameter(0x00);
	lcdWriteParameter(0x00);
	lcdWriteParameter(0x7f);

	// Plot the pixels
	lcdWriteCommand(WRITE_MEMORY_START);
	for(pixel = 0; pixel < 16385; pixel++)
	{
		lcdWriteData(colour >> 8, colour);
	}
}

/**
 * @brief The function is used to plot on the display with the selected color.\n
 *  @param[in] x -> x coordinate
 *  @param[in] y -> y coordinate
 *  @param[in] colour -> colour
*/
void lcdPlot(uint8_t x, uint8_t y, uint16_t colour)
{
	// Horizontal Address Start Position
	lcdWriteCommand(SET_COLUMN_ADDRESS);
	lcdWriteParameter(0x00);
	lcdWriteParameter(x);
	lcdWriteParameter(0x00);
	lcdWriteParameter(0x7f);

	// Vertical Address end Position
	lcdWriteCommand(SET_PAGE_ADDRESS);
	lcdWriteParameter(0x00);
	lcdWriteParameter(y);
	lcdWriteParameter(0x00);
	lcdWriteParameter(0x7f);//7f

	// Plot the point
	lcdWriteCommand(WRITE_MEMORY_START);
	lcdWriteData(colour >> 8, colour);
}

/**
 * @brief The function is used to draw line from x0, y0 to x1, y1 (from left to right) on the display with the selected color.\n
 *  @param[in] x0 -> the starting x-coordinate
 *  @param[in] y0 -> the starting y-coordinate
 *  @param[in] x1 -> the end x-coordinate
 *  @param[in] y1 -> the end y-coordinate
 *  @param[in] colour -> colour
*/
void lcdLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t colour)
{
	int16_t dy = y1 - y0;
	int16_t dx = x1 - x0;
	int16_t stepx, stepy;

	if (dy < 0)
	{
		dy = -dy; stepy = -1;
	}
	else stepy = 1;

 	if (dx < 0)
	{
		dx = -dx; stepx = -1;
	}
	else stepx = 1;

	dy <<= 1; 							// dy is now 2*dy
	dx <<= 1; 							// dx is now 2*dx

	lcdPlot(x0, y0, colour);

	if (dx > dy) {
		int fraction = dy - (dx >> 1);	// same as 2*dy - dx
		while (x0 != x1)
		{
			if (fraction >= 0)
			{
				y0 += stepy;
				fraction -= dx; 		// same as fraction -= 2*dx
			}

   			x0 += stepx;
   			fraction += dy; 				// same as fraction -= 2*dy
   			lcdPlot(x0, y0, colour);
		}
	}
	else
	{
		int fraction = dx - (dy >> 1);
		while (y0 != y1)
		{
			if (fraction >= 0)
			{
				x0 += stepx;
				fraction -= dy;
			}

			y0 += stepy;
			fraction += dx;
			lcdPlot(x0, y0, colour);
		}
	}
}

/**
 * @brief The function is used to draw a rectangle between x0, y0 and x1, y1 on the display with the selected color.\n
 *  @param[in] x0 -> the starting x-coordinate
 *  @param[in] y0 -> the starting y-coordinate
 *  @param[in] x1 -> the end x-coordinate
 *  @param[in] y1 -> the end y-coordinate
 *  @param[in] colour -> colour
*/
void lcdRectangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t colour)
{
	lcdLine(x0, y0, x0, y1, colour);
	lcdLine(x0, y1, x1, y1, colour);
	lcdLine(x1, y0, x1, y1, colour);
	lcdLine(x0, y0, x1, y0, colour);
}

/**
 * @brief The function is used to draw a filled rectangle between x0, y0 and x1, y1 on the display with the selected color.\n
 * @note  y1 must be greater than y0  and x1 must be greater than x0
 *  @param[in] x0 -> the starting x-coordinate
 *  @param[in] y0 -> the starting y-coordinate
 *  @param[in] x1 -> the end x-coordinate
 *  @param[in] y1 -> the end y-coordinate
 *  @param[in] colour -> colour
*/
void lcdFilledRectangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t colour)
{
	uint16_t pixels;

	// To speed up plotting we define a x window with the width of the
	// rectangle and then just output the required number of bytes to
	// fill down to the end point

	lcdWriteCommand(SET_COLUMN_ADDRESS); // Horizontal Address Start Position
	lcdWriteParameter(0x00);
	lcdWriteParameter(x0);
	lcdWriteParameter(0x00);
	lcdWriteParameter(x1);

	lcdWriteCommand(SET_PAGE_ADDRESS); // Vertical Address end Position
	lcdWriteParameter(0x00);
	lcdWriteParameter(y0);
	lcdWriteParameter(0x00);
	lcdWriteParameter(y1);

	lcdWriteCommand(WRITE_MEMORY_START);

	for (pixels = 0; pixels < ((x1 - x0) * (y1 - y0)); pixels++)
		lcdWriteData(colour >> 8, colour);;
}

/**
 * @brief The function is used to draw a circle on the display with the selected color.\n
 *  @param[in] xCentre -> x-coordinate of center
 *  @param[in] yCentre -> y-coordinate of center
 *  @param[in] radius -> radius of the circle
 *  @param[in] colour -> colour
*/
void lcdCircle(int16_t xCentre, int16_t yCentre, int16_t radius, uint16_t colour)
{
	int16_t x = 0, y = radius;
	int16_t d = 3 - (2 * radius);

    while(x <= y)
	{
		lcdPlot(xCentre + x, yCentre + y, colour);
		lcdPlot(xCentre + y, yCentre + x, colour);
		lcdPlot(xCentre - x, yCentre + y, colour);
		lcdPlot(xCentre + y, yCentre - x, colour);
		lcdPlot(xCentre - x, yCentre - y, colour);
		lcdPlot(xCentre - y, yCentre - x, colour);
		lcdPlot(xCentre + x, yCentre - y, colour);
		lcdPlot(xCentre - y, yCentre + x, colour);

		if (d < 0) d += (4 * x) + 6;
		else
		{
			d += (4 * (x - y)) + 10;
			y -= 1;
		}

		x++;
	}
}

// LCD text manipulation functions --------------------------------------------------------------------------
#define pgm_read_byte_near(address_short) (uint16_t)(address_short)
//

/**
 * @brief The function is used to plot a character at the specified x, y coordinates (top left hand corner of character).\n
 * @details Among the input parameters is the choice of the background color and the color of the character.
 *  @param[in] character -> character
 *  @param[in] x -> x-coordinate
 *  @param[in] y -> y-coordinate
 *  @param[in] fgColour -> colour of character
 *  @param[in] bgColour -> background colour of character
*/
void lcdPutCh(unsigned char character, uint8_t x, uint8_t y, uint16_t fgColour, uint16_t bgColour)
{
	uint8_t row, column;

	// To speed up plotting we define a x window of 6 pixels and then
	// write out one row at a time.  This means the LCD will correctly
	// update the memory pointer saving us a good few bytes

	lcdWriteCommand(SET_COLUMN_ADDRESS); // Horizontal Address Start Position
	lcdWriteParameter(0x00);
	lcdWriteParameter(x);
	lcdWriteParameter(0x00);
	lcdWriteParameter(x+5);

	lcdWriteCommand(SET_PAGE_ADDRESS); // Vertical Address end Position
	lcdWriteParameter(0x00);
	lcdWriteParameter(y);
	lcdWriteParameter(0x00);
	lcdWriteParameter(0x7f);

	lcdWriteCommand(WRITE_MEMORY_START);

	// Plot the font data
	for (row = 0; row < 8; row++)
	{
		for (column = 0; column < 6; column++)
		{
			//if ((font5x8[character][column]) & (1 << row))
			if ((fontus[character][column]) & (1 << row))
				lcdWriteData(fgColour>>8, fgColour);
			else lcdWriteData(bgColour >> 8, bgColour);
		}
	}
}

/**
 * @brief The function is used to translate a 3 byte RGB value into a 2 byte value for the display (values should be 0-31).\n
 *  @param[in] r -> R value
 *  @param[in] x -> G value
 *  @param[in] y -> B value
*/
uint16_t decodeRgbValue(uint8_t r, uint8_t g, uint8_t b)
{
	return (b << 11) | (g << 6) | (r);
}


/**
 * @brief The function is used to takes a row number from 0 to 20 and returns the x coordinate on the screen (0-127) to make it easy to place text. \n
*/
uint8_t lcdTextX(uint8_t x) { return x*6; }

/**
 * @brief The function is used to takes a row number from 0 to 20 and returns the y coordinate on the screen (0-127) to make it easy to place text. \n
*/
uint8_t lcdTextY(uint8_t y) { return y*8; }

/**
 * @brief The function is used to plot a string of characters on the display\n
 *  @param[in] *string -> pointer string of characters
 *  @param[in] x -> x-coordinate
 *  @param[in] y -> y-coordinate
 *  @param[in] fgColour -> colour of string
 *  @param[in] bgColour -> background colour of string
*/
void lcdPutS(const char *string, uint8_t x, uint8_t y, uint16_t fgColour, uint16_t bgColour)
{
	uint8_t origin = x;
	uint8_t characterNumber;

	for (characterNumber = 0; characterNumber < strlen(string); characterNumber++)
	{
		// Check if we are out of bounds and move to
		// the next line if we are
		if (x > 121)
		{
			x = origin;
			y += 8;
		}

		// If we move past the bottom of the screen just exit
		if (y > 120) break;

		// Plot the current character
		lcdPutCh(string[characterNumber], x, y, fgColour, bgColour);
		x += 6;
	}
}


#endif /* ILI9163_C_ */
