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

public:

  /**
   * defined according http://sudoku.soeinding.de/strategie/strategie03.php
   */
  enum DifficultyLevel {
    VERY_EASY,
    EASY,
    DEFAULT,
    MODERATE,
    DEMANDING,
    VERY_DEMANDING,
    DEVILISHLY,
    VERY_DEVILISHLY
  };

private:  

  SudokuBox boxes[9];
  SudokuLine columns[9];
  SudokuLine rows[9];

  SudokuHistory history;
  DifficultyLevel level;

public:

  SudokuField();

  unsigned int countFixedValues() const;

  bool setValue(unsigned char column, unsigned char row, unsigned char value);

  bool isSolved() const;

  bool solve();

  DifficultyLevel getDifficultyLevel() const;

  void printDifficultyLevel() const;

  /**
  * search if in a group only one item
  * can have a certain value
  */
  bool scanValues();

  /**
   * search if a item can be only one value
   */
  bool excludeAlternatives();

  /**
   * search pairs and remove them from other items
   */
  bool checkForPair();

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
