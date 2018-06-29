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
  m_ui->tblTeamOrg->setRowCount(MatchOptions::m_numberOfTeams);
  int maxTeamSize = 0;
  for (int i = 0; i < m_cars->size(); i++)
  {
    //since teams can have uneven numbers of teams during the car assignment, can't simply make
    //grid based on setting's team size
    maxTeamSize = ((*m_cars)[i].size() > maxTeamSize) ? (*m_cars)[i].size() : maxTeamSize;
  } //end  for (int i = 0; i < m_cars->size(); i++)
  m_ui->tblTeamOrg->setColumnCount(maxTeamSize);

  //create each of the CarOptionsWidgets
  for (int i = 0; i < m_cars->size(); i++) //team iteration
  {
    auto team = (*m_cars)[i];
    for (int j = 0; j < team.size(); j++) //car iteration
    {
      CarOptionsWidget* toAdd = new CarOptionsWidget(team[j], this);
      connect(toAdd, &CarOptionsWidget::teamChange, this, &CarSettings::teamChangeHandler);
      m_ui->tblTeamOrg->setCellWidget(m_cars->size() - i - 1, j, toAdd);
    } //end  for (int j = 0; j < team.size(); j++)
  } //end  for (int i = 0; i < m_cars->size(); i++
}
void CarSettings::makeConnections()
{
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

//public slots
void CarSettings::teamChangeHandler(int newTeam, int oldTeam)
{
  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    cout << "INFO: CarSettings: recieved signal that a team change request has been made" << endl;
    cout << "\told team: " << oldTeam << ", newTeam: " << newTeam << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)

  //ensure the sender is a valid CarOptionsWidge
  CarOptionsWidget* carSender = qobject_cast<CarOptionsWidget*>(sender());
  if (carSender != nullptr)
  {
    //get the column the sender is from
    auto column = carSender->pos().x() / carSender->width();
    if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
    {
      cout << "INFO: CarSettings: column of the requesting the team change is " << column << endl;
    } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)

    //get the car from the sender
    auto car = carSender->getCar();

    //move the car to its new team
    (*m_cars)[oldTeam].remove(column);
    (*m_cars)[newTeam].push_back(std::make_shared<decltype(car)>(car));

    setupCarOptionsWidgets();
  } //end  if (carSender != nullptr)
  else
  {
    if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_ONLY)
    {
      cout << "ERROR: CarSettings: recieved team change signal from something "
           << "that isn't a CarOptionsWidget. Ignoring request" << endl;
    } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_ONLY)
  } //end  else
}
void CarSettings::bypassStateChangedHandler(bool bypassed)
{
}
void CarSettings::controllerChangedHandler(int newController)
{
}
void CarSettings::indicateRequestedHandler()
{
}