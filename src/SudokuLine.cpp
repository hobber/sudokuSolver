
#include "SudokuLine.h"

SudokuLine::SudokuLine()
{

}

void SudokuLine::initialize(const SudokuTripple &tripple0, const SudokuTripple &tripple1, const SudokuTripple &tripple2)
{
  tripples[0] = tripple0;
  tripples[1] = tripple1;
  tripples[2] = tripple2;

  tripples[0].addListener(this);
  tripples[1].addListener(this);
  tripples[2].addListener(this);
}

void SudokuLine::setID(unsigned char ID)
{
  tripples[0].getItem(0)->setID(ID*9);
  tripples[0].getItem(1)->setID(ID*9+1);
  tripples[0].getItem(2)->setID(ID*9+2);
  tripples[1].getItem(0)->setID(ID*9+3);
  tripples[1].getItem(1)->setID(ID*9+4);
  tripples[1].getItem(2)->setID(ID*9+5);
  tripples[2].getItem(0)->setID(ID*9+6);
  tripples[2].getItem(1)->setID(ID*9+7);
  tripples[2].getItem(2)->setID(ID*9+8);
}

bool SudokuLine::containsValue(unsigned char value) const
{
  for(unsigned char i=0; i<9; i++)
    if(getItem(i)->isFixed() && getItem(i)->getValue() == value)
      return true;
  return false;
}

bool SudokuLine::setValue(unsigned char index, unsigned char value)
{
  if(index >= 9)
    return false;
  return getItem(index)->setValue(value);
}

bool SudokuLine::setLastItem()
{
  unsigned char fixedItemCounter = 0;    
  for(unsigned char i=0; i<9; i++)
    if(getItem(i)->isFixed())
      fixedItemCounter++;

  if(fixedItemCounter != 8)
    return false;

  bool containsValue[9];
  unsigned char unsetItemIndex = -1;
  for(unsigned char i=0; i<9; i++)
    containsValue[i] = false;
  for(unsigned char i=0; i<9; i++)
    if(getItem(i)->isFixed())     
      containsValue[getItem(i)->getValue()-1] = true;
    else
      unsetItemIndex = i;

  for(unsigned char i=0; i<9; i++)
    if(containsValue[i] == false) 
    {
      getItem(unsetItemIndex)->setValue(i+1);
      std::cout << " (last item in a line)" << std::endl;
      return true;
    }

  return false;
}

bool SudokuLine::disableValueInATripple(unsigned char value, unsigned char trippleIndex)
{
  if(trippleIndex > 2)
    return false;
  return tripples[trippleIndex].disableValue(value);
}

bool SudokuLine::setLastChance()
{
  bool found = false;
  for(unsigned char value = 1; value<=9; value++)
  {
    unsigned char counter = 0;
    unsigned char index = 0;
    for(unsigned char i=0; i<9; i++)
    {
      if(getItem(i)->isFixed())
        continue;

      if(getItem(i)->testValue(value)) 
      {
        counter++;
        index = i;
      }

      if(counter >= 2)
        break;
    }

    if(counter != 1)
      continue;

    getItem(index)->setValue(value);
    std::cout << " (last chance in a line)" << std::endl;
    found = true;
  }
  return found;
}

void SudokuLine::notify(unsigned char impossibleValue)
{
  tripples[0].disableValue(impossibleValue);
  tripples[1].disableValue(impossibleValue);
  tripples[2].disableValue(impossibleValue);
}

SudokuItem *SudokuLine::getItem(unsigned char index) const
{
  return tripples[index/3].getItem(index % 3);
}

void SudokuLine::print() const
{
  tripples[0].print();
  std::cout << "   ";
  tripples[1].print();
  std::cout << "   ";
  tripples[2].print();    
}
