#include <LEDMultiplexMatrix.h>

// Testing the font
// by Mariana Bocoi <http://www.craft-experiments.de>
// Displays all the symbols in the font from the LEDMultiplexMatrix library.
// Created 2 April 2012

  //array for row pin mapping (bottom to top)
  int rowPins[8] = {13,12,11,10,9,8,7,6};
  //array for column pin mapping (right to left)
  int columnPins[8] = {5,4,3,2,1,0,A5,A4};
  
LEDMultiplexMatrix matrix = LEDMultiplexMatrix( rowPins ,columnPins);

void setup(){
  //Makes the scroll slower default is 10
  matrix.setScrollDelay(15);
}

void loop(){
  /*Scrolls all the avalable symbols string from the right to the left side (left and right of the viewer)
   the """ symbol and the "\" symbol need to be escaped  with an aditional \
  */
  matrix.scrollStringLeft(" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~");
  //Clears the display
  matrix.scrollSpacesLeft(8);
  /*Scrolls all the avalable symbols string from the left to the right side (left and right of the viewer)
   the """ symbol and the "\" symbol need to be escaped  with an aditional \  
   */
  matrix.scrollStringRight("~}|{zyxwvutsrqponmlkjihgfedcba`_^]\\[ZYXWVUTSRQPONMLKJIHGFEDCBA@?>=<;:9876543210/.-,+*)('&%$#\"! ");
  //Clears the display
  matrix.scrollSpacesRight(8);
}

