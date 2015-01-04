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
#include "SudokuItemGroup.h"
#include "SudokuTripple.h"

class SudokuBox : public SudokuItemGroup {

  SudokuItem items[9];

public:

  SudokuBox();

  void setHistory(SudokuHistory *history);

  SudokuTripple getColumnTripple(unsigned char index);

  SudokuTripple getRowTripple(unsigned char index);

  unsigned int countFixedValues() const;

  bool setLastItem();

  bool setLastChance();

  bool setSingleChoice();

  bool isComplete() const;

  bool lineMustContainValue(unsigned char value, unsigned char lineIndex, bool horizontal) const;

  void notify(unsigned char impossibleValue);

  SudokuItem *getItem(unsigned char index);

  const SudokuItem *getConstItem(unsigned char index) const;

  void print() const;
};
