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
  QMap<int, int> carsAdded;
  for (auto car : (*m_cars))
  {
    if (!carsAdded.contains(car.getTeam()))
    {
      carsAdded.insert(car.getTeam(), 0);
    } //end  if (!carsAdded.contains(car.getTeam()))

    CarOptionsWidget* toAdd = new CarOptionsWidget(std::make_shared<CarOptions>(car), this);
    m_ui->tblTeamOrg->setCellWidget(car.getTeam(), carsAdded[car.getTeam()], toAdd);
    carsAdded[car.getTeam()]++;
  } //end  for (auto car : (*m_cars))

}

//constructors
CarSettings::CarSettings(std::shared_ptr<QVector<CarOptions>> cars, QWidget* parent) :
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
