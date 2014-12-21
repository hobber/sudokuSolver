//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
//WW                  WWW           WWW WWW           WWW                    WW
//WW                   WWW   WWW   WWW   WWW   WWW   WWW                     WW
//WW                    WWW WW WW WWW     WWW WW WW WWW                      WW
//WW                     WWWW   WWWW       WWWW   WWWW                       WW
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW


#pragma once

#include <iomanip>
#include <vector>

#include "SudokuHistory.h"
#include "SudokuItemListener.h"
#include "SudokuItemState.h"

class SudokuItemState;
class SudokuHistory;

class SudokuItem
{
  SudokuItemState *state;
  std::vector<SudokuItemListener*> listeners;
  SudokuHistory *history;
  
public:

  SudokuItem();
  ~SudokuItem();

  void setID(unsigned char ID);

  void setHistory(SudokuHistory *history);

  bool testValue(unsigned char value) const;

  void addListener(SudokuItemListener* listener);

  bool setSingleChoice();

  bool setValue(unsigned char value);

  bool disableValue(unsigned char value);

  unsigned char getValue() const;

  bool isFixed() const;

  std::vector<unsigned char> getPossibilites() const;

  void setState(const SudokuItemState &state);

  const SudokuItemState &getState() const;

  void print() const;
};