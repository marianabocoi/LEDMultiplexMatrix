/*
 LEDMultiplexMatrix.h - Library for Scrolling text on an 8x8 LED Multiplex Matrix.
 Created by Mariana Bocoi, April 2, 2012.
 Copyright (c) 2012 Mariana Bocoi 
 The font is Copyright (c) 2012 Mariana Bocoi 
 
 The program uses an array of bytes to represent the states of the matrix called frame. It uses the frame as a buffer in between displays to keep track of what was displayed before.
 
 To display the frame it lights up each column of the frame at a time for some ms(_delayMS), then displays the frame several times(_displayDelay).
 */

#include "Arduino.h"
#include "LEDMultiplexMatrix.h"

/*
 Font where each glyph has max 5 with and 8 height. 
 The glyphs are all the ASCII symbols in the correct order from "!"(dec 33) to "~"(dec 126). The space " "(dec 32) is represented later by 3 spaces in total(one by default after the previous glyph and one by default after the empty column).
 The glyphs are represented in byte columns, because it makes the scrolling easy and it is memory efficient.
*/
byte _glyphs[_FONT_GLYPHS][_FONT_WIDTH]={{95,0,0,0,0},{1,1,0,0,0},{20,62,20,62,20},{4,42,107,42,16},{32,18,72,4,0},{44,82,82,32,80},{1,0,0,0,0},{28,34,65,0,0},{65,34,28,0,0},{5,2,5,0,0},{8,28,8,0,0},{64,32,0,0,0},{8,8,8,0,0},{32,0,0,0,0},{96,56,14,3,0},{30,33,33,33,30},{2,63,0,0,0},{34,49,41,37,34},{18,33,37,37,26},{8,12,10,63,8},{23,37,37,37,25},{30,41,41,41,18},{33,17,9,5,3},{26,37,37,37,26},{18,37,37,37,30},{18,0,0,0,0},{32,18,0,0,0},{8,20,34,0,0},{20,20,20,0,0},{34,20,8,0,0},{2,1,81,9,6},{28,34,73,85,95},{62,9,9,9,62},{63,37,37,37,26},{30,33,33,33,18},{63,33,33,33,30},{63,37,37,37,33},{63,9,9,9,1},{30,33,41,41,26},{63,8,8,8,63},{33,63,33,0,0},{16,32,32,32,31},{63,4,4,10,49},{63,32,32,32,0},{63,2,4,2,63},{63,2,4,8,63},{30,33,33,33,30},{63,9,9,15,0},{30,33,33,33,94},{63,9,9,9,54},{18,37,37,37,24},{1,1,63,1,1},{31,32,32,32,31},{3,28,32,28,3},{31,32,31,32,31},{33,18,12,18,33},{3,4,56,4,3},{49,41,37,35,33},{127,65,0,0,0},{3,14,56,96,0},{65,127,0,0,0},{2,1,2,0,0},{64,64,64,64,64},{1,2,0,0,0},{24,36,36,60,0},{63,36,36,24,0},{24,36,36,36,0},{24,36,36,63,0},{24,44,44,8,0},{62,9,9,0,0},{24,-92,-92,124,0},{63,4,4,60,0},{61,0,0,0,0},{-128,125,0,0,0},{63,8,20,32,0},{63,0,0,0,0},{60,4,56,4,56},{60,4,4,56,0},{24,36,36,24,0},{-4,36,36,24,0},{24,36,36,-4,0},{60,8,4,0,0},{44,44,52,0,0},{4,63,4,0,0},{28,32,32,60,0},{12,48,8,4,0},{28,32,28,32,28},{36,24,24,36,0},{28,-96,-96,124,0},{36,52,44,36,0},{8,62,65,0,0},{127,0,0,0,0},{65,62,8,0,0},{2,1,2,1,0}};

