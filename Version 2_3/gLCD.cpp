/*
	Sparkfun Nokia knockoff screen 128x128 controller. Should work with (all) screens.
	
	Code written by Thomas Carpenter (2011)
	
	See header file for function descriptions and ChangeLog
	
*/
#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif
#include "gLCD.h"
#include <avr/pgmspace.h>

	//Character Database store
byte charData[105][5] PROGMEM = {
	{0x00 , 0x00 , 0x00 , 0x00 , 0x00 }, // 32 = <space>
	{0x00 , 0x06 , 0x5F , 0x06 , 0x00 }, // 33 = !
	{0x07 , 0x03 , 0x00 , 0x07 , 0x03 }, // 34 = "
	{0x24 , 0x7E , 0x24 , 0x7E , 0x24 }, // 35 = #
	{0x24 , 0x2B , 0x6A , 0x12 , 0x00 }, // 36 = $
	{0x63 , 0x13 , 0x08 , 0x64 , 0x63 }, // 37 = %
	{0x36 , 0x49 , 0x56 , 0x20 , 0x50 }, // 38 = &
	{0x00 , 0x07 , 0x03 , 0x00 , 0x00 }, // 39 = '
	{0x00 , 0x3E , 0x41 , 0x00 , 0x00 }, // 40 = (
	{0x00 , 0x41 , 0x3E , 0x00 , 0x00 }, // 41 = )
	{0x08 , 0x3E , 0x1C , 0x3E , 0x08 }, // 42 = *
	{0x08 , 0x08 , 0x3E , 0x08 , 0x08 }, // 43 = +
	{0x00 , 0xE0 , 0x60 , 0x00 , 0x00 }, // 44 = ,
	{0x08 , 0x08 , 0x08 , 0x08 , 0x08 }, // 45 = -
	{0x00 , 0x60 , 0x60 , 0x00 , 0x00 }, // 46 = .
	{0x20 , 0x10 , 0x08 , 0x04 , 0x02 }, // 47 = /
	{0x3E , 0x51 , 0x49 , 0x45 , 0x3E }, // 48 = 0
	{0x00 , 0x42 , 0x7F , 0x40 , 0x00 }, // 49 = 1
	{0x62 , 0x51 , 0x49 , 0x49 , 0x46 }, // 50 = 2
	{0x22 , 0x49 , 0x49 , 0x49 , 0x36 }, // 51 = 3
	{0x18 , 0x14 , 0x12 , 0x7F , 0x10 }, // 52 = 4
	{0x2F , 0x49 , 0x49 , 0x49 , 0x31 }, // 53 = 5
	{0x3C , 0x4A , 0x49 , 0x49 , 0x30 }, // 54 = 6
	{0x01 , 0x71 , 0x09 , 0x05 , 0x03 }, // 55 = 7
	{0x36 , 0x49 , 0x49 , 0x49 , 0x36 }, // 56 = 8
	{0x06 , 0x49 , 0x49 , 0x29 , 0x1E }, // 57 = 9
	{0x00 , 0x6C , 0x6C , 0x00 , 0x00 }, // 58 = :
	{0x00 , 0xEC , 0x6C , 0x00 , 0x00 }, // 59 = ;
	{0x08 , 0x14 , 0x22 , 0x41 , 0x00 }, // 60 = <
	{0x24 , 0x24 , 0x24 , 0x24 , 0x24 }, // 61 = =
	{0x00 , 0x41 , 0x22 , 0x14 , 0x08 }, // 62 = >
	{0x02 , 0x01 , 0x59 , 0x09 , 0x06 }, // 63 = ?
	{0x3E , 0x41 , 0x5D , 0x55 , 0x1E }, // 64 = @
	{0x7E , 0x09 , 0x09 , 0x09 , 0x7E }, // 65 = A
	{0x7F , 0x49 , 0x49 , 0x49 , 0x36 }, // 66 = B
	{0x3E , 0x41 , 0x41 , 0x41 , 0x22 }, // 67 = C
	{0x7F , 0x41 , 0x41 , 0x41 , 0x3E }, // 68 = D
	{0x7F , 0x49 , 0x49 , 0x49 , 0x41 }, // 69 = E
	{0x7F , 0x09 , 0x09 , 0x09 , 0x01 }, // 70 = F
	{0x3E , 0x41 , 0x49 , 0x49 , 0x7A }, // 71 = G
	{0x7F , 0x08 , 0x08 , 0x08 , 0x7F }, // 72 = H
	{0x00 , 0x41 , 0x7F , 0x41 , 0x00 }, // 73 = I
	{0x30 , 0x40 , 0x40 , 0x40 , 0x3F }, // 74 = J
	{0x7F , 0x08 , 0x14 , 0x22 , 0x41 }, // 75 = K
	{0x7F , 0x40 , 0x40 , 0x40 , 0x40 }, // 76 = L
	{0x7F , 0x02 , 0x04 , 0x02 , 0x7F }, // 77 = M
	{0x7F , 0x02 , 0x04 , 0x08 , 0x7F }, // 78 = N
	{0x3E , 0x41 , 0x41 , 0x41 , 0x3E }, // 79 = O
	{0x7F , 0x09 , 0x09 , 0x09 , 0x06 }, // 80 = P
	{0x3E , 0x41 , 0x51 , 0x21 , 0x5E }, // 81 = Q
	{0x7F , 0x09 , 0x09 , 0x19 , 0x66 }, // 82 = R
	{0x26 , 0x49 , 0x49 , 0x49 , 0x32 }, // 83 = S
	{0x01 , 0x01 , 0x7F , 0x01 , 0x01 }, // 84 = T
	{0x3F , 0x40 , 0x40 , 0x40 , 0x3F }, // 85 = U
	{0x1F , 0x20 , 0x40 , 0x20 , 0x1F }, // 86 = V
	{0x3F , 0x40 , 0x3C , 0x40 , 0x3F }, // 87 = W
	{0x63 , 0x14 , 0x08 , 0x14 , 0x63 }, // 88 = X
	{0x07 , 0x08 , 0x70 , 0x08 , 0x07 }, // 89 = Y
	{0x71 , 0x49 , 0x45 , 0x43 , 0x00 }, // 90 = Z
	{0x00 , 0x7F , 0x41 , 0x41 , 0x00 }, // 91 = [
	{0x02 , 0x04 , 0x08 , 0x10 , 0x20 }, // 92 = <backslash>
	{0x00 , 0x41 , 0x41 , 0x7F , 0x00 }, // 93 = ]
	{0x04 , 0x02 , 0x01 , 0x02 , 0x04 }, // 94 = ^
	{0x80 , 0x80 , 0x80 , 0x80 , 0x80 }, // 95 = _
	{0x00 , 0x03 , 0x07 , 0x00 , 0x00 }, // 96 = `
	{0x20 , 0x54 , 0x54 , 0x54 , 0x78 }, // 97 = a
	{0x7F , 0x44 , 0x44 , 0x44 , 0x38 }, // 98 = b
	{0x38 , 0x44 , 0x44 , 0x44 , 0x28 }, // 99 = c
	{0x38 , 0x44 , 0x44 , 0x44 , 0x7F }, // 100 = d
	{0x38 , 0x54 , 0x54 , 0x54 , 0x18 }, // 101 = e
	{0x08 , 0x7E , 0x09 , 0x09 , 0x00 }, // 102 = f
	{0x18 , 0xA4 , 0xA4 , 0xA4 , 0x7C }, // 103 = g
	{0x7F , 0x04 , 0x04 , 0x78 , 0x00 }, // 104 = h
	{0x00 , 0x00 , 0x7D , 0x00 , 0x00 }, // 105 = i
	{0x40 , 0x80 , 0x84 , 0x7D , 0x00 }, // 106 = j
	{0x7F , 0x10 , 0x28 , 0x44 , 0x00 }, // 107 = k
	{0x00 , 0x00 , 0x7F , 0x40 , 0x00 }, // 108 = l
	{0x7C , 0x04 , 0x18 , 0x04 , 0x78 }, // 109 = m
	{0x7C , 0x04 , 0x04 , 0x78 , 0x00 }, // 110 = n
	{0x38 , 0x44 , 0x44 , 0x44 , 0x38 }, // 111 = o
	{0xFC , 0x44 , 0x44 , 0x44 , 0x38 }, // 112 = p
	{0x38 , 0x44 , 0x44 , 0x44 , 0xFC }, // 113 = q
	{0x44 , 0x78 , 0x44 , 0x04 , 0x08 }, // 114 = r
	{0x08 , 0x54 , 0x54 , 0x54 , 0x20 }, // 115 = s
	{0x04 , 0x3E , 0x44 , 0x24 , 0x00 }, // 116 = t
	{0x3C , 0x40 , 0x20 , 0x7C , 0x00 }, // 117 = u
	{0x1C , 0x20 , 0x40 , 0x20 , 0x1C }, // 118 = v
	{0x3C , 0x60 , 0x30 , 0x60 , 0x3C }, // 119 = w
	{0x6C , 0x10 , 0x10 , 0x6C , 0x00 }, // 120 = x
	{0x9C , 0xA0 , 0x60 , 0x3C , 0x00 }, // 121 = y
	{0x64 , 0x54 , 0x54 , 0x4C , 0x00 }, // 122 = z
	{0x08 , 0x3E , 0x41 , 0x41 , 0x00 }, // 123 = {
	{0x00 , 0x00 , 0x7F , 0x00 , 0x00 }, // 124 = |
	{0x00 , 0x41 , 0x41 , 0x3E , 0x08 }, // 125 = }
	{0x02 , 0x01 , 0x02 , 0x01 , 0x00 }, // 126 = ~
	
	//Custom Non-ASCII charaters
	
	{0x02 , 0x6F , 0x1A , 0x30 , 0x6E }, // 127 = Shuffle
	{0x3C , 0x62 , 0x47 , 0x62 , 0x38 }, // 128 = Repeat
	{0x3E , 0x3E , 0x3E , 0x3E , 0x3E }, // 129 = Stop
	{0x00 , 0x7F , 0x3E , 0x1C , 0x08 }, // 130 = Play
	{0x3E , 0x3E , 0x00 , 0x3E , 0x3E }, // 131 = Pause
	{0x7F , 0x3E , 0x1C , 0x08 , 0x7F }, // 132 = Skip
	{0x1C , 0x3E , 0x7F , 0x00 , 0x1C }, // 133 = Volume
	{0x1C , 0x3E , 0x7F , 0x00 , 0x00 }, // 134 = Mute
	{0x3C , 0x60 , 0x4F , 0x60 , 0x3C }  // 135 = Power
};

