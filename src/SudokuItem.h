//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
//WW                  WWW           WWW WWW           WWW                    WW
//WW                   WWW   WWW   WWW   WWW   WWW   WWW                     WW
//WW                    WWW WW WW WWW     WWW WW WW WWW                      WW
//WW                     WWWW   WWWW       WWWW   WWWW                       WW
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW


#pragma once

class SudokuItem
{
  bool possibilites[9];
  unsigned char value;
  
public:

  SudokuItem()
  {
    for(int i=0; i<9; i++)
      possibilites[i] = true;
    value = 0;
  }

  bool test(unsigned char value) const
  {
    return value > 0 && value <= 9 && possibilites[value-1];
  }

  bool set(unsigned char value)
  {
    if(test(value) == false)
      return false;
    for(int i=0; i<9; i++)
      if(i != value-1)
        possibilites[i] = false;
    this->value = value;
    return true;
  }

  unsigned char get() const
  {
    return value;
  }

  bool fixed() const
  {
    return value > 0;
  }

  void print() const
  {
    if(fixed())
      std::cout << (int) value;
    else
      std::cout << "_";
  }
};