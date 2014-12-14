
#include <vector>

#include "SudokuField.h"

int main( int argc, const char* argv[] )
{
  SudokuField field;
  std::cout << "enter game (enter 9 characters for each line):" << std::endl;  
  field.readFromInput();

  std::cout << std::endl << "start solving..." << std::endl;
  if(field.solve())
    std::cout << std::endl << "Sudoku solved :)" << std::endl << std::endl;
  else {
    std::cout << std::endl << "Sudoku incomplete :(" << std::endl << std::endl;
    
    while(true)
    {
      field.print();
      std::cout << "enter Id of a field: ";
      int ID;
      std::cin >> ID;
      std::cout << std::endl << "possibilities for field " << ID;
      std::vector<unsigned char> possibilities = field.getPossibilites(ID);
      for(unsigned char i=0; i<possibilities.size(); i++)
        std::cout << (int)possibilities[i] << " ";
      std::cout << std::endl;
    }
  }
/**/  
  field.print();
  return 0;	
} 