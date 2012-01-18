/*
  gLCD Library Example 1:
  
  This example shows how to use the basic functions: Line, Plot, Box, Circle, Print, SetForeColour, and SetBackColour.
  
  gLCD should work for all Nokia Clone 128x128 screens which have the
  Epson controller chip.
*/

#include <gLCD.h>

//You can use these variables to set the pin numbers
const char RST = 8;
const char CS = 9;
const char Clk = 13;
const char Dat = 11;

/*Create an instance of the display. Lets call it 'graphic'.
  There are four variables,
  which define which pins the LCD is connected too. 
  these are:
    Reset, Chip Select, Clock, Data 
*/
gLCD graphic(RST,CS,Clk,Dat);


void setup() {  
 /*Display needs to be initialised. You only need to do this once,
   You may have to press the Arduino reset button after uploading
   your code as the screen may fail to startup otherwise
   
   The first two variables in the Init call specify where on the screen
   (0,0) is. On some screens the first one or two rows/cols of
   pixels aren't visible, so Init(X,Y,,) allows all X and Y co-ords
   to be shifted slightly. (0,2) works well for both my screens.
   
   The third variable specifies whether the colours are inverted.
   If the White appears as Black on your screen, set this to a 1
   Else leave it as a zero
   
   If you have a Phillips screen, you need to provide a fourth and fifth variable
   i.e. Init(0,0,0,1,xRevese); 
			The fourth variable is 1. This tells the library to use the phillips startup sequence.

			The fifth byte is called xReverse. This controls how the phillips display will behave,
			and requires some trial and error to get right.
			
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
   
   If you have an Epson screen dont use these last two variables;
   i.e. Init(0,0,0);
 */
   
 //For an Epson Screen:
 graphic.Init(0,2,0);
 
 //For a Phillips Screen, use one of this:
 //graphic.Init(0,2,0,1,0); //Normal X direction
 //or this:
 //graphic.Init(0,2,0,1,1); //Revesed X direction.
 //or this:
 //graphic.Init(0,2,0,1,2); //Normal X, Revesed Y direction.
 //or this:
 //graphic.Init(0,2,0,1,3); //Revesed X, Revesed Y direction.
 
 
 
 /*If you can't see the colours properly, then uncomment the 
   graphic.Contrast() function. 
   If the Screen is too dark, or you cant see anything send a value >0x2B (>0x30 for Phillips). If you cant see all
   the different colours distinctly on the test pattern, send a value <0x2B (<0x30 for Phillips). The default values
   should work for many screens, so you may not have to use this at all.
   
   Range for phillips: -0x3F to 0x3F
   Range for EPSON:		0x00 to 0x3F
 */

 //graphic.Contrast(0x2B);
}
void loop() {
  /*Lets draw a box...
  
    First we set the background colour and foreground colour
    We use the SetBackColour function to do this.
    The function takes three bytes, which are: Red, Green, Blue. 
    Each of these is a 4 bit number where 0 = off, 15 = fully on.
  */
    
  //We want a white background, so that would be 15 for each variable
  graphic.SetBackColour(15,15,15);
  
  //We want a red foreground, so red will be 15 and the others 0
  graphic.SetForeColour(15,0,0); 
  
  /*Now We draw our box. Lets use the Box() function.
    Box( X1, Y1, X2, Y2, format) takes 5 variables. 
    
    The first two are: X1, Y1. These are bytes which represent the (x,y) co-ord where the box will start
    
    The second two are: X2, Y2. These bytes represent the (x,y) co-ord where the box will end. NOTE: This coodinate will also be included in the box
    
    The final one is: format. This controls how the box will look (b7..b3 are ignored)

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
  
    Lets draw a box which starts from (10,10) and is 100 pixes square. So, X1 = 10, 
                                                                           Y1 = 10,
                                                                           X2 = 10 + 99,   <- Because X2,Y2 will be part of the box
                                                                           Y2 = 10 + 99 
    It will have a border coloured Red, and be filled with the background colour. So, 'format' = 4
  */
  graphic.Box(10,10,109,109,4);
  
  //Inside is another box filled in the foreground colour
  graphic.Box(20,20,99,99,5);
  
  /* Next we will write Hello in the centre. For this we need to use the Print() function.
    Print( text, X, Y, Font) takes four variables.
    
    The first is: text. This is a String of any length which will be printed on the screen, It can contain any ASCII characters between DEC 32 (space) and DEC 126 (~)
                                                                                              (anything outside this range will just print space).
                                                                                              
    The second two are: X,Y. These are the co-ordinates of where the string will be placed on the screen. 
                                                  NOTE: Currently there is no text wrap so strings that dont fit on the screen will be clipped.
                                                  
    The third is: Font. This controls the vertical and horizontal scaling of the font, and also whether it has a solid or transparent background.
                                                                          
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
  */
  graphic.SetForeColour(0,0,15); //Text is coloured Blue
  graphic.Print("Hello",40,40,0); //Normal sized text, no background
  
  /* Now lets double underline the text twice. Each normal character takes up 6 x 8 pixels, so we need to draw a line 9 pixels below the top of the text
     that is 6*5 = 30px long. And a second of the same length which is 11 pixels below the top of the text.
     
     For this we can use the Line() Function.
     Line(X1,X2,Y1,Y2,Colour) takes five variables
     
     Firstly X1 and Y1 are both unsigned chars which are where the line starts.
     
     The second two are: X2,Y2. These are the last point on the line.
     
     Lastly: Colour. This defines whether the line should be in Foreground colour (Colour = 1) or Background colour (Colour = 0)
  */
  graphic.Line(40,49,69,49,1); // The lines will be Blue as that was the last foreground colour that was set.
  graphic.Line(40,51,69,51,1);
  
  /* The next function is Circle().
     Circle(X1,Y1,Radius,Format) takes four variables 
    
    The first two are: X1, Y1. These are bytes which represent the (x,y) co-ord of the centre of the circle.
    
    The next is: Radius. This is the radius of the circle in pixels.
    
    The final one is: Format.  This controls how the Circle will look (b7..b3 are ignored)

						  b2 | b1 | b0 | Meaning
						 ----+----+----+-----------------------------------------------------------------------------
						   0 |  1 |  x | Draws a Circle with just a border of colour BackColour
						 ----+----+----+-----------------------------------------------------------------------------
					           1 |  1 |  x | Draws a Circle with just a border of colour ForeColour
						 ----+----+----+-----------------------------------------------------------------------------
						   0 |  0 |  0 | Draws a Circle with border in BackColour and fill inside it with BackColour
						 ----+----+----+-----------------------------------------------------------------------------
						   1 |  0 |  0 | Draws a Circle with border in ForeColour and fill inside it with BackColour
						 ----+----+----+-----------------------------------------------------------------------------
						   0 |  0 |  1 | Draws a Circle with border in BackColour and fill inside it with ForeColour
						 ----+----+----+-----------------------------------------------------------------------------
						   1 |  0 |  1 | Draws a Circle with border in ForeColour and fill inside it with ForeColour

  */
  graphic.Circle(66,74,15,4); //Draw circle of radius 10px, filled with the background colour 
  
  /* The last basic function is Plot(). This simply sets the colour of the pixel at (x,y) to the current foreground colour.
     Plot(X,Y) takes three variables.
     
     X and Y are the co-odinate where the dot is drawn.
          
     Colour defines whether the line should be in Foreground colour (Colour = 3) or Background colour (Colour = 0)
  */
  for (int i = 15;i < 19;i++){
    for (int j = 17;j < 21;j++){
      graphic.Plot((i*4), (j*4),3); //Draw a grid of 16 dots.
    }
  } 
   
  while(1); //Finished
}
