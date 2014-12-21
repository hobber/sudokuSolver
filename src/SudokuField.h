//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
//WW                  WWW           WWW WWW           WWW                    WW
//WW                   WWW   WWW   WWW   WWW   WWW   WWW                     WW
//WW                    WWW WW WW WWW     WWW WW WW WWW                      WW
//WW                     WWWW   WWWW       WWWW   WWWW                       WW
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW


#pragma once

#include <ctype.h>
#include <iomanip>
#include <iostream>
#include <vector>

#include "SudokuBox.h"
#include "SudokuHistory.h"
#include "SudokuLine.h"

class SudokuField {

  SudokuBox boxes[9];
  SudokuLine columns[9];
  SudokuLine rows[9];

  SudokuHistory history;

public:

  SudokuField();

  bool setValue(unsigned char column, unsigned char row, unsigned char value);

  bool isSolved() const;

  bool solve();

  /**
  * test for each tripple in a box if it is the last 
  * one which can contain a value. If so, then this
  * value can be delete from other lines possibilities.
  */
  bool filterValues();

  std::vector<unsigned char> getPossibilites(unsigned char ID) const;

  void readFromInput();

  void undo(unsigned int steps=1);

  void redo(unsigned int steps=1);

  void print();
};
