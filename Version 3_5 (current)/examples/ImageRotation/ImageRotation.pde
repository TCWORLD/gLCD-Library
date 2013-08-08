/*
  gLCD Library Example 3:
  
  This example shows how to use the setRotation() function to rotate the screen.
  
  gLCD should work for all Nokia Clone 128x128 screens which have the
  Epson or Phillips controller chip.
*/

#include <gLCD.h>

//You can use these variables to set the pin numbers
const char RST = 8;
const char CS = 9;
const char Clk = 13;
const char Data = 11;

/*Create an instance of the display. Lets call it 'graphic'.
  There are four variables,
  which define which pins the LCD is connected too. 
  these are:
    Reset, Chip Select, Clock, Data.
  
  A fifth variable 'speed' can be included as 0 or 1, which controls whether to enter high speed mode (see below).
  If the fifth variable is omitted (i.e. only the first four are given), normal speed mode is implied.

  gLCD graphic(RST,CS,Clk,Data [,speed]);

  Note, it is also possible to enable a high speed mode which increases the speed of the display
  by a factor of >5. This is done through the library bypassing the digitalWrite function and
  directly addressing port registers. 
  For the Due, High speed mode increases speed to such an extent that this example completes before you can blink.
  
  Please note that while this doesn't affect how you use the library (it is all handled internally),
  it is possible that it may run too fast for your display and thus the display will appear to not work. 
  This is UNLIKELY to happen, and I have checked with several displays which all worked fine.
  
  As of version 2.4 nothing special needs to be done to use this high speed mode, so I am now mentioning
  it is the example file.
  
*/
//For normal speed, use:
//gLCD graphic(RST,CS,Clk,Data,NORMAL_SPEED); //Normal speed

//For high speed, use:
gLCD graphic(RST,CS,Clk,Data,HIGH_SPEED); //High speed


void setup() {  
  /*Display needs to be initialised. You only need to do this once,
    You may have to press the Arduino reset button after uploading
    your code as the screen may fail to startup otherwise
    
    The first two variables in the begin() call specify where on the screen
    origin is. On some screens the first one or two rows/cols of
    pixels aren't visible, so begin(X,Y,,) allows all X and Y co-ords
    to be shifted slightly.
    
    The third variable specifies whether the colours are inverted.
    If the White background is Black on your screen, set this to a 1
    Else leave it as a zero
    
    The fourth variable is the driver to use you can choose from. There are 6 drivers:
    EPSON (or) EPSON_4 (both are the same) 
    EPSON_5
    PHILLIPS_0
    PHILLIPS_1
    PHILLIPS_2
    PHILLIPS_3 
    
    For an Epson Screen:
  */
  
  //This
  graphic.begin(0,0,0,EPSON); //Normal Epson
  //or
  //graphic.begin(0,0,0,EPSON_4); //Normal Epson
  //or
  //graphic.begin(0,0,0,EPSON_5); //16bit mode Epson - suits some rare screens.
  
  //For a Phillips Screen:
  //This
  //graphic.begin(0,0,0,PHILLIPS_0); //Normal X direction
  //or
  //graphic.begin(0,0,0,PHILLIPS_1); //Revesed X direction.
  //or
  //graphic.begin(0,0,0,PHILLIPS_2); //Normal X direction, Mirrored.
  //or
  //graphic.begin(0,0,0,PHILLIPS_3); //Revesed X direction, Mirrored.
  
  /*If you can't see the colours properly, then uncomment the 
    graphic.Contrast() function. 
    If the Screen is too dark, or you cant see anything send a value >0x2B (>0x30 for Phillips). If you cant see all
    the different colours distinctly on the test pattern, send a value <0x2B (<0x30 for Phillips). The default values
    should work for many screens, so you may not have to use this at all.
    
    Range for phillips: -0x3F to 0x3F
    Range for EPSON:    0x00 to 0x3F
  */

  //graphic.Contrast(0x2B);
}
void loop(){
  static ImageRotation rotation = ROTATION_0; //Setup a variable to store the current rotation
  graphic.setRotation(rotation++); //set the current rotation, then increment it for next time

  //We want a white background, so that would be 15 for each variable
  graphic.setBackColour(15,15,15);
  
  /* Next we will write Hello in the top left corner. For this we need to use the print() function. This behaves exactly like Serial.print() only it prints to the screen not the
    serial port.
    
    First though we need to setup the text. There are two functions to do this.
    setCoordinate(X,Y);
    and
    setFont(Font);
                                                                           
    In setCoordinate(X,Y), we set the co-ordinates of where the text will be placed on the screen - (X,Y) pixels denotes the top left corner. 
                                                  NOTE: Currently there is no text wrap so strings that dont fit on the screen will be clipped. 
                                                        However you can use a '\n' character to print the characters following it on a new line directly below.
    
    Then, in setFont(Font), we set the Font. This controls the vertical and horizontal scaling of the text, and also whether it has a solid or transparent background.
                                                                          Font bits have the following meaning: (b7..b3 are ignored - maybe future use)
                
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
                     
    Or you can use one of the predefined constants:
    Normal_ClearBG = 0b000 = 0
    Wide_ClearBG = 0b001 = 1
    Tall_ClearBG = 0b010 = 2
    Large_ClearBG = 0b011 = 3
    Normal_SolidBG = 0b100 = 4
    Wide_SolidBG = 0b101 = 5
    Tall_SolidBG = 0b110 = 6
    Large_SolidBG = 0b111 = 7
    Normal_ClearBG_Wrap = 0b1000 = 8
    Wide_ClearBG_Wrap = 0b1001 = 9
    Tall_ClearBG_Wrap = 0b1010 = 10
    Large_ClearBG_Wrap = 0b1011 = 11
    Normal_SolidBG_Wrap = 0b1100 = 12
    Wide_SolidBG_Wrap = 0b1101 = 13
    Tall_SolidBG_Wrap = 0b1110 = 14
    Large_SolidBG_Wrap = 0b1111 = 15
    
    
    We then finally call the print function with our text or variable, e.g.
    graphic.print("Some Text");
        See print() in the Arduino Reference for more detains.
  */
  graphic.setForeColour(0,0,15); //Text is coloured Blue
  graphic.setFont(Normal_SolidBG); //normal size text, solid background.
  graphic.setCoordinate(0,0);
  graphic.print("Hello\nWorld!"); //Hello and World will be printed on seperate lines as governed by the newline character '\n'
  
  //We want a red foreground
  graphic.setForeColour(GLCD_RED); 
  for (int i = 13;i < 21;i++){
    for (int j = 13;j < 21;j++){
      graphic.Plot((i*5), (j*5),3); //Draw a grid of 64 dots.
    }
  } 
   
  delay(2000); //wait 2 seconds, then repeat.
}
