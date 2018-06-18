#include "CarSettings.h"

extern OutputManager cout;

//private functions
void CarSettings::setupCarOptionsWidgets()
{
  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    cout << "INFO: CarSettings: Setting up layout for being able to edit car options" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)

  //setup the grid
  m_ui->tblTeamOrg->setColumnCount(MatchOptions::m_carsPerTeam);
  m_ui->tblTeamOrg->setRowCount(MatchOptions::m_numberOfTeams);

  //create each of the CarOptionsWidgets
  for (int i = 0; i < m_cars->size(); i++)
  {
    auto team = (*m_cars)[i];
    for (int j = 0; j < team.size(); j++)
    {
      CarOptionsWidget* toAdd = new CarOptionsWidget(std::make_shared<CarOptions>(team[j]), this);
      toAdd->show();
      m_ui->tblTeamOrg->setCellWidget(i, j, toAdd);
    } //end  for (int j = 0; j < team.size(); j++)
  } //end  for (int i = 0; i < m_cars->size(); i++
}

//constructors
CarSettings::CarSettings(std::shared_ptr<TeamList_t> cars, QWidget* parent) :
  QWidget(parent)
{
  setAttribute(Qt::WA_DeleteOnClose);

  m_cars = cars;

  m_ui = new Ui_CarSettings;
  m_ui->setupUi(this);

  //create the grid
  setupCarOptionsWidgets();
}
CarSettings::~CarSettings()
{
  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    cout << "INFO: CarSettings: deconstructing..." << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)

  delete m_ui;

  //delete all the car options widgets TEMP until the parent system is used
  for (auto carWidget : m_carOptionsWidgets)
  {
    delete carWidget;
  }
}
