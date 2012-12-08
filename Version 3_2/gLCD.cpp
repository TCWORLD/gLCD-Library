/*
	Sparkfun Nokia knockoff screen 128x128 controller. Should work with (all) screens.
	
	Code written by Thomas Carpenter (2011)
	
	==================================================================================================
	Current Library Version: 3.2
	
	See header file for function descriptions and ChangeLog
	
*/
#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif
#include "gLCD.h"
#ifndef _LIB_SAM_
#define PGMSPACE PROGMEM
#include <avr/pgmspace.h>
#else
#define PGMSPACE const
#endif
//Character Database store

//This is how many custom characters you have added to the end of the map. There are no more than 128 allowed.
#define numberOfCustomCharacters 9
PGMSPACE byte charData[96 + numberOfCustomCharacters][5] = {
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
	//Add more lines at the end to generate custom characters.
	
	{0x02 , 0x6F , 0x1A , 0x30 , 0x6E }, // 127 = Shuffle
	{0x3C , 0x62 , 0x47 , 0x62 , 0x38 }, // -128 = Repeat
	{0x3E , 0x3E , 0x3E , 0x3E , 0x3E }, // -127 = Stop
	{0x00 , 0x7F , 0x3E , 0x1C , 0x08 }, // -126 = Play
	{0x3E , 0x3E , 0x00 , 0x3E , 0x3E }, // -125 = Pause
	{0x7F , 0x3E , 0x1C , 0x08 , 0x7F }, // -124 = Skip
	{0x1C , 0x3E , 0x7F , 0x00 , 0x1C }, // -123 = Volume
	{0x1C , 0x3E , 0x7F , 0x00 , 0x00 }, // -122 = Mute
	{0x3C , 0x60 , 0x4F , 0x60 , 0x3C },  // -121 = Power
};

gLCD::gLCD(byte RS, byte CS, byte SCLK, byte SDATA, SpeedMode speed){
	_fast = speed;

	pinMode(RS, OUTPUT);
	_RS = RS;
	pinMode(CS, OUTPUT);
	_CS = CS;
	pinMode(SCLK, OUTPUT);
	_SCLK = SCLK;
	pinMode(SDATA, OUTPUT);
	_SDATA = SDATA;

#ifndef _LIB_SAM_
	if(speed){
		byte RSport = digitalPinToPort(RS);
		byte CSport = digitalPinToPort(CS);
		byte SCLKport = digitalPinToPort(SCLK);
		byte SDATAport = digitalPinToPort(SDATA);
		
		if ((   RSport == NOT_A_PIN) ||
			(   CSport == NOT_A_PIN) ||
			( SCLKport == NOT_A_PIN) ||
			(SDATAport == NOT_A_PIN) )
		{
			_fast = 0; //Not a correct register, so use digitalWrite
		} else {
			_RS_PORT = portOutputRegister(RSport);
			_CS_PORT = portOutputRegister(CSport);
			_SCLK_PORT = portOutputRegister(SCLKport);
			_SDATA_PORT = portOutputRegister(SDATAport);
			_RS_HIGH = digitalPinToBitMask(RS);
			_RS_LOW = ~_RS_HIGH;
			_CS_HIGH = digitalPinToBitMask(CS);
			_CS_LOW = ~_CS_HIGH;
			_SCLK_HIGH = digitalPinToBitMask(SCLK);
			_SCLK_LOW = ~_SCLK_HIGH;
			_SDATA_HIGH = digitalPinToBitMask(SDATA);
			_SDATA_LOW = ~_SDATA_HIGH;
		}
	}
#endif

	_contrast = 126; //In otherwords, use default unless told otherwise
	
	//_LCDwidth = 132;
	//_LCDheight = 132;
}

void gLCD::setForeColour(char Red, char Green, char Blue){
	_ForeRed = Red & 0x0F;
	_ForeGreen = Green & 0x0F;
	_ForeBlue = Blue & 0x0F;
}

void gLCD::setBackColour(char Red, char Green, char Blue){
	_BackRed = Red & 0x0F;
	_BackGreen = Green & 0x0F;
	_BackBlue = Blue & 0x0F;
}

void gLCD::setForeColour(unsigned long colour){
	_ForeRed = (colour >> 16) & 0x0F;
	_ForeGreen = (colour >> 8) & 0x0F;
	_ForeBlue = colour & 0x0F;
}

void gLCD::setBackColour(unsigned long colour){
	_BackRed = (colour >> 16) & 0x0F;
	_BackGreen = (colour >> 8) & 0x0F;
	_BackBlue = colour & 0x0F;
}

