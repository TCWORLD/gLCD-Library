/*
	Sparkfun Nokia knockoff screen 128x128 controller.
	
	Written by Thomas Carpenter (2011)
	
	==================================================================================================
	Current Library Version: 2.5
	
	   Date    | Version | Changes
	-----------+---------+-----------------------------------------------------------------------------
	17/07/2012 |    2.5  | - Added the ability to have many custom characters.
			   |         |
	01/06/2012 |    2.4  | - Constructor method [gLCD(,,,)] uses built in port decoding from Arduino.h which means
			   |         |   that the correct port is automatically determined, and #defines have thus been removed.
			   |         |   This also improves compatibility with other boards including Teensy and Pro.
			   |         |
	18/01/2012 |    2.3  | - Update Phillips Init() call to also work with screens that would scan
			   |		 |   top to bottom before, and thus display fonts wrong (thanks github member: mumps)
			   |         |
	05/01/2012 |    2.2  | - Corrected printing of Wide fonts (thanks Sparkfun Member #8577)
			   |         |
	22/12/2011 |    2.1  | - updated twoPixels() to take 6 values (R1,G1,B1,R2,G2,B2) aswell as still being able
			   |         |   to take the 3 it did before (R1G1,B1R2,G2B2)
			   |         |
	03/12/2011 |    2.0  | - Contrast macro can now be called at any point in the program (as long as it is
			   |         |   AFTER the init() call). This means that the contrast can now be changed as many
			   |         |   times as you like during the program, without the need to reinitialise the screen.
			   |         | 
			   |         | - Library now supports Ardiuno 1.0
			   |         |
			   |---------|
			   |         |
	06/11/2011 |    1.4  | - Corrected the drawing of borders when the Box function is called, where before
	           |         |   it used to get the length of the x and y axis lines switched
			   |         | - Added two new functions: displayOff(), which turns the display off to save power,
			   |         |   and displayOn(), which turns it back on again.
	           |         |
	22/10/2011 |    1.3  | - Added ability to invert phillips display
			   |         |
	14/10/2011 |    1.2  | - Written a faster digital write set of functions. This speeds up the display by a factor of 10
			   |         |
	09/10/2011 |    1.1  | - Character data array is now stored in PROGMEM to free up 480Bytes of SRAM
			   |	1.0  | - Major rewrite of printing to screen which has massively increased performance.
			   |         |
	           |         | - Circles are now filled MUCH faster.
	           |         | - Test pattern renders even faster.
	           |         | - More control over colour of circles and boxes.
			   |         |
			   |---------|
	           |         |
	08/10/2011 |	0.8  | - Fixed Issue with Window() macro and the Epson controller - First pixel was drawn in wrong place.
			   |         |   This required changing the scan direction of the Epson screen, and of the Phillips screen so that
			   |         |   both render the same image in the same orientation.
			   |         | - testPattern() now more efficient and renders much faster.
			   |    0.7  | - Contrast depends heavily on the type of screen, so new function to set contrast has been added.
			   |         | - Added support for Phillips displays, and displays whose colour is inverted (i.e White = Black)
			   |    0.6  | - Fixed Lines not drawing correctly if Y1 > Y2
			   |    0.5  | - Added Examples to show how to use functions
			   |         | - Added Circle drawing algorithm
			   |         | - Can now select colour of the Line() and Plot() as foreground or background colour
			   |    0.4  | - Added co-ordinate offset. (On some displays, (0,0) is not visible) 
			   |         |   Window() function has had the offset built in, as all functions use
			   |         |   it to draw anything on the screen.
			   |         |   Offset is specified when calling Init();
	           |         |
	07/10/2011 |    0.3  | - Added testPattern Function.
	           |    0.2  | - Fixed functions not working correctly if X or Y were greater than 126.
			   |         | - Increased speed of software SPI
			   |         | - Added Version history
			   |         | - Simplified Box formatting
			   |         |
	06/10/2011 |    0.1  | - Initial library created with some basic functions
	           |         |
	
	===================================================================================================
	
	Wishlist/To Do:
		- Detect which controller the screen has		
		
		- Draw Triangles (Filled and Unfilled)
	
	===================================================================================================
	
	Functions:
		gLCD(RS,CS,SCLK,SDATA)
		gLCD(RS,CS,SCLK,SDATA,speed) - Connect screen pins. Reset, !Chip Select, Clock, and Data. Speed is optional and may be omitted
									       If speed is given (and is 1), then the FAST digital write will be used.
		
		Init(Xzero, Yzero, InvertColour) - Initialise the display. This may need changing for certain screens. 
										   Xzero and Yzero are (0,0) offset. Invert colour can be used if White
										   appears as black, which it does on some displays.(1 = Invert, 0 = Normal)
		Init(Xzero, Yzero, InvertColour, Phillips, xReverse) - If a fourth and fifth variable is defined, then the Phillips
															   routines will be used. The fifth variable mirrors in the x direction.
															   
															   xRevese controls how the phillips display will behave, and requires
															   some trial and error to get right.
															   First, try setting it to 0 and observe which way the screen prints
															   the image onto the screen.
															   -If it builds up the image from the LEFT(connector end is the top):
															    0 is correct.
															   -If it builds up from the RIGTH:
															    set it to 1 (it should now scan from the LEFT)
															   -If it builds up from the BOTTOM:
															    set it to 2 (it should now scan from the LEFT, else try 3)
															   -If it builds up from the TOP:
															    set it to 3 (it should now scan from the LEFT, else try 2)
		
		displayOff() - Turns the display off.
		displayOn() - Turns it back on again.
		
		testPattern() - Prints a colour table to check that all colours working properly.
		
		Contrast(contrast) - 'contrast' is a value between 0 and 63 (EPSON) or -63 and 63 (Phillips). 
							 If the Screen is too dark, or you cant see anything send a value >0x2B (<0x00 for Phillips). If you cant see all
							 the different colours distinctly on the test pattern, send a value <0x2B (<0x30 (but >0x00) for Phillips). The default values
							 should work for many screens, so you may not have to use this at all.
							 
							 Contrast() should be called BEFORE Init(). It is only needed if the display doesn't look right with just Init() alone.
							 
							 NOTE: after Init() has been called, Contrast will do nothing.
							
	
		Plot(X,Y,Colour) - Places a dot on the screen at (X,Y). If colour = 3, then it is in ForeColour. If colour = 0, then in BackColour
		
		Line(X1,Y1,X2,Y2,Colour) - Draws a line between (X1,Y1) and (X2,Y2) inclusive, in forground colour (Colour = 1) or background colour (Colour = 0)
		
		Box(X1,Y1,X2,Y2,format) - Draws a box from (X1,Y1) to (X2,Y2) inclusive. 
									format controls how the box will look (b7..b3 are ignored)
    
									  b2 | b1 | b0 | Meaning
									 ----+----+----+-----------------------------------------------------------------------------
									   0 |  1 |  x | Draws a box with just a border of colour BackColour
									 ----+----+----+-----------------------------------------------------------------------------
									   1 |  1 |  x | Draws a box with just a border of colour ForeColour
									 ----+----+----+-----------------------------------------------------------------------------
									   0 |  0 |  0 | Draws a box with border in BackColour and fill inside it with BackColour
									 ----+----+----+-----------------------------------------------------------------------------
									   1 |  0 |  0 | Draws a box with border in ForeColour and fill inside it with BackColour
									 ----+----+----+-----------------------------------------------------------------------------
									   0 |  0 |  1 | Draws a box with border in BackColour and fill inside it with ForeColour
									 ----+----+----+-----------------------------------------------------------------------------
									   1 |  0 |  1 | Draws a box with border in ForeColour and fill inside it with ForeColour
		
		Circle(X1,Y1,Radius,format) - Draws a Circle from (X1,Y1) with radius 'Radius'. 
									format controls how the box will look (b7..b3 are ignored)
    
									  b2 | b1 | b0 | Meaning
									 ----+----+----+-----------------------------------------------------------------------------
									   0 |  1 |  x | Draws a circle with just a border of colour BackColour
									 ----+----+----+-----------------------------------------------------------------------------
									   1 |  1 |  x | Draws a circle with just a border of colour ForeColour
									 ----+----+----+-----------------------------------------------------------------------------
									   0 |  0 |  0 | Draws a circle with border in BackColour and fill inside it with BackColour
									 ----+----+----+-----------------------------------------------------------------------------
									   1 |  0 |  0 | Draws a circle with border in ForeColour and fill inside it with BackColour
									 ----+----+----+-----------------------------------------------------------------------------
									   0 |  0 |  1 | Draws a circle with border in BackColour and fill inside it with ForeColour
									 ----+----+----+-----------------------------------------------------------------------------
									   1 |  0 |  1 | Draws a circle with border in ForeColour and fill inside it with ForeColour
									   
		Print(text,X,Y,Font) - Prints the string 'text' on to the display starting at (X,Y). There is no word wrap yet - maybe in the future
								Font controls the the look of the text and is as follows (b7..b3 are ignored - maybe future use)
								
									  b2 | b1 | b0 | Meaning
									 ----+----+----+---------------------------------------
									   0 |  x |  x | Text has transparent background
									 ----+----+----+---------------------------------------
									   1 |  x |  x | Text has solid background
									 ----+----+----+---------------------------------------
									   x |  0 |  0 | Text normal. (6 x 8 pixels)
									 ----+----+----+---------------------------------------
									   x |  0 |  1 | Text Wide. (12 x 8 pixels)
									 ----+----+----+---------------------------------------
									   x |  1 |  0 | Text Tall. (6 x 16 pixels)
									 ----+----+----+---------------------------------------
									   x |  1 |  1 | Text Tall and Wide. (12 x 16 pixels)
						
		Clear() - Blanks everything on display. All pixels go to background colour
		
		SetBackColour(R,G,B) - Sets the global RGB background colour. Doesn't affect anything already onscreen. R, G and B are 4bit long
		
		SetForeColour(R,G,B) - Sets the global RGB foreground colour. Doesn't affect anything already onscreen. R, G and B are 4bit long
*/

