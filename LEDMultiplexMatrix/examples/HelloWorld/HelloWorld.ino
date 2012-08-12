#include <LEDMultiplexMatrix.h>

// Scrolling a string to the right
// by Mariana Bocoi <http://www.craft-experiments.de>
// Demostrates how to scroll the String "Hello World!" with the LEDMultiplexMatrix library.
// Created 2 April 2012

  //array for row pin mapping (bottom to top)
  int rowPins[8] = {13,12,11,10,9,8,7,6};
  //array for column pin mapping (right to left)
  int columnPins[8] = {5,4,3,2,1,0,A5,A4};
  
LEDMultiplexMatrix matrix = LEDMultiplexMatrix( rowPins ,columnPins);

void setup(){
}

void loop(){
  //Scrolls the "Hello World!" string from the to the left side
  matrix.scrollStringLeft("Hello World!");
  //Scrolls 8 empty columns to the left one by one
  matrix.scrollSpacesLeft(8);
}

