#include <LEDMultiplexMatrix.h>

// Snake?
// by Mariana Bocoi <http://www.craft-experiments.de>
// Created 2 April 2012

  //array for row pin mapping (bottom to top)
  int rowPins[8] = {13,12,11,10,9,8,7,6};
  //array for column pin mapping (right to left)
  int columnPins[8] = {5,4,3,2,1,0,A5,A4};
  
LEDMultiplexMatrix matrix = LEDMultiplexMatrix( rowPins ,columnPins);
int space;
void setup()
{
  space=7;
}

void loop()
{
  matrix.scrollCharLeft('.');
  matrix.scrollSpacesLeft(space);
  matrix.scrollCharRight('.');
  matrix.scrollSpacesRight(space);
  if(space!=0){
    space--;
  }else{
    space=8;
  }
}

