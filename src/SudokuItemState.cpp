
#include "SudokuItemState.h"

SudokuItemState::SudokuItemState(SudokuItem *item) : value(0), item(item) {}

SudokuItemState::SudokuItemState(const SudokuItemState &src)
{
  set(src);
}

void SudokuItemState::set(const SudokuItemState &src)
{
  ID = src.ID;
  value = src.value;
  item = src.item;
  for(unsigned char i=0; i<9; i++)
    possibilites[i] = src.possibilites[i];
}

void SudokuItemState::print() const
{
  std::cout << (int)ID << ": ";
  for(unsigned char i=0; i<9; i++)
    if(possibilites[i])
      std::cout << (int)(i+1);
    else
      std::cout << "_";
}
