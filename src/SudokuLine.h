//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
//WW                  WWW           WWW WWW           WWW                    WW
//WW                   WWW   WWW   WWW   WWW   WWW   WWW                     WW
//WW                    WWW WW WW WWW     WWW WW WW WWW                      WW
//WW                     WWWW   WWWW       WWWW   WWWW                       WW
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW


#pragma once

#include "SudokuItem.h"
#include "SudokuItemListener.h"
#include "SudokuTripple.h"

class SudokuLine : public SudokuItemListener {

  SudokuTripple tripples[3];

public:
  SudokuLine();

  void initialize(const SudokuTripple &tripple0, const SudokuTripple &tripple1, const SudokuTripple &tripple2);

  void setID(unsigned char ID);

  bool containsValue(unsigned char value) const;

  bool setValue(unsigned char index, unsigned char value);

  bool setLastItem();

  bool disableValueInATripple(unsigned char value, unsigned char trippleIndex);

  bool setLastChance();

  void notify(unsigned char impossibleValue);

  SudokuItem *getItem(unsigned char index) const;

  void print() const;

};