gLCD::gLCD(byte RS, byte CS, byte SCLK, byte SDATA){
	pinMode(RS, OUTPUT);
	_RS = RS;
	pinMode(CS, OUTPUT);
	_CS = CS;
	pinMode(SCLK, OUTPUT);
	_SCLK = SCLK;
	pinMode(SDATA, OUTPUT);
	_SDATA = SDATA;
	
	_parameter = 1;
	_command = 0;
	
	_contrast = 126; //In otherwords, use default unless told otherwise
	
	//_LCDwidth = 132;
	//_LCDheight = 132;
}

gLCD::gLCD(byte RS, byte CS, byte SCLK, byte SDATA, boolean speed){
	_fast = speed;

	pinMode(RS, OUTPUT);
	_RS = RS;
	pinMode(CS, OUTPUT);
	_CS = CS;
	pinMode(SCLK, OUTPUT);
	_SCLK = SCLK;
	pinMode(SDATA, OUTPUT);
	_SDATA = SDATA;

  #if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
	if (speed){//Calculate pin registers.
		if ((RS > 9)&&(RS < 14)){
			_RS_HIGH = 1 << (RS - 6);
			_RS_LOW = ~_RS_HIGH;
		} else if ((RS > 5)&&(RS < 10)){
			_RS_HIGH = 1 << (RS - 3);
			_RS_LOW = ~_RS_HIGH;
		} else if (RS == 4){
			_RS_HIGH = 1 << (RS + 1);
			_RS_LOW = ~_RS_HIGH;
		} else if (RS == 5){
			_RS_HIGH = 1 << (RS - 2);
			_RS_LOW = ~_RS_HIGH;
		} else if ((RS > 1)&&(RS < 4)){
			_RS_HIGH = 1 << (RS + 2);
			_RS_LOW = ~_RS_HIGH;
		} else if (RS < 2){
			_RS_HIGH = 1 << RS;
			_RS_LOW = ~_RS_HIGH;
		} else {
			_fast = 0; //Not a correct register, so use digitalWrite
		}
		if ((CS > 9)&&(CS < 14)){
			_CS_HIGH = 1 << (CS - 6);
			_CS_LOW = ~_CS_HIGH;
		} else if ((CS > 5)&&(CS < 10)){
			_CS_HIGH = 1 << (CS - 3);
			_CS_LOW = ~_CS_HIGH;
		} else if (CS == 4){
			_CS_HIGH = 1 << (CS + 1);
			_CS_LOW = ~_CS_HIGH;
		} else if (CS == 5){
			_CS_HIGH = 1 << (CS - 2);
			_CS_LOW = ~_CS_HIGH;
		} else if ((CS > 1)&&(CS < 4)){
			_CS_HIGH = 1 << (CS + 2);
			_CS_LOW = ~_CS_HIGH;
		} else if (CS < 2){
			_CS_HIGH = 1 << CS;
			_CS_LOW = ~_CS_HIGH;
		} else {
			_fast = 0; //Not a correct register, so use digitalWrite
		}
		if ((SCLK > 9)&&(SCLK < 14)){
			_SCLK_HIGH = 1 << (SCLK - 6);
			_SCLK_LOW = ~_SCLK_HIGH;
		} else if ((SCLK > 5)&&(SCLK < 10)){
			_SCLK_HIGH = 1 << (SCLK - 3);
			_SCLK_LOW = ~_SCLK_HIGH;
		} else if (SCLK == 4){
			_SCLK_HIGH = 1 << (SCLK + 1);
			_SCLK_LOW = ~_SCLK_HIGH;
		} else if (SCLK == 5){
			_SCLK_HIGH = 1 << (SCLK - 2);
			_SCLK_LOW = ~_SCLK_HIGH;
		} else if ((SCLK > 1)&&(SCLK < 4)){
			_SCLK_HIGH = 1 << (SCLK + 2);
			_SCLK_LOW = ~_SCLK_HIGH;
		} else if (SCLK < 2){
			_SCLK_HIGH = 1 << SCLK;
			_SCLK_LOW = ~_SCLK_HIGH;
		} else {
			_fast = 0; //Not a correct register, so use digitalWrite
		}
		if ((SDATA > 9)&&(SDATA < 14)){
			_SDATA_HIGH = 1 << (SDATA - 6);
			_SDATA_LOW = ~_SDATA_HIGH;
		} else if ((SDATA > 5)&&(SDATA < 10)){
			_SDATA_HIGH = 1 << (SDATA - 3);
			_SDATA_LOW = ~_SDATA_HIGH;
		} else if (SDATA == 4){
			_SDATA_HIGH = 1 << (SDATA + 1);
			_SDATA_LOW = ~_SDATA_HIGH;
		} else if (SDATA == 5){
			_SDATA_HIGH = 1 << (SDATA - 2);
			_SDATA_LOW = ~_SDATA_HIGH;
		} else if ((SDATA > 1)&&(SDATA < 4)){
			_SDATA_HIGH = 1 << (SDATA + 2);
			_SDATA_LOW = ~_SDATA_HIGH;
		} else if (SDATA < 2){
			_SDATA_HIGH = 1 << SDATA;
			_SDATA_LOW = ~_SDATA_HIGH;
		} else {
			_fast = 0; //Not a correct register, so use digitalWrite
		}
	}
  #else
	if (speed){//Calculate pin registers.
		if ((RS > 7)&&(RS < 14)){
			_RS_HIGH = 1 << (RS - 8);
			_RS_LOW = ~_RS_HIGH;
		} else if (RS < 8){
			_RS_HIGH = 1 << RS;
			_RS_LOW = ~_RS_HIGH;
		} else {
			_fast = 0; //Not a correct register, so use digitalWrite
		}
		if ((CS > 7)&&(CS < 14)){
			_CS_HIGH = 1 << (CS - 8);
			_CS_LOW = ~_CS_HIGH;
		} else if (CS < 8){
			_CS_HIGH = 1 << CS;
			_CS_LOW = ~_CS_HIGH;
		} else {
			_fast = 0; //Not a correct register, so use digitalWrite
		}
		if ((SCLK > 7)&&(SCLK < 14)){
			_SCLK_HIGH = 1 << (SCLK - 8);
			_SCLK_LOW = ~_SCLK_HIGH;
		} else if (SCLK < 8){
			_SCLK_HIGH = 1 << SCLK;
			_SCLK_LOW = ~_SCLK_HIGH;
		} else {
			_fast = 0; //Not a correct register, so use digitalWrite
		}
		if ((SDATA > 7)&&(SDATA < 14)){
			_SDATA_HIGH = 1 << (SDATA - 8);
			_SDATA_LOW = ~_SDATA_HIGH;
		} else if (SDATA < 8){
			_SDATA_HIGH = 1 << SDATA;
			_SDATA_LOW = ~_SDATA_HIGH;
		} else {
			_fast = 0; //Not a correct register, so use digitalWrite
		}
	}
 #endif
	
	_parameter = 1;
	_command = 0;
	
	_contrast = 126; //In otherwords, use default unless told otherwise
	
	//_LCDwidth = 132;
	//_LCDheight = 132;
}

