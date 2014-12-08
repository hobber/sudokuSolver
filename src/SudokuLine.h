//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
//WW                  WWW           WWW WWW           WWW                    WW
//WW                   WWW   WWW   WWW   WWW   WWW   WWW                     WW
//WW                    WWW WW WW WWW     WWW WW WW WWW                      WW
//WW                     WWWW   WWWW       WWWW   WWWW                       WW
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW


#pragma once

#include "SudokuTripple.h"

class SudokuLine {

  SudokuTripple tripples[3];

public:
  SudokuLine()
  {

  }

  void initialize(const SudokuTripple &tripple0, const SudokuTripple &tripple1, const SudokuTripple &tripple2)
  {
    tripples[0] = tripple0;
    tripples[1] = tripple1;
    tripples[2] = tripple2;
  }

  void print() const
  {
    tripples[0].print();
    std::cout << " ";
    tripples[1].print();
    std::cout << " ";
    tripples[2].print();    
  }

};
