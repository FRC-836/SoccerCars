#ifndef SOCCER_CARS_FMS_CAR_OPTIONS_H
#define SOCCER_CARS_FMS_CAR_OPTIONS_H

#include "CmdOptions.h"
#include "MatchOptions.h"

class CarOptions
{
private:
  static int defaultCarNameNum;
  static QMap<int, bool> controllersUsed;

  //member data
  unsigned int m_team;
  unsigned int m_controller;
  bool m_bypassed;
  QString m_name;

  //private functions
  void init(unsigned int team, unsigned int controller, const QString& name);

public:
  //constructors
  CarOptions(const QString& name = "");
  CarOptions(unsigned int team, const QString& name = "");
  CarOptions(unsigned int team, unsigned int controller, const QString& name = "");

  //public functions
  void bypass();
  void enable();

  //getters
  unsigned int getTeam();
  unsigned int getController();
  bool getBypassed();
  QString getName();

  //setters
  void setTeam(unsigned int team);
  void setController(unsigned int controller);
};

#endif