void gLCD::SetForeColour(char Red, char Green, char Blue){
	_ForeRed = Red & 0x0F;
	_ForeGreen = Green & 0x0F;
	_ForeBlue = Blue & 0x0F;
}

void gLCD::SetBackColour(char Red, char Green, char Blue){
	_BackRed = Red & 0x0F;
	_BackGreen = Green & 0x0F;
	_BackBlue = Blue & 0x0F;
}

void gLCD::twoPixels(byte SendR1, byte SendG1, byte SendB1, byte SendR2, byte SendG2, byte SendB2){
	byte SendR1G1 = (SendR1 << 4) | (SendG1);
	byte SendB1R2 = (SendB1 << 4) | (SendR2);
	byte SendG2B2 = (SendG2 << 4) | (SendB2);
	
	twoPixels(SendR1G1, SendB1R2, SendG2B2);
}

void gLCD::twoPixels(byte SendR1G1, byte SendB1R2, byte SendG2B2){
	//Add both pixels to the window
	SendByte(_parameter, SendR1G1);
	SendByte(_parameter, SendB1R2);
	SendByte(_parameter, SendG2B2);
}

void gLCD::twoPixels(char Colour){
	//Get type for each pixel
	int pixelOne = Colour & 1;
	int pixelTwo = (Colour >> 1) & 1;
	
	//Pixel data is in the format:   RRRRGGGG BBBBRRRR GGGGBBBB, where this is  two pixels worth of data
	
	//Is pixel one foreground or background
	if (pixelOne){
		_SendRG = _ForeRed << 4;
		_SendRG |= _ForeGreen;
		_SendBR = _ForeBlue << 4;
	} else {
		_SendRG = _BackRed << 4;
		_SendRG |= _BackGreen;
		_SendBR = _BackBlue << 4;
	}
	//Is pixel two foreground or background
	if (pixelTwo){
		_SendBR |= _ForeRed;
		_SendGB = _ForeGreen << 4;
		_SendGB |= _ForeBlue;
	} else {
		_SendBR |= _BackRed;
		_SendGB = _BackGreen << 4;
		_SendGB |= _BackBlue;
	}
	//Add both pixels to the window
	SendByte(_parameter, _SendRG);
	SendByte(_parameter, _SendBR);
	SendByte(_parameter, _SendGB);
}

