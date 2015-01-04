
#include "SudokuItem.h"

SudokuItem::SudokuItem()
{
  state = new SudokuItemState(this);
  for(unsigned char i=0; i<9; i++)
    state->possibilites[i] = true;    
}

SudokuItem::~SudokuItem()
{
  delete state;
}

void SudokuItem::setID(unsigned char ID)
{
  state->ID = ID;
}

unsigned char SudokuItem::getID() const
{
  return state->ID;
}

void SudokuItem::setHistory(SudokuHistory *history)
{
  this->history = history;
}

bool SudokuItem::testValue(unsigned char value) const
{
  return value > 0 && value <= 9 && state->possibilites[value-1];
}

void SudokuItem::addListener(SudokuItemListener* listener)
{
  listeners.push_back(listener);
}

unsigned char SudokuItem::countPossibilities() const
{
  if(isFixed())
    return 0;

  unsigned char possibilyCounter = 0;
  for(unsigned char i=0; i<9; i++)
    if(state->possibilites[i])
      possibilyCounter++;

  return possibilyCounter;
}

bool SudokuItem::setSingleChoice()
{
  if(countPossibilities() != 1)
    return false;

  for(unsigned char i=0; i<9; i++)
    if(state->possibilites[i]) {
      setValue(i+1);
      std::cout << " (last choice of item)" << std::endl;
      return true;
    }
}  

bool SudokuItem::setValue(unsigned char value)
{    
  if(testValue(value) == false)
    return false;

  if(state->value == value)
    return true;

  std::cout << "set item " << std::setw(2) << (int)state->ID << " (" << (int)(state->ID%9+1);
  std::cout << "," << (int)(state->ID/9+1) << ") on " << (int)value;
    
  history->add(*state);

  for(int i=0; i<9; i++)
    if(i != value-1)
      state->possibilites[i] = false;
  state->value = value;

  for(unsigned int i=0; i<listeners.size(); i++)
    listeners[i]->notify(value);
    
  return true;
}

bool SudokuItem::disableValue(unsigned char value)
{
  if(state->value == value)
    return false;
  if(state->possibilites[value-1] == false)
    return false;

  history->add(*state);

  state->possibilites[value-1] = false;
  return true;
}

unsigned char SudokuItem::getValue() const
{
  return state->value;
}

bool SudokuItem::isFixed() const
{
  return state->value > 0;
}

std::vector<unsigned char> SudokuItem::getPossibilites() const
{
  std::vector<unsigned char> list;
  for(unsigned char i=0; i<9; i++)
    if(state->possibilites[i])
      list.push_back(i+1);
  return list;
}

void SudokuItem::setState(const SudokuItemState &state)
{
  delete this->state;
  this->state = new SudokuItemState(state);
  this->state->item = this;
}

const SudokuItemState &SudokuItem::getState() const
{
  return *state;
}

void SudokuItem::print() const
{
  if(isFixed())
    std::cout << (int)state->value;
  else
    std::cout << "_";
}
