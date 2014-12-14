//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
//WW                  WWW           WWW WWW           WWW                    WW
//WW                   WWW   WWW   WWW   WWW   WWW   WWW                     WW
//WW                    WWW WW WW WWW     WWW WW WW WWW                      WW
//WW                     WWWW   WWWW       WWWW   WWWW                       WW
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW


#pragma once

#include <iostream>
#include <stdexcept> 

#include "SudokuItem.h"
#include "SudokuTripple.h"

class SudokuBox : public SudokuItemListener {

  SudokuItem items[9];

public:

  SudokuBox()
  {
    for(unsigned char i=0; i<9; i++)
      items[i].addListener(this);
  }

  SudokuTripple getColumnTripple(unsigned char index)
  {
  	if(index > 2)
  	  throw new std::out_of_range("index out of range!");
    return SudokuTripple(&items[index], &items[index+3], &items[index+6]);
  }

  SudokuTripple getRowTripple(unsigned char index)
  {
    if(index > 2)
      throw new std::out_of_range("index out of range!");
    return SudokuTripple(&items[3*index], &items[3*index+1], &items[3*index+2]); 
  }

  bool setLastItem()
  {
    unsigned char fixedItemCounter = 0;    
    for(unsigned char i=0; i<9; i++)
      if(items[i].isFixed())
        fixedItemCounter++;

    if(fixedItemCounter != 8)
      return false;

    bool containsValue[9];
    unsigned char unsetItemIndex = -1;
    for(unsigned char i=0; i<9; i++)
      containsValue[i] = false;
    for(unsigned char i=0; i<9; i++)
      if(items[i].isFixed())     
        containsValue[items[i].getValue()-1] = true;
      else
        unsetItemIndex = i;

    for(unsigned char i=0; i<9; i++)
      if(containsValue[i] == false) 
      {
        items[unsetItemIndex].setValue(i+1);
        std::cout << " (last item in a box)" << std::endl;
        return true;
      }

    return false;
  }

  bool setLastChance()
  {
    bool found = false;
    for(unsigned char value = 1; value<=9; value++)
    {
      unsigned char counter = 0;
      unsigned char index = 0;
      for(unsigned char i=0; i<9; i++)
      {
        if(items[i].isFixed())
          continue;

        if(items[i].testValue(value)) 
        {
          counter++;
          index = i;
        }

        if(counter >= 2)
          break;
      }

      if(counter != 1)
        continue;

      items[index].setValue(value);
      std::cout << " (last chance in a box)" << std::endl;
      found = true;
    }
    return found;
  }

  bool setSingleChoice()
  {
    bool hasSetASingleChoice = false;
    for(unsigned char i=0; i<9; i++)
      if(items[i].setSingleChoice())
        hasSetASingleChoice = true;
    return hasSetASingleChoice;
  }

  bool isComplete() const
  {
    for(unsigned char i=0; i<9; i++)
      if(items[i].isFixed() == false)
        return false;
    return true;
  }

  void notify(unsigned char impossibleValue)
  {
    for(unsigned char i=0; i<9; i++)
      items[i].disableValue(impossibleValue);
  }

  void print()
  {
    for(unsigned char i=0; i<9; i++)
    {
      items[i].print();
      std::cout << " ";
    }
  }
};