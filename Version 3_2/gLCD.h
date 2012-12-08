/*
	Sparkfun Nokia knockoff screen 128x128 controller.
	
	Written by Thomas Carpenter (2011->2012)
	
	==================================================================================================
	Current Library Version: 3.2
	
	   Date    | Version | Changes
	-----------+---------+-----------------------------------------------------------------------------
	22/10/2012 |    3.2  | - Updated the library to include support for the Arduino Due. Note however there is no 'High Speed'
			   |         |   mode on the Due, it uses digitalWrite() in either mode. This is not an issue as the due is very fast.
			   |         |
			   |         | - Added a simple character wrap feature which if selected as part of the font will begin continue printing
			   |         |   on subsequent lines if the text is too long to fit on the screen.
			   |         |
	06/10/2012 |    3.1  | - Added another driver type (EPSON_5). This is for screens that dont support the 3pixel/2byte mode.
			   |         |   For these a 4pixel/2byte mode is used. In order to not have constant checks for which type of data
			   |         |   mode is being used, there are seperate functions for each, the correct function is set via a function
			   |         |   pointer. This change is internal, so should not affect existing code.
			   |         |   Speed should also not be affected, however this has cost 0.5kB to 1kB of program space.
			   |         |
			   |         | - definitions for fonts and formats have been added to improve readability of user code.
			   |         |
	18/09/2012 |    3.0  | - The library has been converted to use the Arduino Print class allowing more familiar
			   |         |   calls such as print() and println() to be used, rather than the original Print(String,x,y,font).
			   |         |   The original function now gives an error message explaining the changes.
			   |         |
			   |         | - There are now global X1, Y1, X2 and Y2 variables, along with a global Font and Format. This
			   |         |   allows consecutive calls to the display functions without having to repeatedly specify these
			   |         |   variables.
			   |         |
			   |         | - Fixed the printing function so that the '\n' character moves to a new line on the screen.
			   |         |
			   |         | - Change the Init() function to be named begin() to more closely match the arduino style. The 
			   |         |   function is also now more common between the two displays (no extra variables), making it 
			   |         |   easier to follow.
			   |         |
			   |---------|
			   |         |
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
	22/12/2011 |    2.1  | - updated twoPixels() to take 6 values (R1,G1,B1,R2,G2,B2) as well as still being able
			   |         |   to take the 3 it did before (R1G1,B1R2,G2B2)
			   |         |
	03/12/2011 |    2.0  | - Contrast function can now be called at any point in the program (as long as it is
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
		
		begin(Xzero, Yzero, InvertColour, EPSON) 	  -		   Initialise the display. This may need changing for certain screens. 
															   Xzero and Yzero are (0,0) offset. Invert colour can be used if White
															   appears as black, which it does on some displays.(1 = Invert, 0 = Normal)
															   EPSON specifies that an Epson display is being used
															   
		begin(Xzero, Yzero, InvertColour, PHILLIPS_x) - 	   the last byte controls how the phillips display will behave, and requires
															   some trial and error to get right.
															   First, try setting it to PHILLIPS_0 and observe which way the screen prints
															   the image onto the screen.
															   -If it builds up the image from the LEFT(connector end is the top):
															    PHILLIPS_0 is correct.
															   -If it builds up from the RIGTH:
															    set it to PHILLIPS_1 (it should now scan from the LEFT)
															   -If it builds up from the BOTTOM:
															    set it to PHILLIPS_2 (it should now scan from the LEFT, else try PHILLIPS_3)
															   -If it builds up from the TOP:
															    set it to PHILLIPS_3 (it should now scan from the LEFT, else try PHILLIPS_2)
		
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
									   
		setFont(Font) - Sets the global font. Font is byte with each bit having a meaning. 
									These are as follows (b7..b3 are ignored)
								
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
		
		setBackColour(R,G,B) - Sets the global RGB background colour. Doesn't affect anything already onscreen. R, G and B are 4bit long
		
		setForeColour(R,G,B) - Sets the global RGB foreground colour. Doesn't affect anything already onscreen. R, G and B are 4bit long
*/

