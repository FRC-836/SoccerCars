#include "CarOptions.h"

extern OutputManager cout;

int CarOptions::defaultCarNameNum = 0;
QMap<int, bool> CarOptions::controllersUsed;

//private functions
void CarOptions::init(unsigned int team, unsigned int controller, const QString& name)
{
  //check if the provided name is blank, if it is, use a default one
  if (name.trimmed().isEmpty())
  {
    m_name = "Car " + QString::number(defaultCarNameNum);
    defaultCarNameNum++;
  } //end  if (std::all_of(name.begin(), name.end(), isspace))
  else
  {
    m_name = name;
  } //end  else

  setTeam(team);
  setController(controller);
  m_bypassed = false; //all cars are enabled by default
}

//constructors
CarOptions::CarOptions(const QString& name)
{
  init(0, 0, name);
}
CarOptions::CarOptions(unsigned int team, const QString& name)
{
  init(team, 0, name);
}
CarOptions::CarOptions(unsigned int team, unsigned int controller, const QString& name)
{
  init(team, controller, name);
}

//public functions
void CarOptions::bypass()
{
  m_bypassed = true;
  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    cout << "INFO: CarOptions: Car status updated to bypassed" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
};
void CarOptions::enable()
{
  m_bypassed = false;
  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    cout << "INFO: CarOptions: car status updated to enabled" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
}

//getters
unsigned int CarOptions::getTeam()
{
  return m_team;
}
unsigned int CarOptions::getController()
{
  return m_controller;
}
bool CarOptions::getBypassed()
{
  return m_bypassed;
}
QString CarOptions::getName()
{
  return m_name;
}

//setter
void CarOptions::setTeam(unsigned int team)
{
  if (team >= 0)
  {
    m_team = team;
  } //end  if (team >= 0)
  else
  {
    if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_ONLY)
    {
      cout << "ERROR: CarOptions: cannot set team to a negative number. Team remains unchanged" 
           << endl;
    } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_ONLY)
  } //end  else
}
void CarOptions::setController(unsigned int controller)
{
  if (controller >= 0)
  {
    if (controllersUsed[controller])
    {
      if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_ONLY)
      {
        cout << "ERROR: CarOptions: Trying to set controller to one that is already used, "
             << "assigning a default unused conroller" << endl;
      } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_ONLY)
      controller = 1;
      while (controllersUsed[controller])
      {
        controller++;
      } //end  while (controllersUsed[controller])
    }
    m_controller = controller;
    controllersUsed[controller] = true;
  } //end  if (controller >= 0)
  else
  {
    if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_ONLY)
    {
      cout << "ERROR: CarOptions: cannot set controller to a negative number. Controller remains "
           << "unchanged" << endl;
    } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_ONLY)
  } //end  else
}