void gLCD::Window(unsigned char X1, unsigned char Y1, unsigned char X2, unsigned char Y2){
	X1 = X1 + _Xzero; //Apply offset to window
	Y1 = Y1 + _Yzero;
	X2 = X2 + _Xzero;
	Y2 = Y2 + _Yzero;
	
	if (_Phillips){
		SendByte(_command, 0x2A);        //Column adress
		SendByte(_parameter, Y1);        //y-Position upper left corner
		SendByte(_parameter, Y2);        //y-Position of lower right corner
		SendByte(_command, 0x2B);        //Page adressing
		SendByte(_parameter, X1);        //X-Position upper left corner
		SendByte(_parameter, X2);        //x-Position of lower right corner
		SendByte(_command, 0x2C);        //RAMWR - Ram Write
	
	} else {
		SendByte(_command, 0x15);        //Column adress
		SendByte(_parameter, X1);        //X-Position upper left corner
		SendByte(_parameter, X2);        //x-Position of lower right corner
		SendByte(_command, 0x75);        //Page adressing
		SendByte(_parameter, Y1);        //y-Position upper left corner
		SendByte(_parameter, Y2);        //y-Position of lower right corner
		SendByte(_command, 0x5C);        //RAMWR - Ram Write
	}
}

void gLCD::writeRS(boolean bitValue){
	if (bitValue){
		RSPORT |= _RS_HIGH;
	} else {
		RSPORT &= _RS_LOW;
	}
}

void gLCD::writeCS(boolean bitValue){
	if (bitValue){
		CSPORT |= _CS_HIGH;
	} else {
		CSPORT &= _CS_LOW;
	}
}

