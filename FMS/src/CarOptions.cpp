#include "CarOptions.h"

extern OutputManager cout;

//private functions
void CarOptions::init(unsigned int team)
{
  setTeam(team);
  bypassed = false; //all cars are enabled by default
}

//constructors
CarOptions::CarOptions()
{
  init(0);
}
CarOptions::CarOptions(unsigned int team)
{
  init(team);
}

//public functions
void CarOptions::bypass()
{
  bypassed = true;
  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    cout << "INFO: CarOptions: Car status updated to bypassed" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
};
void CarOptions::enable()
{
  bypassed = false;
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
