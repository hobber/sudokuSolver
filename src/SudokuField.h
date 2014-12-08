//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
//WW                  WWW           WWW WWW           WWW                    WW
//WW                   WWW   WWW   WWW   WWW   WWW   WWW                     WW
//WW                    WWW WW WW WWW     WWW WW WW WWW                      WW
//WW                     WWWW   WWWW       WWWW   WWWW                       WW
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW


#pragma once

#include <iomanip>
#include <iostream>

#include "SudokuBox.h"
#include "SudokuLine.h"

class SudokuField {

  SudokuBox boxes[9];
  SudokuLine columns[9];
  SudokuLine rows[9];

public:

  SudokuField()
  {    
    columns[0].initialize(boxes[0].getColumnTripple(0), boxes[3].getColumnTripple(0), boxes[6].getColumnTripple(0));
    columns[1].initialize(boxes[0].getColumnTripple(1), boxes[3].getColumnTripple(1), boxes[6].getColumnTripple(1));
    columns[2].initialize(boxes[0].getColumnTripple(2), boxes[3].getColumnTripple(2), boxes[6].getColumnTripple(2));
    columns[3].initialize(boxes[1].getColumnTripple(0), boxes[4].getColumnTripple(0), boxes[7].getColumnTripple(0));
    columns[4].initialize(boxes[1].getColumnTripple(1), boxes[4].getColumnTripple(1), boxes[7].getColumnTripple(1));
    columns[5].initialize(boxes[1].getColumnTripple(2), boxes[4].getColumnTripple(2), boxes[7].getColumnTripple(2));
    columns[6].initialize(boxes[2].getColumnTripple(0), boxes[5].getColumnTripple(0), boxes[8].getColumnTripple(0));
    columns[7].initialize(boxes[2].getColumnTripple(1), boxes[5].getColumnTripple(1), boxes[8].getColumnTripple(1));
    columns[8].initialize(boxes[2].getColumnTripple(2), boxes[5].getColumnTripple(2), boxes[8].getColumnTripple(2));

    rows[0].initialize(boxes[0].getRowTripple(0), boxes[1].getRowTripple(0), boxes[2].getRowTripple(0));
    rows[1].initialize(boxes[0].getRowTripple(1), boxes[1].getRowTripple(1), boxes[2].getRowTripple(1));
    rows[2].initialize(boxes[0].getRowTripple(2), boxes[1].getRowTripple(2), boxes[2].getRowTripple(2));
    rows[3].initialize(boxes[3].getRowTripple(0), boxes[4].getRowTripple(0), boxes[5].getRowTripple(0));
    rows[4].initialize(boxes[3].getRowTripple(1), boxes[4].getRowTripple(1), boxes[5].getRowTripple(1));
    rows[5].initialize(boxes[3].getRowTripple(2), boxes[4].getRowTripple(2), boxes[5].getRowTripple(2));
    rows[6].initialize(boxes[6].getRowTripple(0), boxes[6].getRowTripple(0), boxes[8].getRowTripple(0));
    rows[7].initialize(boxes[6].getRowTripple(1), boxes[6].getRowTripple(1), boxes[8].getRowTripple(1));
    rows[8].initialize(boxes[6].getRowTripple(2), boxes[6].getRowTripple(2), boxes[8].getRowTripple(2));    
  }

  void print()
  {
    for(int i=0; i<9; i++) 
    {      
      rows[i].print();
      std::cout << std::endl;
    }
  }
};