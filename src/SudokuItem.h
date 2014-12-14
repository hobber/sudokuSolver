//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
//WW                  WWW           WWW WWW           WWW                    WW
//WW                   WWW   WWW   WWW   WWW   WWW   WWW                     WW
//WW                    WWW WW WW WWW     WWW WW WW WWW                      WW
//WW                     WWWW   WWWW       WWWW   WWWW                       WW
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW


#pragma once

#include <iomanip>
#include <vector>

#include "SudokuItemListener.h"

class SudokuItem
{
  unsigned char ID;
  bool possibilites[9];
  unsigned char value;
  std::vector<SudokuItemListener*> listeners;
  
public:

  SudokuItem() : value(0)
  {
    for(unsigned char i=0; i<9; i++)
      possibilites[i] = true;    
  }

  void setID(unsigned char ID)
  {
    this->ID = ID;
  }

  bool testValue(unsigned char value) const
  {
    return value > 0 && value <= 9 && possibilites[value-1];
  }

  void addListener(SudokuItemListener* listener)
  {
    listeners.push_back(listener);
  }

  bool setSingleChoice()
  {
    if(isFixed())
      return false;

    unsigned char possibilyCounter = 0;
    for(unsigned char i=0; i<9; i++)
      if(possibilites[i])
        possibilyCounter++;

    if(possibilyCounter != 1)
      return false;

    for(unsigned char i=0; i<9; i++)
      if(possibilites[i]) {
        setValue(i+1);
        std::cout << " (last choice of item)" << std::endl;
        return true;
      }
  }  

  bool setValue(unsigned char value)
  {    
    if(testValue(value) == false)
      return false;

    if(this->value == value)
      return true;

    std::cout << "set item " << std::setw(2) << (int)ID << " (" << (int)(ID%9+1) << "," << (int)(ID/9+1) << ") on " << (int)value;
    
    for(int i=0; i<9; i++)
      if(i != value-1)
        possibilites[i] = false;
    this->value = value;

    for(unsigned int i=0; i<listeners.size(); i++)
      listeners[i]->notify(value);
    
    return true;
  }

  bool disableValue(unsigned char value)
  {
    if(this->value == value)
      return false;
    bool previousState = possibilites[value-1];
    possibilites[value-1] = false;
    return previousState;
  }

  unsigned char getValue() const
  {
    return value;
  }

  bool isFixed() const
  {
    return value > 0;
  }

  std::vector<unsigned char> getPossibilites() const
  {
    std::vector<unsigned char> list;
    for(unsigned char i=0; i<9; i++)
      if(possibilites[i])
        list.push_back(i+1);
    return list;
  }

  void print() const
  {
    if(isFixed())
      std::cout << (int)value;
    else
      std::cout << "_";
  }
};