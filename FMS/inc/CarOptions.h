#ifndef SOCCER_CARS_FMS_CAR_OPTIONS_H
#define SOCCER_CARS_FMS_CAR_OPTIONS_H

#include "CmdOptions.h"
#include "MatchOptions.h"

class CarOptions
{
private:
  //member data
  unsigned int m_team;
  bool m_bypassed;

  //private functions
  void init(unsigned int team);

public:
  //constructors
  CarOptions();
  CarOptions(unsigned int team);

  //public functions
  void bypass();
  void enable();

  //getters
  unsigned int getTeam();

  //setters
  void setTeam(unsigned int team);
};

#endif