void gLCD::writeSCLK(boolean bitValue){
	if (bitValue){
		SCLKPORT |= _SCLK_HIGH;
	} else {
		SCLKPORT &= _SCLK_LOW;
	}
}

void gLCD::writeSDATA(boolean bitValue){
	if (bitValue){
		SDATAPORT |= _SDATA_HIGH;
	} else {
		SDATAPORT &= _SDATA_LOW;
	}
}

void gLCD::SendByte(boolean Command, unsigned char data){

		char i;
		if (_fast){
			writeRS(1);					//Startup LCD Communication
			writeCS(0);					//start of sequence
			
			//Send Command or parameter
			writeSCLK(0);					//Clock 0
			writeSDATA(Command);		//Send a bit
			writeSCLK(1);					//Clock 1
			
			//Send data
			for (i = 7;i >= 0; i--){
				writeSCLK(0);				//Clock 0
				writeSDATA((data >> i) & 1);//isolate and send a data bit
				writeSCLK(1);				//Clock 1
			}
			writeCS(1);
		} else {
			char databit;
			digitalWrite(_RS, 1);					//Startup LCD Communication
			digitalWrite(_CS, 0);					//start of sequence
			
			//Send Command or parameter
			digitalWrite(_SCLK, 0);					//Clock 0
			digitalWrite(_SDATA, Command);			//Send a bit
			digitalWrite(_SCLK, 1);					//Clock 1
			
			//Send data
			for (i = 7;i >= 0; i--){
				digitalWrite(_SCLK, 0);				//Clock 0
				databit = (data >> i) & 1; 			//isolate the data bit
				digitalWrite(_SDATA, databit);		//Send a bit
				digitalWrite(_SCLK, 1);				//Clock 1
			}
			
			digitalWrite(_CS, 1);					//end of sequence
		}
}

void gLCD::Contrast(signed char contrast){
	_contrast = contrast; 
	if (_Phillips){
		if (_contrast > 63){
			_contrast = 63;
		}
		if (_contrast < -63){
			_contrast = -63;
		}
		SendByte(_command, 0x25);            //Contrast Control
		SendByte(_parameter, _contrast);	 //User defined contrast.
	} else {
		if (_contrast > 63){
			_contrast = 63;
		}
		if (_contrast < 0){
			_contrast = 0;
		}
		SendByte(_command, 0x81);            //Contrast Control
		SendByte(_parameter, _contrast); 	//User defined contrast.
		SendByte(_parameter, 0x02);			 //Resistor Ratio - 0x02 should be fine for most screens
	}
}

void gLCD::Configure(boolean normal){
	if (_Phillips){
		SendByte(_command, 0x36);           		 //Configure Display
		if(normal){
			SendByte(_parameter, _normalScan);		 //RGB order, mirror display x or y. 
		} else {
			SendByte(_parameter, _inverseScan);
		}
	} else {
		SendByte(_command, 0xBC);           		 //Display Control
		if (normal){
			SendByte(_parameter, _normalScan);       //Scan direction
		} else {
			SendByte(_parameter, _inverseScan);
		}
		SendByte(_parameter, 0x00);      		     //RGB colour order
		SendByte(_parameter, 0x02);       		     //colour mode - 4096 colours
	}
}

void gLCD::Init(char Xzero, char Yzero, boolean InvertColour){
		
		_Yzero = Yzero;
		_Xzero = Xzero;
		
		_Phillips = 0;
		
		digitalWrite(_RS,0);				 //Reset LCD

		delay(10);  

		digitalWrite(_CS,1); 				 //Select LCD
		digitalWrite(_SDATA,1);    		 	 //Set Data Pin High
		digitalWrite(_SCLK,1);      		 //Set Clock Pin High
		digitalWrite(_RS,1);        		 //Startup LCD

		delay(10);     						 //Wait after Reset
		
		SendByte(_command, 0xCA);            //Configure Display
		SendByte(_parameter, 0x00);          //2 divisions, switching period=8 (default)
		SendByte(_parameter, 0x20);          //nlines/4 - 1 = 132/4 - 1 = 32)
		SendByte(_parameter, 0x00);          //no inversely highlighted lines

		SendByte(_command, 0xBB);            //Common Output Scan (avoid split display)...
		SendByte(_parameter, 0x01);          //...Scan 1->69, 69->132

		SendByte(_command, 0xD1);            //Enable Oscillators

		SendByte(_command, 0x94);            //Sleep Out

		SendByte(_command, 0x20);            //Voltage Regulators On
		SendByte(_parameter, 0x0F);          //Ref voltage, then circuit voltage, then booster
		
		if (InvertColour){
			SendByte(_command, 0xA7);        //Invert Display Colour
		}

		SendByte(_command, 0xBC);            //Display Control
		_normalScan = 0x04; 
		_inverseScan = 0x01;
		SendByte(_parameter, _normalScan);          //Scan direction (left-->right or right-->left)
		SendByte(_parameter, 0x00);          //RGB colour order
		SendByte(_parameter, 0x02);          //colour mode - 4096 colours

		SendByte(_command, 0x81);            //Contrast Control
		SendByte(_parameter, 0x2B);     	 //0 to 63: sets contrast - 0x2B is default. 
		SendByte(_parameter, 0x02);			 //Resistor Ratio - 0x02 should be fine for most screens

		delay(100);                          //Allow Power to stablise

		SendByte(_command, 0xAF);            //Display On
		delay(40);

		SetForeColour(0x0F,0x0F,0x0F);		 //Display is White foreground and Blue background
		SetBackColour(0x00,0x00,0x0F);	

		Clear();
}

