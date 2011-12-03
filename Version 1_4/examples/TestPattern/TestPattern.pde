/*
  gLCD Library Example 1:
  
  This example shows you how to create an instance of the display,
  connect it to the correct pins, and then display the built in
  Test Pattern.
  
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
 /*If you can't see the colours properly, then uncomment the 
   graphic.Contrast() function. 
   If the Screen is too dark, or you cant see anything send a value >0x2B (>0x30 for Phillips). If you cant see all
   the different colours distinctly on the test pattern, send a value <0x2B (<0x30 for Phillips). The default values
   should work for many screens, so you may not have to use this at all.
 */

 //graphic.Contrast(0x2B);
  
  
 /*Display needs to be initialised. You only need to do this once,
   You may have to press the Arduino reset button after uploading
   your code as the screen may fail to startup otherwise
   
   The first two variables in the Init call specify where on the screen
   (0,0) is. On some screens the first one or two rows/cols of
   pixels aren't visible, so Init(X,Y,,) allows all X and Y co-ords
   to be shifted slightly. (0,2) works well for both my screens.
   
   The third variable specifies whether the colours are inverted.
   If the White background is Black on your screen, set this to a 1
   Else leave it as a zero
   
   If you have a Phillips screen, you need to provide a fourth variable
   i.e. Init(0,0,0,1,0); where the 1 is the fourth variable. This tells the
   library to use the phillips startup sequence. The fifth byte for a
   phillips screen mirrors it in the X direction when set to 1.
   
   If you have an Epson screen dont use these variables;
   i.e. Init(0,0,0);
   
   For an Epson Screen:
 */
 
 graphic.Init(0,2,0);
 
 //For a Phillips Screen:
 //This
 //graphic.Init(0,2,0,1,0); //Normal X direction
 //or
 //graphic.Init(0,2,0,1,1); //Revesed X direction.
}
void loop() {
  //Print out the test pattern.
  graphic.testPattern();
  while(1); //Finished
}
