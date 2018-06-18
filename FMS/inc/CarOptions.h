#ifndef SOCCER_CARS_FMS_CAR_OPTIONS_H
#define SOCCER_CARS_FMS_CAR_OPTIONS_H

#include <algorithm>

#include "CmdOptions.h"
#include "MatchOptions.h"

class CarOptions
{
private:
  static int defaultCarNameNum;
  //member data
  unsigned int m_team;
  bool m_bypassed;
  QString m_name;

  //private functions
  void init(unsigned int team, const QString& name);

public:
  //constructors
  CarOptions(const QString& name = "");
  CarOptions(unsigned int team, const QString& name = "");

  //public functions
  void bypass();
  void enable();

  //getters
  unsigned int getTeam();
  bool getBypassed();
  QString getName();

  //setters
  void setTeam(unsigned int team);
};

#endif