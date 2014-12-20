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

  SudokuTripple()
  {
    items[0] = NULL;
    items[1] = NULL;
    items[2] = NULL;
  }

  SudokuTripple(SudokuItem *item0, SudokuItem *item1, SudokuItem *item2)
  {
    items[0] = item0;
    items[1] = item1;
    items[2] = item2;
  }

  SudokuTripple(const SudokuTripple &rhs)
  {
    items[0] = rhs.items[0];
    items[1] = rhs.items[1];
    items[2] = rhs.items[2];
  }

  SudokuItem *getItem(unsigned char index) const
  {
    if(index >= 3)
      return NULL;
    return items[index];
  }

  bool setValue(unsigned char index, unsigned char value)
  {
    if(index >= 3)
      return false;
    return items[index]->setValue(value);
  }

  void addListener(SudokuItemListener* listener)
  {
    items[0]->addListener(listener);
    items[1]->addListener(listener);
    items[2]->addListener(listener);    
  }

  bool disableValue(unsigned char impossibleValue)
  {
    return items[0]->disableValue(impossibleValue) |
           items[1]->disableValue(impossibleValue) |
           items[2]->disableValue(impossibleValue);  
  }

  void print() const
  {
    if(items[0]) items[0]->print(); else std::cout << "x";
    std::cout << " ";
    if(items[1]) items[1]->print(); else std::cout << "x";
    std::cout << " ";
    if(items[2]) items[2]->print(); else std::cout << "x";    
  }

};