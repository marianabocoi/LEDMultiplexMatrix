/*
 LEDMultiplexMatrix.h - Library for Scrolling text on an 8x8 LED Multiplex Matrix.
 Created by Mariana Bocoi, April 2, 2012.
 Copyright (c) 2012 Mariana Bocoi 
*/

#ifndef LEDMultiplexMatrix_Header_h
#define LEDMultiplexMatrix_Header_h
//font dimensions
#define _FONT_WIDTH 5
#define _FONT_HEIGHT 8 
#define _FONT_GLYPHS 94
//frame dimensions
#define _FRAME_WIDTH 8
#define _FRAME_HEIGHT 8

#include "Arduino.h"

class LEDMultiplexMatrix
{
public:
    LEDMultiplexMatrix(int rowPins[_FRAME_HEIGHT], int columnPins[_FRAME_WIDTH]);
    
    //Left scroll
    void scrollStringLeft(String s);
    void scrollCharLeft(char ch);
    //a space is an empty column
    void scrollSpaceLeft();
    //scrolls "spaceNr" emprty columns
    void scrollSpacesLeft(int spaceNr);
    
    //Right scroll
    void scrollStringRight(String s);
    void scrollCharRight(char ch);
    //a space is an empty column
    void scrollSpaceRight();
    //scrolls "spaceNr" emprty columns
    void scrollSpacesRight(int spaceNr);
    
    void setScrollDelay(int delay);
    
private:
    //variable that memorises the current state of the LED Matrix
    //used as a buffer between prints
    byte _frame[_FRAME_WIDTH];
    
    //the number of times the frame is displayed before changing to the next _frame
    int _displayDelay;
    //the number of milliseconds it waits while displaying one column of the _frame
    int _delayMS;
    
    //array for row pin mapping (bottom to top)
    int _rowPins[_FRAME_HEIGHT];
    //array for column pin mapping (right to left)
    int _columnPins[_FRAME_WIDTH];
    
    //pushes one symbol from the font to the left one column at a time 
    //while pusing the current content of the _frame out on the right side 
    void pushGlyphLeft(int glyphNr);
    //pushes one symbol from the font to the right one column at a time 
    //while pusing the current content of the _frame out on the left side
    void pushGlyphRight(int glyphNr);
    
    //displays the _frame "_displayDelay" times
    void printFrame();
    
    // calls activateFrameColumn(int col) for each column in the _frame
    void _drawFrame();
    
    //switches on the leds corresponding to 1 in the _frame for one column for "_delayMS" ms
    void activateFrameColumn(int col);
    //switches a column off
    void deactivateFrameColumn(int col);
};
#endif