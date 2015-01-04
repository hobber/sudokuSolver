
#include "SudokuField.h"

SudokuField::SudokuField()
{ 
  level = VERY_EASY;

  boxes[0].setHistory(&history);
  boxes[1].setHistory(&history);
  boxes[2].setHistory(&history);
  boxes[3].setHistory(&history);
  boxes[4].setHistory(&history);
  boxes[5].setHistory(&history);
  boxes[6].setHistory(&history);
  boxes[7].setHistory(&history);
  boxes[8].setHistory(&history);

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

unsigned int SudokuField::countFixedValues() const
{
  unsigned int count = 0;
  for(unsigned char i=0; i<9; i++)
    count += boxes[i].countFixedValues();
  return count;
}

bool SudokuField::setValue(unsigned char column, unsigned char row, unsigned char value)  
{
  bool result = columns[column].setValue(row, value);
  std::cout << std::endl;
  return result;
}

bool SudokuField::isSolved() const
{
  for(unsigned char i=0; i<9; i++)
    if(boxes[i].isComplete() == false)
      return false;
  return true;
}

bool SudokuField::solve()
{  
  if(isSolved())
    return true;

  int count = countFixedValues(); 
  if(count >= 35)
    level = VERY_EASY;
  else if(count >= 30)
    level = EASY;
  else if(count >= 24)
    level = DEFAULT;
  else
    level = MODERATE;

  while(true)
  {
    if(isSolved())
      return true;

    //very easy + easy
    if(scanValues())
      continue;

    //default
    level = DEFAULT;
    if(excludeAlternatives())
      continue;
    
    //moderate
    level = MODERATE;
    if(checkForPair())
      continue;

    break;
  }

  return false;
}

SudokuField::DifficultyLevel SudokuField::getDifficultyLevel() const
{
  return level;
}

void SudokuField::printDifficultyLevel() const
{
  switch(level)
  {
    case VERY_EASY:       std::cout << "VERY EASY";       break;
    case EASY:            std::cout << "EASY";            break;
    case DEFAULT:         std::cout << "DEFAULT";         break;
    case MODERATE:        std::cout << "MODERATE";        break;
    case DEMANDING:       std::cout << "DEMANDING";       break;
    case VERY_DEMANDING:  std::cout << "VERY DEMANDING";  break;
    case DEVILISHLY:      std::cout << "DEVILISHLY";      break;
    case VERY_DEVILISHLY: std::cout << "VERY DEVILISHLY"; break;
    default:              std::cout << "UNKNOWN";         break;
  }
}

bool SudokuField::scanValues()
{
  bool found = false;
  for(unsigned char i=0; i<9; i++) 
  {
    found |= boxes[i].setLastChance();
    found |= rows[i].setLastChance();
    found |= columns[i].setLastChance();
  }
  return found;
}

bool SudokuField::excludeAlternatives()
{
  bool found = false;
  for(unsigned char i=0; i<9; i++) {
    found |= boxes[i].setSingleChoice();
  }
  return found;
}

bool SudokuField::checkForPair()
{
  bool found = false;
  for(unsigned char i=0; i<9; i++) {
    found |= boxes[i].checkForPair();
    found |= rows[i].checkForPair();
    found |= columns[i].checkForPair();
  }
  return found;
}

bool SudokuField::filterValues() 
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

std::vector<unsigned char> SudokuField::getPossibilites(unsigned char ID) const
{
   return rows[ID/9].getConstItem(ID % 9)->getPossibilites();
}

void SudokuField::readFromInput()
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

void SudokuField::undo(unsigned int steps)
{
  history.undo(steps);
}

void SudokuField::redo(unsigned int steps)
{
  history.redo(steps);
}

void SudokuField::print()
{
  for(int i=0; i<9; i++) 
  {      
    rows[i].print();
    std::cout << std::endl;
    if(i % 3 == 2)
      std::cout << std::endl;
  }
}