void gLCD::Init(char Xzero, char Yzero, boolean InvertColour, boolean Phillips, byte xReverse){
	
		_Yzero = Yzero;
		_Xzero = Xzero;
		
		_Phillips = 1;
		
		digitalWrite(_RS,0);				 //Reset LCD

		delay(30);  

		digitalWrite(_CS,1); 				 //Select LCD
		digitalWrite(_SDATA,1);    		 	 //Set Data Pin High
		digitalWrite(_SCLK,1);      		 //Set Clock Pin High
		digitalWrite(_RS,1);        		 //Startup LCD

		delay(30);     						 //Wait after Reset
		
		SendByte(_command, 0x11);			 //Wake up from sleep mode
		
		if (InvertColour){
			SendByte(_command, 0x20);        //Invert Display Colour
		}
		
		SendByte(_command, 0x3A);            //Colour Control
		SendByte(_parameter, 0x03);          //colour mode - 4096 colours
		
		SendByte(_command, 0x36);            //Configure Display
		if (xReverse & 1){ //When xReverse is one, then the value of this parameter is ajusted so that x is mirrored from normal.
			_normalScan = 0x60 - ((xReverse & 2)<<4);
			_inverseScan = 0xC0 + ((xReverse & 2)<<4);
			SendByte(_parameter, _normalScan);      //RGB order, mirror display x or y. 0x60 = RGB, no mirroring
													//									0x68 = BGR, no mirroring
													//									0xA0 = RGB, mirror X and Y
													//									0xA8 = BGR, mirror X and Y
		} else {
			_normalScan = 0x20 - ((xReverse & 2)<<4);
			_inverseScan = 0x80 + ((xReverse & 2)<<4);
			SendByte(_parameter, _normalScan);      //RGB order, mirror display x or y. 0x20 = RGB, no mirroring
													//									0x28 = BGR, no mirroring
													//									0xE0 = RGB, mirror X and Y
													//									0xE8 = BGR, mirror X and Y
		}
		SendByte(_command, 0x25);            //Contrast Control
		SendByte(_parameter, 0x30);      //-63 to 63: sets contrast - 0x30 is default. 
		
		delay(2);

		SendByte(_command, 0x29);            //Display On
		
		delay(40);

		SetForeColour(0x0F,0x0F,0x0F);		 //Display is White foreground and Blue background
		SetBackColour(0x00,0x00,0x0F);	

		Clear();
}

void gLCD::displayOff(){
	if(_Phillips){
		//DISPOFF
		SendByte(_command, 0x28);
	} else {
		//DISOFF
		SendByte(_command, 0xAE);
	}
}

void gLCD::displayOn(){
	if(_Phillips){
		//DISPON
		SendByte(_command, 0x29);
	} else {
		//DISON
		SendByte(_command, 0xAF);
	}
}

void gLCD::Clear(){
		int i,j;

		Window(0,0,131,131);			//Create a window the size of the screen
		
		for (i = 0;i < 132;i++){
			for (j = 0;j < 67;j++){
				twoPixels(0);			//Send pairs of pixels in background colour
			}
		}
}

void gLCD::Print(String text, unsigned char X1, unsigned char Y1, byte Font){
	    
		int i,j,k, xcnt, ycnt;
		
		
	    char width = (Font & 1) + 1; //Double width (BOLD)
	    char height = ((Font >> 1) & 1) + 1; //Double height (Large text when used with fontwidth)
		boolean background = ((Font >> 2) & 1); //Whether the text has a background

		int X = X1;
		int startX = X1;
		int Y = Y1;
		int startY = Y1;
		
		int length = text.length(); //Length of the string to be printed

		char char2print;
		byte data;
		unsigned char databit;
		
	    for (i=0;i<length;i++){         //Start at beginning of string and work along
			
			 //Finds the character to print, and adjusts it to a position in the ASCII array
			char2print = text.charAt(i);
			if (char2print == 13){
				//If it is a carriage return, move to the next line.
				X1 = startX;
				X = X1;
				startY += (8*height);
				Y1 = startY;
				Y = Y1;
				continue; //Move on to next character in string
			} else if ((char2print < 23)&&(char2print > -121)){ //The > -121 allows for the 9 custom characters to be used
				//If it is not a printable character, print a space instead.
				char2print = 0;
			} else {
				char2print -= 32;
			}
			
			if(background){
				//Print the character
				Window(X1,Y1,X1+(6*width)-1,Y1+(8*height)-1);			//Create a window the size of one character, then fill it with the background colour
				for (xcnt = 0;xcnt < 5;xcnt++){
					for (j = 0;j < width;j++){
						if (height == 2){
							//If double height, each pair of pixels will be the same, and there will be 8 pairs of them.
							for (ycnt = 0;ycnt < 8;ycnt++){
								data = pgm_read_byte(&(charData[char2print][xcnt]));
								databit = (data >> ycnt) & 1;
								databit |= databit << 1;
								twoPixels(databit);
							}
						} else {
							//If not height, each pair of pixels will be two distinct pixels, so we need to set the colour for each correctly.
							for (ycnt = 0;ycnt < 7;ycnt += 2){
								data = pgm_read_byte(&(charData[char2print][xcnt]));
								databit = (data >> ycnt) & 3;
								twoPixels(databit);
							}
						}
					}
				}
				//Fill in the character seperator pixels
				for (j = 0;j < (4*height)*width;j++){
					twoPixels(0);
				}
			} else {
				//Print the character
				for (xcnt = 0;xcnt < 5;xcnt++){
					//Do this once or twice depending on width format
					for (j = 0;j < width;j++){
						for (ycnt = 0;ycnt <8;ycnt++){
							data = pgm_read_byte(&(charData[char2print][xcnt]));
							databit = (data >> ycnt) & 1; 			//isolate the data bit
							
							//Do this once or twice depending on height format
							for (k = 0;k < height;k++){
								if(databit){
									Plot(X,Y,3);
								}
								Y++;//increase Y offset
							}
						}
						X++; //increase X offset
						Y = Y1; //Y back to zero offset
					}
				}
			}
			X1 += (6*width); // Move X position so that next character knows where to be placed
			X = X1; //X back to zero offset
	    }
}

