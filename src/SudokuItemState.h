//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
//WW                  WWW           WWW WWW           WWW                    WW
//WW                   WWW   WWW   WWW   WWW   WWW   WWW                     WW
//WW                    WWW WW WW WWW     WWW WW WW WWW                      WW
//WW                     WWWW   WWWW       WWWW   WWWW                       WW
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW


#pragma once

#include <iostream>

#include "SudokuItem.h"

class SudokuItem;

struct SudokuItemState {
  unsigned char ID;
  bool possibilites[9];
  unsigned char value;
  SudokuItem *item;

  SudokuItemState(SudokuItem *item);

  SudokuItemState(const SudokuItemState &src);

  void set(const SudokuItemState &src);

  friend std::ostream& operator<< (std::ostream &out, const SudokuItemState& state)
  {
    out << "Field " << (int)state.ID << ": ";
    for(unsigned char i=0; i<9; i++)
    	out << state.possibilites[i] ? "1" : "0";
    if(state.value > 0)
    	out << " = " << (int)state.value;
    return out;
  }

  void print() const;
};
