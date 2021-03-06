//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
//WW                  WWW           WWW WWW           WWW                    WW
//WW                   WWW   WWW   WWW   WWW   WWW   WWW                     WW
//WW                    WWW WW WW WWW     WWW WW WW WWW                      WW
//WW                     WWWW   WWWW       WWWW   WWWW                       WW
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW


#pragma once

#include <iostream>

#include "SudokuItem.h"
#include "SudokuItemListener.h"

class SudokuTripple {

  SudokuItem *items[3];

public:

  SudokuTripple();

  SudokuTripple(SudokuItem *item0, SudokuItem *item1, SudokuItem *item2);

  SudokuTripple(const SudokuTripple &rhs);

  SudokuItem *getItem(unsigned char index) const;

  bool setValue(unsigned char index, unsigned char value);

  void addListener(SudokuItemListener* listener);

  bool disableValue(unsigned char impossibleValue);

  void print() const;
};