void gLCD::Plot(unsigned char X, unsigned char Y, char Colour){
		Window(X,Y,X,Y);                          //Creates a window of 1 pixel
		
		Colour |= Colour << 1;
		
		twoPixels(Colour);
}

void gLCD::Circle(unsigned char X1, unsigned char Y1, unsigned char Radius, unsigned char format){
		/*
		Implimentation of Bresenham's Circle Algorithm
		*/
		
		char fillColour = format & 1;
		char nofill = (format >> 1) & 1;
		char borderColour = (format >> 2) & 1;
		
		fillColour |= fillColour << 1;
		borderColour |= borderColour << 1;
		
		unsigned char X = Radius;
		unsigned char Y = 0;
		signed int error = 0;
		signed int dx = 1 - (Radius << 1);
		signed int dy = 1;
		
		//Have to do it twice if it is filled in unfortunately
		
		if (!nofill){
			while (X >= Y){
				CircleFill(X,Y,X1,Y1,fillColour);
				Y++;
				error += dy;
				dy += 2;
				if ((dx + (error<<1)) > 0){
					X--;
					error += dx;
					dx += 2;
				}
			}
		}
		
		X = Radius;
		Y = 0;
		error = 0;
		dx = 1 - (Radius << 1);
		dy = 1;
		
		while (X >= Y){
			CirclePlot(X,Y,X1,Y1,borderColour);
			Y++;
			error += dy;
			dy += 2;
			if ((dx + (error<<1)) > 0){
				X--;
				error += dx;
				dx += 2;
			}
		}
		
}

void gLCD::CircleFill(unsigned char X, unsigned char Y, unsigned char X1, unsigned char Y1, char Colour){
		int i;
		Window(X1-X,Y1+Y,X1+X,Y1+Y); 
		for(i = 0; i < X; i++){
			twoPixels(Colour);
		}
		Window(X1-X,Y1-Y,X1+X,Y1-Y);
		for(i = 0; i < X; i++){
			twoPixels(Colour);
		}
		Window(X1-Y,Y1+X,X1+Y,Y1+X);
		for(i = 0; i < Y; i++){
			twoPixels(Colour);
		}
		Window(X1-Y,Y1-X,X1+Y,Y1-X);
		for(i = 0; i < Y; i++){
			twoPixels(Colour);
		}
}

void gLCD::CirclePlot(unsigned char X, unsigned char Y, unsigned char X1, unsigned char Y1, char Colour){
		//Circle is Symmetrical, so we can plot the whole thing having only calculated an octant
		Plot(X1+X,Y1+Y,Colour); //Octant 1
		Plot(X1-X,Y1+Y,Colour); //Octant 4
		Plot(X1+X,Y1-Y,Colour); //Octant 8
		Plot(X1-X,Y1-Y,Colour); //Octant 5
		Plot(X1+Y,Y1+X,Colour); //Octant 2
		Plot(X1-Y,Y1+X,Colour); //Octant 3
		Plot(X1+Y,Y1-X,Colour); //Octant 7
		Plot(X1-Y,Y1-X,Colour); //Octant 6
}

void gLCD::Line(unsigned char X1, unsigned char Y1, unsigned char X2, unsigned char Y2, char Colour){

		signed char xdir = 1;		 //Amount by which X changes
		signed char ydir = 1;		 //Amount by which Y changes
		signed int error;
		unsigned char i;
		
		Colour |= Colour << 1;
		
		/*
		Implimentation of Bresenham's Line Algorithm
		*/
		
		//The algorithm works for only one octant. By reversing the direction, the algorithm can work for 4 of the octants
		
		signed int dx = X2 - X1; 	 //Change in X
		signed int dy = Y2 - Y1; 	 //Change in Y
		
		if (dx < 0){
			xdir = -1;
			dx = 0 - dx;
		}
		if (dy < 0){
			ydir = -1;
			dy = 0 - dy;
		}
		
		signed int dy2 = dy << 1;	 //Change in Y with twice the precision
		signed int dx2 = dx << 1;	 //Change in X with twice the precision
		
		
		//By choosing the major axis, one that experiances greatest change, the algorithm will work for all octants
		if (dx > dy){
			//The X axis see's the largest change, so with each new pixel, X always changes by 1
			error = dy2 - dx;
			for (i = 0; i <= dx; i++){
				Plot(X1,Y1,Colour); //Print the pixel
				X1 += xdir;	//move to next x value
				if (error > 0){ 
					//Error is above the midpoint. So, we move up one
					error += (dy2 - dx2);
					Y1 += ydir;
				} else {
					//Error is below midpoint, so we keep the same y value
					error += dy2;
				}			
			}
		} else {
			//The Y axis see's the largest change, so with each new pixel, Y always changes by 1
			error = dx2 - dy;
			for (i = 0; i <= dy; i++){
				Plot(X1,Y1,Colour); //Print the pixel
				Y1 += ydir;	//move to next y value
				if (error > 0){ 
					//Error is above the midpoint. So, we move right one
					error += (dx2 - dy2);
					X1 += xdir;
				} else {
					//Error is below midpoint, so we keep the same x value
					error += dx2;
				}
			}
		}
}

