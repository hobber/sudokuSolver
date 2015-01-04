//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
//WW                  WWW           WWW WWW           WWW                    WW
//WW                   WWW   WWW   WWW   WWW   WWW   WWW                     WW
//WW                    WWW WW WW WWW     WWW WW WW WWW                      WW
//WW                     WWWW   WWWW       WWWW   WWWW                       WW
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW


#pragma once

#include "SudokuItemListener.h"

class SudokuItemGroup : public SudokuItemListener {

public:

  virtual ~SudokuItemGroup() {}

  bool containsValue(unsigned char value) const
  {
    for(unsigned char i=0; i<9; i++)
      if(getConstItem(i)->isFixed() && getConstItem(i)->getValue() == value)
        return true;
    return false;
  }

  virtual bool setValue(unsigned char index, unsigned char value)
  {  
    if(index >= 9)
      return false;
    return getItem(index)->setValue(value);
  }

  virtual bool setLastChance() = 0;

  bool checkForPair()
  {
    bool hasFoundAPair = false;
    //test all pairs of items
    for(unsigned char i=0; i<9; i++) 
    {
      if(getItem(i)->countPossibilities() != 2)
        continue;
  
      for(unsigned char j=i+1; j<9; j++) 
      {
        if(getItem(j)->countPossibilities() != 2)
          continue;
    
        //test all pairs of values
        for(unsigned char a=0; a<9; a++) 
        {
          if(getItem(i)->testValue(a) == false || getItem(j)->testValue(a) == false)
            continue;
  
          for(unsigned char b=a+1; b<9; b++) 
          {
            if(getItem(i)->testValue(b) == false || getItem(j)->testValue(b) == false)
              continue;

            //found a pair -> remove from other items
            bool found = false;
            for(unsigned char l=0; l<9; l++)
            {
              if(l == i || l == j)
                continue;
              found |= getItem(l)->disableValue(a);
              found |= getItem(l)->disableValue(b);
            }
            hasFoundAPair |= found;
            if(found) 
              std::cout << "found a pair @ " << (int)getItem(i)->getID() << " and "
                        << (int)getItem(j)->getID() << ": " << (int)a << ", " << (int)b << std::endl;
          }
        }
      }
    }
    return hasFoundAPair;
  }

  virtual void notify(unsigned char impossibleValue) = 0;

  virtual SudokuItem *getItem(unsigned char index) = 0;

  virtual const SudokuItem *getConstItem(unsigned char index) const = 0;

  virtual void print() const = 0;

};
