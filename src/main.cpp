
#include <vector>

#include "SudokuField.h"

int main( int argc, const char* argv[] )
{
  SudokuField field;
  std::cout << "enter game (enter 9 characters for each line):" << std::endl;  
  field.readFromInput();

  std::cout << std::endl << "start solving..." << std::endl;
  if(field.solve()) {
    std::cout << std::endl << "Sudoku solved :)   ";
    field.printDifficultyLevel();
    std::cout << std::endl << std::endl;
  }
  else {
    std::cout << std::endl << "Sudoku incomplete :(" << std::endl << std::endl;
  }
  
  field.print();
/*
  field.undo(5);
  field.redo(4);
  field.undo(5);
  field.redo(6);
  field.print();
*/  
  return 0;	
} 
