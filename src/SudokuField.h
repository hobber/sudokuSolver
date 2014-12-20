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
    rows[6].initialize(boxes[6].getRowTripple(0), boxes[7].getRowTripple(0), boxes[8].getRowTripple(0));
    rows[7].initialize(boxes[6].getRowTripple(1), boxes[7].getRowTripple(1), boxes[8].getRowTripple(1));
    rows[8].initialize(boxes[6].getRowTripple(2), boxes[7].getRowTripple(2), boxes[8].getRowTripple(2));  

    rows[0].setID(0); 
    rows[1].setID(1);
    rows[2].setID(2);
    rows[3].setID(3);
    rows[4].setID(4);
    rows[5].setID(5);
    rows[6].setID(6);
    rows[7].setID(7);
    rows[8].setID(8);
  }

  bool setValue(unsigned char column, unsigned char row, unsigned char value)  
  {
    bool result = columns[column].setValue(row, value);
    std::cout << std::endl;
    return result;
  }

  bool isSolved() const
  {
    for(unsigned char i=0; i<9; i++)
      if(boxes[i].isComplete() == false)
        return false;
    return true;
  }

  bool solve()
  {   
    bool found = false;     
    do
    {
      found = false;
      for(unsigned char i=0; i<9; i++)
      {
        if(boxes[i].setLastItem())
          found = true;
        
        if(boxes[i].setLastChance())
          found = true;

        if(boxes[i].setSingleChoice())             
          found = true;

        if(rows[i].setLastItem())
          found = true;
        
        if(rows[i].setLastChance())
          found = true;

        if(columns[i].setLastItem())
          found = true;
        
        if(columns[i].setLastChance())
          found = true;        
      }      

      if(found == false && filterValues())
        found = true;

    } while(found);

    return isSolved();
  }

  /**
  * test for each tripple in a box if it is the last 
  * one which can contain a value. If so, then this
  * value can be delete from other lines possibilities.
  */
  bool filterValues() 
  {    
    bool found = false;
    for(unsigned char i=0; i<9; i++)
    {
      for(unsigned char v=0; v<9; v++)
      {
        if(boxes[i].containsValue(v))
          continue;

        for(unsigned char l=0; l<3; l++) {
          if(boxes[i].lineMustContainValue(v, l, false))
          {
            unsigned char columnID = (i % 3) * 3 + l;             
            unsigned char trippleID1 = ((i / 3) + 1) % 3;
            unsigned char trippleID2 = ((i / 3) + 2) % 3;

            if((columns[columnID].disableValueInATripple(v, trippleID1) |
                columns[columnID].disableValueInATripple(v, trippleID2)) == false)            
              continue;

            found = true;
            std::cout << "filter " << (int)v << " in column " << (int) columnID << " in boxes ";
            std::cout << (int)trippleID1 << ", " << (int)trippleID2 << std::endl;

          }
          if(boxes[i].lineMustContainValue(v, l, true))
          {
            unsigned char rowID = (i / 3) * 3 + l;
            unsigned char trippleID1 = ((i % 3) + 1) % 3;
            unsigned char trippleID2 = ((i % 3) + 2) % 3;
            
            if((rows[rowID].disableValueInATripple(v, trippleID1) |
                rows[rowID].disableValueInATripple(v, trippleID2)) == false)            
              continue;

            found = true;
            std::cout << "filter " << (int)v << " in row " << (int) rowID << " in boxes ";
            std::cout << (int)trippleID1 << ", " << (int)trippleID2 << std::endl;
          } 
        }      
      }      
    }
    return found;
  }

  std::vector<unsigned char> getPossibilites(unsigned char ID) const
  {
     return rows[ID/9].getItem(ID % 9)->getPossibilites();
  }

  void readFromInput()
  {
    for(unsigned char i=0; i<9; i++)
    {
      std::string line;
      std::cin >> line;      
      if(line.length() != 9)
      {
        std::cout << "enter 9 characters for each line!" << std::endl;
        i--;
      }
      else
      {
        for(unsigned char j=0; j<9; j++)
        {
          if(isdigit(line[j]))
            setValue(j, i, line[j] - '0');
        }
      }
    }    
  }

  void print()
  {
    for(int i=0; i<9; i++) 
    {      
      rows[i].print();
      std::cout << std::endl;
      if(i % 3 == 2)
        std::cout << std::endl;
    }
  }
};