LEDMultiplexMatrix::LEDMultiplexMatrix(int rowPins[_FRAME_HEIGHT], int columnPins[_FRAME_WIDTH]){
    //initialize delay times
    _displayDelay=10;
    _delayMS=1;
    
    for(int i=0; i < _FRAME_HEIGHT; i++) {
        _rowPins[i] = rowPins[i];
        pinMode(_rowPins[i], OUTPUT);
    }
    for(int i=0; i < _FRAME_WIDTH; i++) {
        _frame[i]=0;
        _columnPins[i] = columnPins[i];
        pinMode(_columnPins[i], OUTPUT);
    }
}
void LEDMultiplexMatrix::setScrollDelay(int delay){
    _displayDelay = delay;
}
void LEDMultiplexMatrix::scrollStringLeft(String s){
    for(int k=0;k<s.length();k++){
        scrollCharLeft(s.charAt(k));
    }
}
void LEDMultiplexMatrix::scrollCharLeft(char ch){
    if(ch>32 && ch<127){
        pushGlyphLeft(ch-33);
    }else{
        if(ch==32){
            //space
            if (_FONT_WIDTH>3) {
                scrollSpacesLeft(_FONT_WIDTH-2);
            }else{
                scrollSpacesLeft(_FONT_WIDTH);
            }
        }else{
             scrollSpacesLeft(_FONT_WIDTH);
        }
    }
}
void LEDMultiplexMatrix::pushGlyphLeft(int glyphNr){
    for(int i=0;i<_FONT_WIDTH;i++){
        if(_glyphs[glyphNr][i]!=0){
            for(int j=0;j<_FRAME_WIDTH-1;j++){
                _frame[j]=_frame[j+1];
            }
            _frame[_FRAME_WIDTH-1]=_glyphs[glyphNr][i];
            printFrame();
        }
    }
    scrollSpaceLeft();
}
void LEDMultiplexMatrix::scrollSpaceLeft(){
    for(int j=0;j<_FRAME_WIDTH-1;j++){
        _frame[j]=_frame[j+1];
    }
    _frame[_FRAME_WIDTH-1]=0;
    printFrame();
}
void LEDMultiplexMatrix::scrollSpacesLeft(int spaceNr){
    for(int i=0;i<spaceNr;i++){
        scrollSpaceLeft();
    }
}
void LEDMultiplexMatrix::scrollStringRight(String s){
    for(int k=0;k<s.length();k++){
        scrollCharRight(s.charAt(k));
    }
}
void LEDMultiplexMatrix::scrollCharRight(char ch){
    if(ch>32 && ch<127){
        pushGlyphRight(ch-33);
    }else{
        if(ch==32){
            //space
            scrollSpaceRight();
        }
        scrollSpacesRight(_FONT_WIDTH);
    }
}
void LEDMultiplexMatrix::pushGlyphRight(int glyphNr){
    for(int i=_FONT_WIDTH-1;i>=0;i--){
        if(_glyphs[glyphNr][i]!=0){
            for(int j=_FRAME_WIDTH-2;j>=0;j--){
                _frame[j+1]=_frame[j];
            }
            _frame[0]=_glyphs[glyphNr][i];
            printFrame();
        }
    }
    scrollSpaceRight();
}
void LEDMultiplexMatrix::scrollSpaceRight(){
    for(int j=_FRAME_WIDTH-2;j>=0;j--){
        _frame[j+1]=_frame[j];
    }
    _frame[0]=0;
    printFrame();
}
void LEDMultiplexMatrix::scrollSpacesRight(int spaceNr){
    for(int i=0;i<spaceNr;i++){
        scrollSpaceRight();
    }
}
void LEDMultiplexMatrix::printFrame(){
    for(int t=0;t<_displayDelay;t++){
        _drawFrame();
    }
}
void LEDMultiplexMatrix::_drawFrame(){
    for(int column=0; column<_FRAME_WIDTH; column++){
        activateFrameColumn(column);
    }
}
void LEDMultiplexMatrix::activateFrameColumn(int col){
    //switch the led on
    //row pin (cathode) high
    for(int i=0;i<_FRAME_HEIGHT;i++){
        if(_frame[col] & (1<< (7-i))){
            digitalWrite(_rowPins[i], HIGH);
        }
    }
    //column pin (anode) low
    digitalWrite(_columnPins[col], LOW);
    
    //wait 1-5ms
    delay(_delayMS);
    
    //reverse bias the LED again -- switch the leds off
    deactivateFrameColumn(col);
}
void LEDMultiplexMatrix::deactivateFrameColumn(int col){
    //reverse bias the LED -- switch the led off
    //row (cathode) low
    for(int i=0;i<_FRAME_HEIGHT;i++){
        digitalWrite(_rowPins[i], LOW);
    }
    //column pin (anode) high
    digitalWrite(_columnPins[col], HIGH);
}