#ifndef gLCD_h
#define gLCD_h
	#if ARDUINO >= 100
	  #include "Arduino.h"
	#else
	  #include "WProgram.h"
	#endif

	class gLCD {
		public:
			gLCD(byte RS, byte CS, byte SCLK, byte SDATA, boolean speed = 0); //Constructor. 'speed' can be omitted in call. 
			//Macro function declarations
			void SetForeColour(char Red, char Green, char Blue);
			void SetBackColour(char Red, char Green, char Blue);
			void Clear();
			void Print(String text, unsigned char X1, unsigned char Y1, byte Font);
			void Plot(unsigned char X, unsigned char Y, char Colour);
			void Line(unsigned char X1, unsigned char Y1, unsigned char X2, unsigned char Y2, char Colour);
			void Box(unsigned char X1, unsigned char Y1, unsigned char X2, unsigned char Y2, unsigned char format);
			void Circle(unsigned char X1, unsigned char Y1, unsigned char Radius, unsigned char format);
			void Init(char Xzero, char Yzero, boolean InvertColour);
			void Init(char Xzero, char Yzero, boolean InvertColour, boolean Phillips, byte xReverse);
			void displayOn();
			void displayOff();
			void testPattern();
			void Contrast(signed char contrast);
			//This allows direct window writes, for example bitmap creation
			void twoPixels(byte SendR1G1, byte SendB1R2, byte SendG2B2);
			void twoPixels(byte SendR1, byte SendG1, byte SendB1, byte SendR2, byte SendG2, byte SendB2);
			void Window(unsigned char X1, unsigned char Y1, unsigned char X2, unsigned char Y2);
			void Configure(boolean normal); //1 = Normal, 0 = Bitmap (BMP files work best with this, though still a little buggy)
		private:
			//Macro function declarations			
			void writeRS(boolean bitValue);
			void writeCS(boolean bitValue);
			void writeSCLK(boolean bitValue);
			void writeSDATA(boolean bitValue);
			void SendByte(boolean Command, unsigned char data);
			void twoPixels(char Colour);
			void RedGreen(unsigned char X1, unsigned char Y1, unsigned char X2, unsigned char Y2);
			void GreenBlue(unsigned char X1, unsigned char Y1, unsigned char X2, unsigned char Y2);
			void BlueRed(unsigned char X1, unsigned char Y1, unsigned char X2, unsigned char Y2);
			void ColourBars(unsigned char X1, unsigned char Y1, unsigned char X2, unsigned char Y2);
			void CirclePlot(unsigned char X, unsigned char Y, unsigned char X1, unsigned char Y1, char Colour);
			void CircleFill(unsigned char X, unsigned char Y, unsigned char X1, unsigned char Y1, char Colour);

			//Variables
			int _RS;
			int _CS;
			int _SCLK;
			int _SDATA;
			volatile uint8_t* _RS_PORT;
			volatile uint8_t* _CS_PORT;
			volatile uint8_t* _SCLK_PORT;
			volatile uint8_t* _SDATA_PORT;
			byte _RS_HIGH;
			byte _CS_HIGH;
			byte _SCLK_HIGH;
			byte _SDATA_HIGH;
			byte _RS_LOW;
			byte _CS_LOW;
			byte _SCLK_LOW;
			byte _SDATA_LOW;
			boolean _fast;
			byte _normalScan;
			byte _inverseScan;
			
			char _SendRG;
			char _SendBR;
			char _SendGB;
			
			char _ForeRed;
			char _ForeGreen;
			char _ForeBlue;
			char _BackRed;
			char _BackGreen;
			char _BackBlue;
			
			char _parameter;
			char _command;
			
			char _Yzero;
			char _Xzero;
			
			signed char _contrast;
		public:
			char _Phillips;	
	};
#endif