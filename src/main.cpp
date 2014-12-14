
#include "SudokuField.h"

void createField01(SudokuField &field)
{
  field.setValue(0,0,9);
  field.setValue(2,0,6);
  field.setValue(3,0,8);
  field.setValue(4,0,1);
  field.setValue(5,0,3);
  field.setValue(6,0,5);
  field.setValue(7,0,4);

  field.setValue(0,1,2);
  field.setValue(2,1,1);
  field.setValue(4,1,4);
  field.setValue(5,1,5);
  field.setValue(7,1,6);
  field.setValue(8,1,3);

  field.setValue(1,2,4);

  field.setValue(3,3,6);
  field.setValue(4,3,2);
  field.setValue(8,3,9);

  field.setValue(2,4,9);
  field.setValue(6,4,2);

  field.setValue(0,5,7);
  field.setValue(4,5,3);
  field.setValue(5,5,4);

  field.setValue(7,6,9);

  field.setValue(0,7,5);
  field.setValue(1,7,9);
  field.setValue(3,7,3);
  field.setValue(4,7,6);
  field.setValue(6,7,1);
  field.setValue(8,7,4);

  field.setValue(1,8,2);
  field.setValue(2,8,7);
  field.setValue(3,8,4);
  field.setValue(4,8,5);
  field.setValue(5,8,9);
  field.setValue(6,8,3);
  field.setValue(8,8,6);
}

void createField02(SudokuField &field)
{
  field.setValue(1,0,1);
  field.setValue(2,0,5);
  field.setValue(6,0,9);
  field.setValue(7,0,8);

  field.setValue(3,1,2);
  field.setValue(5,1,8);

  field.setValue(0,2,8);
  field.setValue(1,2,4);
  field.setValue(7,2,3);
  field.setValue(8,2,5);

  field.setValue(2,3,1);
  field.setValue(3,3,4);
  field.setValue(5,3,5);
  field.setValue(6,3,8);

  field.setValue(1,4,2);
  field.setValue(3,4,7);
  field.setValue(5,4,9);
  field.setValue(7,4,6);

  field.setValue(2,5,3);
  field.setValue(3,5,8);
  field.setValue(5,5,1);
  field.setValue(6,5,2);

  field.setValue(0,6,2);
  field.setValue(1,6,5);
  field.setValue(7,6,7);
  field.setValue(8,6,4);

  field.setValue(3,7,6);
  field.setValue(5,7,2);

  field.setValue(1,8,3);
  field.setValue(2,8,7);
  field.setValue(6,8,6);
  field.setValue(7,8,2);
}

int main( int argc, const char* argv[] )
{
  SudokuField field;
  createField01(field);

  std::cout << std::endl << "start solving..." << std::endl;
  if(field.solve())
    std::cout << std::endl << "Sudoku solved :)" << std::endl << std::endl;
  else
    std::cout << std::endl << "Sudoku incomplete :(" << std::endl << std::endl;
/**/  
  field.print();
  return 0;	
} 