//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
//WW                  WWW           WWW WWW           WWW                    WW
//WW                   WWW   WWW   WWW   WWW   WWW   WWW                     WW
//WW                    WWW WW WW WWW     WWW WW WW WWW                      WW
//WW                     WWWW   WWWW       WWWW   WWWW                       WW
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW


#pragma once

#include <iostream>
#include <stdexcept> 

#include "SudokuHistory.h"
#include "SudokuItem.h"
#include "SudokuTripple.h"

class SudokuBox : public SudokuItemListener {

  SudokuItem items[9];

public:

  SudokuBox();

  void setHistory(SudokuHistory *history);

  SudokuTripple getColumnTripple(unsigned char index);

  SudokuTripple getRowTripple(unsigned char index);

  bool setLastItem();

  bool setLastChance();

  bool setSingleChoice();

  bool isComplete() const;

  bool containsValue(unsigned char value) const;

  bool lineMustContainValue(unsigned char value, unsigned char lineIndex, bool horizontal) const;

  void notify(unsigned char impossibleValue);

  void print();
};