//This one is inefficient and not used internally, but it is useful in certain situations
void gLCD::twoPixels(byte SendR1, byte SendG1, byte SendB1, byte SendR2, byte SendG2, byte SendB2){
	byte SendR1G1,SendB1R2,SendG2B2,SendFourth;
	if(_driver & 0x01){
		SendR1G1 = SendR1;
		SendB1R2 = (SendG1 << 4) | (SendB1 & 0x0F);
		SendG2B2 = SendR2;
		SendFourth = (SendG2 << 4) | (SendB2 & 0x0F);
		twoPixels(SendR1G1, SendB1R2, SendG2B2, SendFourth);
	} else {
		//Note that SendFourth is unused for these, so to save time we don't bother giving it a value.
		SendR1G1 = (SendR1 << 4) | (SendG1 & 0x0F);
		SendB1R2 = (SendB1 << 4) | (SendR2 & 0x0F);
		SendG2B2 = (SendG2 << 4) | (SendB2 & 0x0F);
		twoPixels(SendR1G1, SendB1R2, SendG2B2);
	}
}

//This one is not used internally, but it is useful in certain situations
void gLCD::twoPixels(byte SendR1G1, byte SendB1R2, byte SendG2B2){
	//Add both pixels to the window
	SendByte(_parameter, SendR1G1);
	SendByte(_parameter, SendB1R2);
	SendByte(_parameter, SendG2B2);
}

void gLCD::twoPixels(byte SendR1G1, byte SendB1R2, byte SendG2B2, byte SendFourth){
	//Add both pixels to the window
	SendByte(_parameter, SendR1G1);
	SendByte(_parameter, SendB1R2);
	SendByte(_parameter, SendG2B2);
	SendByte(_parameter, SendFourth);
}


void gLCD::setSendColour16bit(char Colour){
	//Get type for each pixel
	int pixelOne = Colour & 1;
	int pixelTwo = (Colour >> 1) & 1;
	
	//For 16bit:
	//Pixel data is in the format:   RRRRRGGG GGGBBBBB RRRRRGGG GGGBBBBB, where this is  two pixels worth of data
	
	//Is pixel one foreground or background
	if (pixelOne){
		_SendRG = _ForeRed;
		_SendBR = (_ForeGreen << 4) | (_ForeBlue);
	} else {
		_SendRG = _BackRed;
		_SendBR = (_BackGreen << 4) | (_BackBlue);
	}
	//Is pixel two foreground or background
	if (pixelTwo){
		_SendGB = _ForeRed;
		_SendFourth = (_ForeGreen << 4) | (_ForeBlue);
	} else {
		_SendGB = _BackRed;
		_SendFourth = (_BackGreen << 4) | (_BackBlue);
	}
}
	
void gLCD::setSendColour12bit(char Colour){
	//Get type for each pixel
	int pixelOne = Colour & 1;
	int pixelTwo = (Colour >> 1) & 1;
	
	//For 12 bit:
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
}

void gLCD::twoPixels(char Colour){
    (*this.*setSendColour)(Colour);
	//Add both pixels to the window
	(*this.*sendTwoPixels)();
}

void gLCD::two16bitPixels(){
	//Add both pixels to the window (use the old colour data)
	SendByte(_parameter, _SendRG);
	SendByte(_parameter, _SendBR);
	SendByte(_parameter, _SendGB);
	SendByte(_parameter, _SendFourth);
}
	
void gLCD::two12bitPixels(){
	SendByte(_parameter, _SendRG);
	SendByte(_parameter, _SendBR);
	SendByte(_parameter, _SendGB);
}

void gLCD::Window(){
	Window(X1,X2,Y1,Y2); //Use the global coordinates to call the window
}

void gLCD::Window(unsigned char _X1, unsigned char _Y1, unsigned char _X2, unsigned char _Y2){
	_X1 = _X1 + _Xzero; //Apply offset to window
	_Y1 = _Y1 + _Yzero;
	_X2 = _X2 + _Xzero;
	_Y2 = _Y2 + _Yzero;
	
	if (_Phillips){
		SendByte(_command, 0x2A);        //Column adress
		SendByte(_parameter, _Y1);        //y-Position upper left corner
		SendByte(_parameter, _Y2);        //y-Position of lower right corner
		SendByte(_command, 0x2B);        //Page adressing
		SendByte(_parameter, _X1);        //X-Position upper left corner
		SendByte(_parameter, _X2);        //x-Position of lower right corner
		SendByte(_command, 0x2C);        //RAMWR - Ram Write
	
	} else {
		SendByte(_command, 0x15);        //Column adress
		SendByte(_parameter, _X1);        //X-Position upper left corner
		SendByte(_parameter, _X2);        //x-Position of lower right corner
		SendByte(_command, 0x75);        //Page adressing
		SendByte(_parameter, _Y1);        //y-Position upper left corner
		SendByte(_parameter, _Y2);        //y-Position of lower right corner
		SendByte(_command, 0x5C);        //RAMWR - Ram Write
	}
}


