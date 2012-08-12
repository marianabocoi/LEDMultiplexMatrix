#include <LEDMultiplexMatrix.h>

// Passing a "Bannana?" from the left to the right
// by Mariana Bocoi <http://www.craft-experiments.de>
// Created 2 April 2012

  //array for row pin mapping (bottom to top)
  int rowPins[8] = {13,12,11,10,9,8,7,6};
  //array for column pin mapping (right to left)
  int columnPins[8] = {5,4,3,2,1,0,A5,A4};
  
LEDMultiplexMatrix matrix = LEDMultiplexMatrix( rowPins ,columnPins);

void setup()
{
}

void loop()
{
  matrix.scrollStringLeft("Bannana?");
  matrix.scrollSpacesLeft(8);
  matrix.scrollStringRight("?anannaB");
  matrix.scrollSpacesRight(8);
}