#ifndef gLCD_h
#define gLCD_h
	#if ARDUINO >= 100
	  #include "Arduino.h"
	#else
	  #include "WProgram.h"
	#endif
	
	#define GLCD_WHITE 0x0F0F0F
	#define GLCD_BLACK 0x000000
	#define GLCD_GREEN 0x000F00
	#define GLCD_LIME 0x080F00
	#define GLCD_BLUE 0x00000F
	#define GLCD_RED 0x0F0000
	#define GLCD_GREY 0x080808
	#define GLCD_ORANGE 0x0F0800
	#define GLCD_CYAN 0x000F0F
	#define GLCD_YELLOW 0x0F0F00
	#define GLCD_LEMON 0x0F0F08
	#define GLCD_MAGENTA 0x0F000F
	#define GLCD_PINK 0x0F0808
	
	typedef enum{
		EPSON_5 = 5,
		EPSON_4 = 4,
		EPSON = 4,
		PHILLIPS_3 = 3,
		PHILLIPS_2 = 2,
		PHILLIPS_1 = 1,
		PHILLIPS_0 = 0
	} DriverType;
	
	typedef enum{
		HIGH_SPEED = true,
		NORMAL_SPEED = false
	} SpeedMode;
	
	typedef enum{
		_parameter = 1,
		_command = 0
	} DataType;
	
	#define Normal_SolidBG_Wrap 0b1100
	#define Wide_SolidBG_Wrap 0b1101
	#define Tall_SolidBG_Wrap 0b1110
	#define Large_SolidBG_Wrap 0b1111
	#define Normal_ClearBG_Wrap 0b1000
	#define Wide_ClearBG_Wrap 0b1001
	#define Tall_ClearBG_Wrap 0b1010
	#define Large_ClearBG_Wrap 0b1011
	#define Normal_SolidBG 0b100
	#define Wide_SolidBG 0b101
	#define Tall_SolidBG 0b110
	#define Large_SolidBG 0b111
	#define Normal_ClearBG 0b000
	#define Wide_ClearBG 0b001
	#define Tall_ClearBG 0b010
	#define Large_ClearBG 0b011
	
	#define Wrap_Text 1
	
	#define OutlineBackColour 0b010
	#define OutlineForeColour 0b110
	#define SolidBackColour 0b000
	#define BorderForeColour_FillBackColour 0b100
	#define BorderBackColour_FillForeColour 0b001
	#define SolidForeColour 0b101
	
	class gLCD; //make function pointers valid.
	typedef void (gLCD::*TwoPixelsMode)();
	typedef void (gLCD::*SetSendColourMode)(char);
	
	class gLCD : public Print{
		private:
			SetSendColourMode setSendColour; //Function pointer to select which setSendColour is used
			TwoPixelsMode sendTwoPixels; //Function pointer to select which twoPixels is used
		public:
			gLCD(byte RS, byte CS, byte SCLK, byte SDATA, SpeedMode speed = NORMAL_SPEED); //Constructor. 'speed' can be omitted in call. 
			//function declarations
	#if ARDUINO >= 100
			virtual size_t write(const uint8_t *buffer, size_t size);//
			virtual size_t write(const uint8_t character);//
	#else
			virtual void write(const uint8_t *buffer, size_t size);//
			virtual void write(const uint8_t character);//
	#endif
			void begin(signed char Xzero, signed char Yzero, boolean InvertColour, DriverType driver);//
			void Contrast(signed char contrast);//
			void setForeColour(char Red, char Green, char Blue);//
			void setForeColour(unsigned long colour);
			void setBackColour(char Red, char Green, char Blue);//
			void setBackColour(unsigned long colour);
			void Clear();//
			void setFont(byte _Font);//
			void setFormat(byte _format);
			//void setFormat(unsigned char _format);//
			void setCoordinate(unsigned char X, unsigned char Y, byte pair = 1); //setCoordinate(X1,Y1), setCoordinate(X1,Y1,1), setCoordinate(X2,Y2,2)
			void setCoordinate(unsigned char _X1, unsigned char _Y1, unsigned char _X2, unsigned char _Y2);//
			void Plot(unsigned char _X1, unsigned char _Y1, unsigned char Colour);//
			void Plot(unsigned char _X1, unsigned char _Y1);//
			void Plot(unsigned char Colour);//
			void Plot();//
			void Line(unsigned char _X1, unsigned char _Y1, unsigned char _X2, unsigned char _Y2, byte _format);//
			void Line(unsigned char _X1, unsigned char _Y1, unsigned char _X2, unsigned char _Y2);//
			void Line(byte _format);//
			void Line();//
			void Box(unsigned char _X1, unsigned char _Y1, unsigned char _X2, unsigned char _Y2, byte _format);//
			void Box(unsigned char _X1, unsigned char _Y1, unsigned char _X2, unsigned char _Y2);//
			void Box(byte _format);//
			void Box();//
			void Circle(unsigned char _X1, unsigned char _Y1, unsigned char Radius, byte _format);//
			void Circle(unsigned char _X1, unsigned char _Y1, unsigned char Radius);//
			void Circle(unsigned char Radius, byte _format);//
			void Circle(unsigned char Radius);//
			void displayOn();//
			void displayOff();//
			void testPattern();//
			
			//This allows direct window writes, for example bitmap creation
			void twoPixels(byte SendR1G1, byte SendB1R2, byte SendG2B2, byte SendFourth); //Forth byte is only relevant for _EPSON_16bit
			void twoPixels(byte SendR1G1, byte SendB1R2, byte SendG2B2);
			void twoPixels(byte SendR1, byte SendG1, byte SendB1, byte SendR2, byte SendG2, byte SendB2);//
			void Window(unsigned char _X1, unsigned char _Y1, unsigned char _X2, unsigned char _Y2);//
			void Window();//
			void Configure(boolean normal); //1 = Normal, 0 = Bitmap (BMP files work best with this, though still a little buggy)
		private:
			void SendByte(DataType Command, unsigned char data);
			void setSendColour16bit(char Colour);
			void setSendColour12bit(char Colour);
			void two16bitPixels();
			void two12bitPixels();
			void twoPixels(char Colour);
			void RedGreen(unsigned char _X1, unsigned char _Y1, unsigned char _X2, unsigned char _Y2);
			void GreenBlue(unsigned char _X1, unsigned char _Y1, unsigned char _X2, unsigned char _Y2);
			void BlueRed(unsigned char _X1, unsigned char _Y1, unsigned char _X2, unsigned char _Y2);
			void ColourBars(unsigned char _X1, unsigned char _Y1, unsigned char _X2, unsigned char _Y2);
			void CirclePlot(unsigned char _X1, unsigned char _Y1, unsigned char _X2, unsigned char _Y2);
			void CircleFill(unsigned char _X1, unsigned char _Y1, unsigned char _X2, unsigned char _Y2);
			void systemPlot(unsigned char _X1, unsigned char _Y1, unsigned char Colour);//
			void systemPlot(unsigned char _X1, unsigned char _Y1);
			
			//Variables
			byte _RS;
			byte _CS;
			byte _SCLK;
			byte _SDATA;
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
			char _SendFourth; //This is used by EPSON_5 as they have a wierd 16bit colour arrangement.
			
			char _ForeRed;
			char _ForeGreen;
			char _ForeBlue;
			char _BackRed;
			char _BackGreen;
			char _BackBlue;
			
			char _Yzero;
			char _Xzero;
			
			byte Font;
			unsigned char format;
			unsigned char X1;
			unsigned char Y1;
			unsigned char X2;
			unsigned char Y2;
			
			signed char _contrast;
		public:
			char _Phillips;
			DriverType _driver;
	};
	
#endif