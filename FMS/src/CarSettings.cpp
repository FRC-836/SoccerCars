#include "CarSettings.h"

extern OutputManager cout;

//private functions
void CarSettings::setupCarOptionsWidgets()
{
  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    cout << "INFO: CarSettings: Setting up layout for being able to edit car options" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)

  //setup the grid (rows and columns)
  m_ui->tblTeamOrg->setColumnCount(MatchOptions::m_carsPerTeam);
  m_ui->tblTeamOrg->setRowCount(MatchOptions::m_numberOfTeams);

  //create each of the CarOptionsWidgets
  for (int i = 0; i < m_cars->size(); i++) //team iteration
  {
    auto team = (*m_cars)[i];
    for (int j = 0; j < team.size(); j++) //car iteration
    {
      CarOptionsWidget* toAdd = new CarOptionsWidget(team[j], this);
      m_ui->tblTeamOrg->setCellWidget(i, j, toAdd);
    } //end  for (int j = 0; j < team.size(); j++)
  } //end  for (int i = 0; i < m_cars->size(); i++
}

//event handlers
void CarSettings::resizeEvent(QResizeEvent* event)
{
  //set the column sizes
  int columnWidth = m_ui->tblTeamOrg->size().width() / m_ui->tblTeamOrg->columnCount();
  for (int i = 0; i < m_ui->tblTeamOrg->columnCount(); i++)
  {
    m_ui->tblTeamOrg->setColumnWidth(i, columnWidth);
  } //end  for (int i = 0; i < m_ui->tblTeamOrg->columnCount(); i++)

  //set the row sizes
  int rowHeight = m_ui->tblTeamOrg->size().height() / m_ui->tblTeamOrg->rowCount();
  for (int i = 0; i < m_ui->tblTeamOrg->rowCount(); i++)
  {
    m_ui->tblTeamOrg->setRowHeight(i, rowHeight - 10);
  } //end  for (int i = 0; i < m_ui->tblTeamOrg->rowCount(); i++)
}

//constructors
CarSettings::CarSettings(std::shared_ptr<TeamList_t> cars, QWidget* parent) :
  QWidget(parent)
{
  setAttribute(Qt::WA_DeleteOnClose);

  m_cars = cars;

  m_ui = new Ui_CarSettings;
  m_ui->setupUi(this);

  //setup the table
  m_ui->tblTeamOrg->horizontalHeader()->setVisible(false);
  m_ui->tblTeamOrg->verticalHeader()->setVisible(false);
  m_ui->tblTeamOrg->setSelectionMode(QAbstractItemView::SelectionMode::NoSelection);

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