void gLCD::SendByte(DataType Command, unsigned char data){

		signed char i;
#ifndef _LIB_SAM_
		if (_fast){
			*_RS_PORT |= _RS_HIGH;;					//Startup LCD Communication
			*_CS_PORT &= _CS_LOW;					//start of sequence
			
			//Send Command or parameter
			*_SCLK_PORT &= _SCLK_LOW;	//Clock 0
			if(Command){//Send a bit
				*_SDATA_PORT |= _SDATA_HIGH;
			} else {
				*_SDATA_PORT &= _SDATA_LOW;
			}	
			*_SCLK_PORT |= _SCLK_HIGH;	//Clock 1
			
			//Send data	
			for (byte i = 0;i < 8; i++){
				*_SCLK_PORT &= _SCLK_LOW;  //Clock 0
				if(data & 0x80){          //isolate and send a data bit
					*_SDATA_PORT |= _SDATA_HIGH;
				} else {
					*_SDATA_PORT &= _SDATA_LOW;
				}
				data <<= 1;				//shift the data up
				*_SCLK_PORT |= _SCLK_HIGH;  //Clock 1
			}

			*_CS_PORT |= _CS_HIGH;
		} else 
#else
		if(1)
#endif
		{
			digitalWrite(_RS, 1);					//Startup LCD Communication
			digitalWrite(_CS, 0);					//start of sequence
			//Send Command or parameter
			digitalWrite(_SCLK, 0);					//Clock 0
			digitalWrite(_SDATA, Command);			//Send a bit
			digitalWrite(_SCLK, 1);					//Clock 1
			
			//Send data
			/*byte mask = 0x80;
			for (i = 7;i >= 0; i--){
				digitalWrite(_SCLK, 0);				//Clock 0
				digitalWrite(_SDATA, data & mask);		//Send a bit
				mask >>= 1;
				digitalWrite(_SCLK, 1);				//Clock 1
			}*/
			byte mask = 0x80;
			while(mask){
				digitalWrite(_SCLK, 0);				//Clock 0
				digitalWrite(_SDATA, data & mask);		//Send a bit
				mask >>= 1;
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
/*
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

		setForeColour(0x0F,0x0F,0x0F);		 //Display is White foreground and Blue background
		setBackColour(0x00,0x00,0x0F);	

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
		if (xReverse & 1){ //When xReverse is on, then the value of this parameter is ajusted so that x is mirrored from normal.
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
		SendByte(_parameter, 0x30);    		 //-63 to 63: sets contrast - 0x30 is default. 
		
		delay(2);

		SendByte(_command, 0x29);            //Display On
		
		delay(40);

		setForeColour(0x0F,0x0F,0x0F);		 //Display is White foreground and Blue background
		setBackColour(0x00,0x00,0x0F);	

		Clear();
}
*/

void gLCD::begin(signed char Xzero, signed char Yzero, boolean InvertColour, DriverType driver){
		_driver = driver;
		_Phillips = (_driver & 0x04) ? 0 : 1;
		if(_Phillips){
			sendTwoPixels = &gLCD::two12bitPixels;
			setSendColour = &gLCD::setSendColour12bit;
		} else {
			if(_driver & 0x01) {
				sendTwoPixels = &gLCD::two16bitPixels;
				setSendColour = &gLCD::setSendColour16bit;
			} else {
				sendTwoPixels = &gLCD::two12bitPixels;
				setSendColour = &gLCD::setSendColour12bit;
			}
		}
		_Yzero = Yzero;
		_Xzero = Xzero;
		
		digitalWrite(_RS,0);				 //Reset LCD

		delay(30);  
		
		digitalWrite(_CS,1); 				 //Select LCD
		digitalWrite(_SDATA,1);    		 	 //Set Data Pin High
		digitalWrite(_SCLK,1);      		 //Set Clock Pin High
		digitalWrite(_RS,1);        		 //Startup LCD

		delay(30);     						 //Wait after Reset
		
		if(_Phillips){
			SendByte(_command, 0x11);			 //Wake up from sleep mode
		} else {
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
		}
		if (InvertColour){
			SendByte(_command, _Phillips ? 0x20 : 0xA7);        //Invert Display Colour
		}
		
		if(_Phillips){
			SendByte(_command, 0x3A);            //Colour Control
			SendByte(_parameter, 0x03);          //colour mode - 4096 colours
			
			SendByte(_command, 0x36);            //Configure Display
			if (_driver & 1){ //When driver bit 1 is on, then the value of this parameter is ajusted so that x is mirrored from normal.
				_normalScan = 0x60 - ((_driver & 2)<<4);
				_inverseScan = 0xC0 + ((_driver & 2)<<4);
				SendByte(_parameter, _normalScan);      //RGB order, mirror display x or y. 0x60 = RGB, no mirroring
														//									0x68 = BGR, no mirroring
														//									0xA0 = RGB, mirror X and Y
														//									0xA8 = BGR, mirror X and Y
			} else {
				_normalScan = 0x20 - ((_driver & 2)<<4);
				_inverseScan = 0x80 + ((_driver & 2)<<4);
				SendByte(_parameter, _normalScan);      //RGB order, mirror display x or y. 0x20 = RGB, no mirroring
														//									0x28 = BGR, no mirroring
														//									0xE0 = RGB, mirror X and Y
														//									0xE8 = BGR, mirror X and Y
			}
			SendByte(_command, 0x25);            //Contrast Control
			SendByte(_parameter, 0x30);    		 //-63 to 63: sets contrast - 0x30 is default. 
		} else {
			SendByte(_command, 0xBC);            //Display Control
			_normalScan = 0x04; 
			_inverseScan = 0x01;
			SendByte(_parameter, _normalScan);          //Scan direction (left-->right or right-->left)
			SendByte(_parameter, 0x00);          //RGB colour order
			SendByte(_parameter, (_driver & 0x01) ? 0x04 : 0x02);          //colour mode - 4096 colours (for some EPSON Screens 12bpp isn't supported, so we use 16, but scale up 12bits to fit)

			SendByte(_command, 0x81);            //Contrast Control
			SendByte(_parameter, 0x2B);     	 //0 to 63: sets contrast - 0x2B is default. 
			SendByte(_parameter, 0x02);			 //Resistor Ratio - 0x02 should be fine for most screens
		}
		
		delay(100);                          //Allow Power to stablise

		SendByte(_command, _Phillips?0x29:0xAF);            //Display On
		
		delay(40);

		setForeColour(0x0F,0x0F,0x0F);		 //Display is White foreground and Blue background
		setBackColour(0x00,0x00,0x0F);	

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
	//int i,j;

	Window(0,0,131,131);			 //Create a window the size of the screen
    (*this.*setSendColour)(0);//All pixels are the same colour, so do the calculation only once
	for (int i = 0;i < 8844;i++){
		(*this.*sendTwoPixels)(); //send the rest using the existing colours
	}
}

#if ARDUINO >= 100
size_t gLCD::write(const uint8_t character){
	char temp[2] = {0};
	temp[0] = character;
	return write((uint8_t *)temp,1);
}
#else
void gLCD::write(const uint8_t character){
	char temp[2] = {0};
	temp[0] = character;
	write(temp,1);
}
#endif

#if ARDUINO >= 100
size_t gLCD::write(const uint8_t *buffer, size_t size){
#else
void gLCD::write(const uint8_t *buffer, size_t size){
#endif	    
		size_t returnSize = size;
		int j,k, xcnt, ycnt;
		
		boolean wrapText = ((Font >> 3) & 1); //Whether to wrap the font.
		
	    signed char width = (Font & 1) + 1; //Double width (BOLD)
	    signed char height = ((Font >> 1) & 1) + 1; //Double height (Large text when used with fontwidth)
		boolean background = ((Font >> 2) & 1); //Whether the text has a background

		int X = X1;
		unsigned char _X1 = X1;
		int startX = X1;
		int Y = Y1;
		unsigned char _Y1 = Y1;
		int startY = Y1;
		
		char char2print;
		byte data;
		unsigned char databit;
		signed char max = 126 + numberOfCustomCharacters;
	    while (size--){         //Start at beginning of string and work along
			 //Finds the character to print, and adjusts it to a position in the ASCII array
			char2print = *buffer;
			buffer++; //increment pointer for next time.
			if (char2print == 13){
			    //Skip a carraige return
			} if (char2print == 10){
				//If it is a line feed, move to the next line.
				_X1 = startX;
				X = _X1;
				startY += (8*height);
				_Y1 = startY;
				Y = _Y1;
				continue; //Move on to next character in string
			} else if ((char2print < 32)&&(char2print > max)&&(max < 0)){ //The > max allows for the 'numberOfCustomCharacters' custom characters to be used
				//If it is not a printable character, print a space instead.
				char2print = 0;
			} else if (((char2print < 32)||(char2print > max))&&(max > 0)){ //The > max allows for the 'numberOfCustomCharacters' custom characters to be used
				//If it is not a printable character, print a space instead.
				char2print = 0;
			} else {
				char2print -= 32;
			}
			
			byte character = (byte)char2print;
			
			if(background){
				//Print the character
				Window(_X1,_Y1,_X1+(6*width)-1,_Y1+(8*height)-1);			//Create a window the size of one character, then fill it with the background colour
				for (xcnt = 0;xcnt < 5;xcnt++){
					for (j = 0;j < width;j++){
						if (height == 2){
							//If double height, each pair of pixels will be the same, and there will be 8 pairs of them.
							for (ycnt = 0;ycnt < 8;ycnt++){
							#ifdef _LIB_SAM_
								data = charData[character][xcnt];
							#else
								data = pgm_read_byte(&(charData[character][xcnt]));
							#endif
								databit = (data >> ycnt) & 1;
								databit |= databit << 1;
								twoPixels(databit);
							}
						} else {
							//If not height, each pair of pixels will be two distinct pixels, so we need to set the colour for each correctly.
							for (ycnt = 0;ycnt < 7;ycnt += 2){
							#ifdef _LIB_SAM_
								data = charData[character][xcnt];
							#else
								data = pgm_read_byte(&(charData[character][xcnt]));
							#endif
								databit = (data >> ycnt) & 3;
								twoPixels(databit);
							}
						}
					}
				}
				//Fill in the character seperator pixels
				(*this.*setSendColour)(0);
				for (j = 0;j < ((4*height)*width);j++){
					(*this.*sendTwoPixels)();
				}
			} else {
				//Print the character
				for (xcnt = 0;xcnt < 5;xcnt++){
					//Do this once or twice depending on width format
					for (j = 0;j < width;j++){
						for (ycnt = 0;ycnt <8;ycnt++){
						#ifdef _LIB_SAM_
							data = charData[character][xcnt];
						#else
							data = pgm_read_byte(&(charData[character][xcnt]));
						#endif
							databit = (data >> ycnt) & 1; 			//isolate the data bit
							
							//Do this once or twice depending on height format
							for (k = 0;k < height;k++){
								if(databit){
									systemPlot(X,Y,3);
								}
								Y++;//increase Y offset
							}
						}
						X++; //increase X offset
						Y = _Y1; //Y back to zero offset
					}
				}
			}
			_X1 += (6*width); // Move X position so that next character knows where to be placed
			if (wrapText && (128 - _X1 < (6*width)) && (size > 1)){
				//If text wrap is enabled, and there is insufficient space to place the next character, continue on a new line
				if(background){
					Window(_X1,_Y1,128,_Y1+(8*height)-1);			//Create a window the height of one character and to the edge of the screen,
					(*this.*setSendColour)(0);						//then fill it with the background colour
					for (xcnt = 0;xcnt < 128 - _X1;xcnt++){
						for (ycnt = 0;ycnt < 4 * height;ycnt++){
							(*this.*sendTwoPixels)();
						}
					}
				}
				//Now move to the next line ready to print the next character
				_X1 = startX;
				X = _X1;
				startY += (8*height);
				_Y1 = startY;
				Y = _Y1;
				if (Y > 128){
#if ARDUINO >= 100
				  return (returnSize - size); //No point going any further, just drop the rest of the text and return the amount already printed.
#else
				  return;
#endif
				}
			}
			X = _X1; //X back to zero offset
	    }
#if ARDUINO >= 100
		return returnSize;
}
#else
}
#endif	

/*
void gLCD::Print(String text, unsigned signed char X1, unsigned signed char Y1, byte Font){
	    
		int i,j,k, xcnt, ycnt;
		
		
	    signed char width = (Font & 1) + 1; //Double width (BOLD)
	    signed char height = ((Font >> 1) & 1) + 1; //Double height (Large text when used with fontwidth)
		boolean background = ((Font >> 2) & 1); //Whether the text has a background

		int X = X1;
		int startX = X1;
		int Y = Y1;
		int startY = Y1;
		
		int length = text.length(); //Length of the string to be printed

		char char2print;
		byte data;
		unsigned char databit;
		signed char max = 126 + numberOfCustomCharacters;
		
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
			} else if ((char2print < 32)&&(char2print > max)&&(max < 0)){ //The > max allows for the 'numberOfCustomCharacters' custom characters to be used
				//If it is not a printable character, print a space instead.
				char2print = 0;
			} else if (((char2print < 32)||(char2print > max))&&(max > 0)){ //The > max allows for the 'numberOfCustomCharacters' custom characters to be used
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
									systemPlot(X,Y,3);
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
*/
void gLCD::systemPlot(unsigned char _X1, unsigned char _Y1, unsigned char Colour){
		//The systemPlot function does not set the global coordinate as it may be being used as a reference by an internal function.
		Window(_X1,_Y1,_X1,_Y1);                          //Creates a window of 1 pixel
		Colour |= Colour << 1;
		twoPixels(Colour);
}

void gLCD::systemPlot(unsigned char _X1, unsigned char _Y1){
		//The systemPlot function does not set the global coordinate as it may be being used as a reference by an internal function.
		Window(_X1,_Y1,_X1,_Y1);                          //Creates a window of 1 pixel
		(*this.*sendTwoPixels)();
}

void gLCD::Plot(unsigned char _X1, unsigned char _Y1, unsigned char Colour){
		setCoordinate(_X1,_Y1);
		systemPlot(X1,Y1,Colour); //Call the system plot function
}

void gLCD::Plot(unsigned char _X1, unsigned char _Y1){
		Plot(_X1,_Y1,format >> 2); //Use the format variable instead
}

void gLCD::Plot(unsigned char Colour){
		systemPlot(X1,Y1,Colour);
}

void gLCD::Plot(){
		Plot(format >> 2); //Use the format variable instead
}

void gLCD::setFormat(byte _format){
		format = _format;
}

void gLCD::setFont(byte _Font) {
		Font = _Font;
}

void gLCD::setCoordinate(unsigned char _X1, unsigned char _Y1, unsigned char _X2, unsigned char _Y2){
		setCoordinate(_X1,_Y1);
		setCoordinate(_X2,_Y2,2);
}

void gLCD::setCoordinate(unsigned char X, unsigned char Y, byte pair){
		if(pair == 1){
			X1 = X;
			Y1 = Y;
		} else {
			X2 = X;
			Y2 = Y;
		}
}

void gLCD::Circle(unsigned char _X1, unsigned char _Y1, unsigned char Radius){
		setCoordinate(_X1,_Y1);
		Circle(Radius);
}

void gLCD::Circle(unsigned char Radius, byte _format){
		setFormat(_format);
		Circle(Radius);
}

void gLCD::Circle(unsigned char _X1, unsigned char _Y1, unsigned char Radius, byte _format){
		setFormat(_format);
		Circle(_X1,_Y1,Radius);
		/*
		Implimentation of Bresenham's Circle Algorithm
		*/
}

void gLCD::Circle(unsigned char Radius){
		signed char fillColour = format & 1;
		signed char nofill = (format >> 1) & 1;
		signed char borderColour = (format >> 2) & 1;
		
		fillColour |= fillColour << 1;
		borderColour |= borderColour << 1;
		
		unsigned char X = Radius;
		unsigned char Y = 0;
		signed int error = 0;
		signed int dx = 1 - (Radius << 1);
		signed int dy = 1;
		
		//Have to do it twice if it is filled in unfortunately
		
		if (!nofill){
		    (*this.*setSendColour)(fillColour);
			while (X >= Y){
				CircleFill(X,Y,X1,Y1);
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
		(*this.*setSendColour)(borderColour);
		while (X >= Y){
			CirclePlot(X,Y,X1,Y1);
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

void gLCD::CircleFill(unsigned char _X1, unsigned char _Y1, unsigned char _X2, unsigned char _Y2){

		int i;
		Window(_X2-_X1,_Y2+_Y1,_X2+_X1,_Y2+_Y1); 
		for(i = 0; i < _X1; i++){ 
			(*this.*sendTwoPixels)();
		}
		Window(_X2-_X1,_Y2-_Y1,_X2+_X1,_Y2-_Y1);
		for(i = 0; i < _X1; i++){
			(*this.*sendTwoPixels)();
		}
		Window(_X2-_Y1,_Y2+_X1,_X2+_Y1,_Y2+_X1);
		for(i = 0; i < _Y1; i++){
			(*this.*sendTwoPixels)();
		}
		Window(_X2-_Y1,_Y2-_X1,_X2+_Y1,_Y2-_X1);
		for(i = 0; i < _Y1; i++){
			(*this.*sendTwoPixels)();
		}
}

void gLCD::CirclePlot(unsigned char _X1, unsigned char _Y1, unsigned char _X2, unsigned char _Y2){
		//Circle is Symmetrical, so we can plot the whole thing having only calculated an octant
		systemPlot(_X2+_X1,_Y2+_Y1); //Octant 1
		systemPlot(_X2-_X1,_Y2+_Y1); //Octant 4
		systemPlot(_X2+_X1,_Y2-_Y1); //Octant 8
		systemPlot(_X2-_X1,_Y2-_Y1); //Octant 5
		systemPlot(_X2+_Y1,_Y2+_X1); //Octant 2
		systemPlot(_X2-_Y1,_Y2+_X1); //Octant 3
		systemPlot(_X2+_Y1,_Y2-_X1); //Octant 7
		systemPlot(_X2-_Y1,_Y2-_X1); //Octant 6
}

void gLCD::Line(unsigned char _X1, unsigned char _Y1, unsigned char _X2, unsigned char _Y2, byte _format){
		setCoordinate(_X1,_Y1,_X2,_Y2);
		Line(_format);
}

void gLCD::Line(unsigned char _X1, unsigned char _Y1, unsigned char _X2, unsigned char _Y2){
		setCoordinate(_X1,_Y1,_X2,_Y2);
		Line();
}
		
void gLCD::Line(byte _format){
		setFormat(_format);
		Line();
}

void gLCD::Line(){
		signed char xdir = 1;		 //Amount by which X changes
		signed char ydir = 1;		 //Amount by which Y changes
		signed int error;
		unsigned char i;
		unsigned char X = X1;
		unsigned char Y = Y1;
		
		byte Colour = format >> 2;
		Colour |= Colour << 1;
		(*this.*setSendColour)(Colour);
		/*
		Implimentation of Bresenham's Line Algorithm
		*/
		
		//The algorithm works for only one octant. By reversing the direction, the algorithm can work for 4 of the octants
		
		signed int dx = X2 - X; 	 //Change in X
		signed int dy = Y2 - Y; 	 //Change in Y
		
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
				systemPlot(X,Y); //Print the pixel
				X += xdir;	//move to next x value
				if (error > 0){ 
					//Error is above the midpoint. So, we move up one
					error += (dy2 - dx2);
					Y += ydir;
				} else {
					//Error is below midpoint, so we keep the same y value
					error += dy2;
				}			
			}
		} else {
			//The Y axis see's the largest change, so with each new pixel, Y always changes by 1
			error = dx2 - dy;
			for (i = 0; i <= dy; i++){
				systemPlot(X,Y); //Print the pixel
				Y += ydir;	//move to next y value
				if (error > 0){ 
					//Error is above the midpoint. So, we move right one
					error += (dx2 - dy2);
					X += xdir;
				} else {
					//Error is below midpoint, so we keep the same x value
					error += dx2;
				}
			}
		}
}

void gLCD::Box(unsigned char _X1, unsigned char _Y1, unsigned char _X2, unsigned char _Y2, byte _format){
		setCoordinate(_X1,_Y1,_X2,_Y2);
		Box(_format);
}

void gLCD::Box(unsigned char _X1, unsigned char _Y1, unsigned char _X2, unsigned char _Y2){
		setCoordinate(_X1,_Y1,_X2,_Y2);
		Box();
}
		
void gLCD::Box(byte _format){
		setFormat(_format);
		Box();
}

void gLCD::Box(){		
		signed char fillColour = format & 1;
		signed char noFill = format & 2;
		signed char borderColour = (format >> 2) & 1;
		
		unsigned char dx = (X2 - X1) >> 1;
		unsigned char dy = (Y2 - Y1) >> 1;
		
		fillColour |= fillColour << 1;
		borderColour |= borderColour << 1;
		
		if(!noFill){
			(*this.*setSendColour)(fillColour);
			Window(X1,Y1,X2,Y2);		//Create a window for the box
			for (signed char Y = Y1;Y <= Y2;Y++){
				for (signed char X = X1;X <= X2;X++){
					(*this.*sendTwoPixels)();
				}
			}
		}
		
		//draw border
		(*this.*setSendColour)(borderColour);
		Window(X1, Y1, X2, Y1); 
		for(int i = 0; i <= dx; i++){
			(*this.*sendTwoPixels)();
		}
		Window(X2, Y1, X2, Y2);
		for(int i = 0; i <= dy; i++){
			(*this.*sendTwoPixels)();
		}
		Window(X1, Y2, X2, Y2);
		for(int i = 0; i <= dx; i++){
			(*this.*sendTwoPixels)();
		}
		Window(X1, Y1, X1, Y2);
		for(int i = 0; i <= dy; i++){
			(*this.*sendTwoPixels)();
		}
}

void gLCD::RedGreen(unsigned char _X1, unsigned char _Y1, unsigned char _X2, unsigned char _Y2){
	int dy = (_Y2 - _Y1) >> 4; //Y2 - Y1 should be a multiple of eight when invoking this, otherwise it wont work
	int dx = (_X2 - _X1) >> 5; //X2 - X1 should be a multiple of sixteen when invoking this, otherwise it wont work
	
	Window(_X1,_Y1,_X2-1,_Y2-1);
	for (int i = 0;i < 16;i++){
		for (int k = 0;k < dy;k++){
			for (int j = 0;j < 16;j++){
				setForeColour(i,j,0);
				(*this.*setSendColour)(3);
				for (int l = 0;l < dx;l++){
					(*this.*sendTwoPixels)();
				}
			} 
		}
	}
}

void gLCD::GreenBlue(unsigned char _X1, unsigned char _Y1, unsigned char _X2, unsigned char _Y2){
	int dy = (_Y2 - _Y1) >> 4; //Y2 - Y1 should be a multiple of eight when invoking this, otherwise it wont work
	int dx = (_X2 - _X1) >> 5; //X2 - X1 should be a multiple of sixteen when invoking this, otherwise it wont work
	
	Window(_X1,_Y1,_X2-1,_Y2-1);
	for (int i = 0;i < 16;i++){
		for (int k = 0;k < dy;k++){
			for (int j = 0;j < 16;j++){
				setForeColour(0,i,j);
				(*this.*setSendColour)(3);
				for (int l = 0;l < dx;l++){
					(*this.*sendTwoPixels)();
				}
			} 
		}
	}
}

void gLCD::BlueRed(unsigned char _X1, unsigned char _Y1, unsigned char _X2, unsigned char _Y2){
	int dy = (_Y2 - _Y1) >> 4; //Y2 - Y1 should be a multiple of eight when invoking this, otherwise it wont work
	int dx = (_X2 - _X1) >> 5; //X2 - X1 should be a multiple of sixteen when invoking this, otherwise it wont work
	
	Window(_X1,_Y1,_X2-1,_Y2-1);
	for (int i = 0;i < 16;i++){
		for (int k = 0;k < dy;k++){
			for (int j = 0;j < 16;j++){
				setForeColour(j,0,i);
				(*this.*setSendColour)(3);
				for (int l = 0;l < dx;l++){
					(*this.*sendTwoPixels)();
				}
			} 
		}
	}
}

void gLCD::ColourBars(unsigned char _X1, unsigned char _Y1, unsigned char _X2, unsigned char _Y2){

	int dy = _Y2 - _Y1;
	int dx = (_X2 - _X1) >> 4;
	
	char colour[6][3] = {
		{15,0,0},
		{15,15,0},
		{0,15,0},
		{0,15,15},
		{0,0,15},
		{15,0,15}
	};
	
	Window(_X1,_Y1,_X2-1,_Y2-1);
	for (int i = 0;i < 6;i++){
		setForeColour(colour[i][0],colour[i][1],colour[i][2]);
		(*this.*setSendColour)(3);
		for (int k = 0;k < dx;k++){
			for (int j = 0;j < dy;j++){
				(*this.*sendTwoPixels)();
			} 
		}
	}
	dx = dx << 2;
	dy = dy >> 5;
	
	for (int k = 0;k < dx;k++){
		for (int j = 0;j < 16;j++){
			setForeColour(j,j,j);
			(*this.*setSendColour)(3);
			for (int l = 0;l < dy;l++){
				(*this.*sendTwoPixels)();
			} 
		}
	}
}

void gLCD::testPattern(){
	setBackColour(15,15,15);
	Clear();
	RedGreen(1,1,65,65);
	GreenBlue(1,65,65,129);
	BlueRed(65,1,129,65);
	ColourBars(65,65,129,129);
}