void gLCD::Box(unsigned char X1, unsigned char Y1, unsigned char X2, unsigned char Y2, unsigned char format){
		
		char fillColour = format & 1;
		char noFill = (format >> 1) & 1;
		char borderColour = (format >> 2) & 1;
		
		unsigned char dx = (X2 - X1) >> 1;
		unsigned char dy = (Y2 - Y1) >> 1;
		
		fillColour |= fillColour << 1;
		borderColour |= borderColour << 1;
		
		if(!noFill){
			Window(X1,Y1,X2,Y2);		//Create a window for the box
			for (char Y = Y1;Y <= Y2;Y++){
				for (char X = X1;X <= X2;X++){
					twoPixels(fillColour);
				}
			}
		}
		
		//draw border
		Window(X1, Y1, X2, Y1); 
		for(int i = 0; i <= dx; i++){
			twoPixels(borderColour);
		}
		Window(X2, Y1, X2, Y2);
		for(int i = 0; i <= dy; i++){
			twoPixels(borderColour);
		}
		Window(X1, Y2, X2, Y2);
		for(int i = 0; i <= dx; i++){
			twoPixels(borderColour);
		}
		Window(X1, Y1, X1, Y2);
		for(int i = 0; i <= dy; i++){
			twoPixels(borderColour);
		}
}

void gLCD::RedGreen(unsigned char X1, unsigned char Y1, unsigned char X2, unsigned char Y2){
	int dy = (Y2 - Y1) >> 4; //Y2 - Y1 should be a multiple of eight when invoking this, otherwise it wont work
	int dx = (X2 - X1) >> 5; //X2 - X1 should be a multiple of sixteen when invoking this, otherwise it wont work
	
	Window(X1,Y1,X2-1,Y2-1);
	for (int i = 0;i < 16;i++){
		for (int k = 0;k < dy;k++){
			for (int j = 0;j < 16;j++){
				SetForeColour(i,j,0);
				for (int l = 0;l < dx;l++){
					twoPixels(3);
				}
			} 
		}
	}
}

void gLCD::GreenBlue(unsigned char X1, unsigned char Y1, unsigned char X2, unsigned char Y2){
	int dy = (Y2 - Y1) >> 4; //Y2 - Y1 should be a multiple of eight when invoking this, otherwise it wont work
	int dx = (X2 - X1) >> 5; //X2 - X1 should be a multiple of sixteen when invoking this, otherwise it wont work
	
	Window(X1,Y1,X2-1,Y2-1);
	for (int i = 0;i < 16;i++){
		for (int k = 0;k < dy;k++){
			for (int j = 0;j < 16;j++){
				SetForeColour(0,i,j);
				for (int l = 0;l < dx;l++){
					twoPixels(3);
				}
			} 
		}
	}
}

void gLCD::BlueRed(unsigned char X1, unsigned char Y1, unsigned char X2, unsigned char Y2){
	int dy = (Y2 - Y1) >> 4; //Y2 - Y1 should be a multiple of eight when invoking this, otherwise it wont work
	int dx = (X2 - X1) >> 5; //X2 - X1 should be a multiple of sixteen when invoking this, otherwise it wont work
	
	Window(X1,Y1,X2-1,Y2-1);
	for (int i = 0;i < 16;i++){
		for (int k = 0;k < dy;k++){
			for (int j = 0;j < 16;j++){
				SetForeColour(j,0,i);
				for (int l = 0;l < dx;l++){
					twoPixels(3);
				}
			} 
		}
	}
}

void gLCD::ColourBars(unsigned char X1, unsigned char Y1, unsigned char X2, unsigned char Y2){

	int dy = Y2 - Y1;
	int dx = (X2 - X1) >> 4;
	int Y = Y1;
	int X = X1;
	
	char colour[6][3] = {
		{15,0,0},
		{15,15,0},
		{0,15,0},
		{0,15,15},
		{0,0,15},
		{15,0,15}
	};
	
	Window(X1,Y1,X2-1,Y2-1);
	for (int i = 0;i < 6;i++){
		SetForeColour(colour[i][0],colour[i][1],colour[i][2]);
		for (int k = 0;k < dx;k++){
			for (int j = 0;j < dy;j++){
				twoPixels(3);
			} 
		}
	}
	dx = dx << 2;
	dy = dy >> 5;
	
	for (int k = 0;k < dx;k++){
		for (int j = 0;j < 16;j++){
			SetForeColour(j,j,j);
			for (int l = 0;l < dy;l++){
				twoPixels(3);
			} 
		}
	}
}

void gLCD::testPattern(){
	SetBackColour(15,15,15);
	Clear();
	RedGreen(1,1,65,65);
	GreenBlue(1,65,65,129);
	BlueRed(65,1,129,65);
	ColourBars(65,65,129,129);
}