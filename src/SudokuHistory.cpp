
#include "SudokuHistory.h"

SudokuHistory::SudokuHistory()
{
  index = -1;
}

void SudokuHistory::add(const SudokuItemState &state)
{
  while(index != history.size()-1)
    history.pop_back();
  
  history.push_back(state);
  index++;
}

void SudokuHistory::undo(unsigned int steps)
{  
  for(unsigned int i=0; i<steps; i++)
  {          
    if(index < 0)
      break;
    SudokuItemState state = history.at(index);    
    history.at(index) = state.item->getState();
    state.item->setState(state);
    index--;
    std::cout << "undo - new index: " << index << ", size: " << history.size();
    std::cout << " (" << state << ")" << std::endl;
  }
}

void SudokuHistory::redo(unsigned int steps)
{  
  for(unsigned int i=0; i<steps; i++)
  {    
    if(index == history.size() - 1)
      break;  
    index++;  
    SudokuItemState state = history.at(index);
    history.at(index) = state.item->getState();
    state.item->setState(state);
    std::cout << "redo - new index: " << index << ", size: " << history.size();
    std::cout << " (" << state << ")" << std::endl;
  }
}
