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

class SudokuBox {

  SudokuItem items[9];

public:

  SudokuBox()
  {
    
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

  void print()
  {
    for(unsigned char i=0; i< 9; i++)
    {
      items[i].print();
      std::cout << " ";
    }
  }
};