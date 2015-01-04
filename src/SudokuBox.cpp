
#include "SudokuBox.h"

SudokuBox::SudokuBox()
{
  for(unsigned char i=0; i<9; i++)
    items[i].addListener(this);
}

void SudokuBox::setHistory(SudokuHistory *history)
{
  for(unsigned char i=0; i<9; i++)
    items[i].setHistory(history);
}

SudokuTripple SudokuBox::getColumnTripple(unsigned char index)
{
  if(index > 2)
    throw new std::out_of_range("index out of range!");
  return SudokuTripple(&items[index], &items[index+3], &items[index+6]);
}

SudokuTripple SudokuBox::getRowTripple(unsigned char index)
{
  if(index > 2)
    throw new std::out_of_range("index out of range!");
  return SudokuTripple(&items[3*index], &items[3*index+1], &items[3*index+2]); 
}

unsigned int SudokuBox::countFixedValues() const
{
  unsigned int count = 0;
  for(unsigned char i=0; i<9; i++)
    if(items[i].isFixed())
     count++;
  return count; 
}

bool SudokuBox::setLastItem()
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

bool SudokuBox::setLastChance()
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

bool SudokuBox::setSingleChoice()
{
  bool hasSetASingleChoice = false;
  for(unsigned char i=0; i<9; i++)
    if(items[i].setSingleChoice())
      hasSetASingleChoice = true;
  return hasSetASingleChoice;
}

bool SudokuBox::isComplete() const
{
  for(unsigned char i=0; i<9; i++)
    if(items[i].isFixed() == false)
      return false;
  return true;
}

bool SudokuBox::lineMustContainValue(unsigned char value, unsigned char lineIndex, bool horizontal) const
{
  if(horizontal)
  {
    bool canContainValue = false;
    for(unsigned char i=0; i<3 && canContainValue == false; i++)
      if(items[lineIndex*3 + i].testValue(value))
        canContainValue = true;

    if(canContainValue == false)
      return false;

    lineIndex = (lineIndex + 1) % 3;      
    for(unsigned char i=0; i<3; i++)
      if(items[lineIndex*3 + i].testValue(value))
        return false;

    lineIndex = (lineIndex + 1) % 3;      
    for(unsigned char i=0; i<3; i++)
      if(items[lineIndex*3 + i].testValue(value))
        return false;
  }
  else
  {
    bool canContainValue = false;
    for(unsigned char i=0; i<3 && canContainValue == false; i++)
      if(items[i*3 + lineIndex].testValue(value))
        canContainValue = true;

    if(canContainValue == false)
      return false;

    lineIndex = (lineIndex + 1) % 3;      
    for(unsigned char i=0; i<3; i++)
      if(items[i*3 + lineIndex].testValue(value))
        return false;

    lineIndex = (lineIndex + 1) % 3;      
    for(unsigned char i=0; i<3; i++)
      if(items[i*3 + lineIndex].testValue(value))
        return false;
  }
  return true;
}

void SudokuBox::notify(unsigned char impossibleValue)
{
  for(unsigned char i=0; i<9; i++)
    items[i].disableValue(impossibleValue);
}

SudokuItem *SudokuBox::getItem(unsigned char index)
{
  return &items[index];
}

const SudokuItem *SudokuBox::getConstItem(unsigned char index) const
{
  return &items[index];
}

void SudokuBox::print() const
{
  for(unsigned char i=0; i<9; i++)
  {
    items[i].print();
    std::cout << " ";
  }
}
