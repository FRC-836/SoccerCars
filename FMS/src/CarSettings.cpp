#include "CarSettings.h"

extern OutputManager cout;

//private functions
void CarSettings::setupCarOptionsWidgets()
{
  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    cout << "INFO: CarSettings: Setting up layout for being able to edit car options" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)

  //wipe the table for starting clean
  m_ui->tblTeamOrg->clear();

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

  //post a resize event
  QResizeEvent* e = new QResizeEvent(QSize(10, 10), size());
  QCoreApplication::postEvent(this, e);
}
void CarSettings::makeConnections()
{
  connect(m_tmrOptionsCheck, &QTimer::timeout, this, &CarSettings::optionsGood);
}

//private slots
bool CarSettings::optionsGood()
{
  //check that all teams have an appropriate ammount of cars on them
  QVector<int> tooLargeTeams; //contains all the teams that are too full
  QSet<int> controllersUsed; //hold the controllers useed
  QVector<std::pair<int, int>> bypassedCars; //vector of <team, car> for bypassed cars

  //iterate over teams
  for (int i = 0; i < m_cars->size(); i++)
  {
    if ((*m_cars)[i].size() > MatchOptions::m_carsPerTeam)
    {
      tooLargeTeams.push_back(i);
    } //end  if ((*m_cars)[i].size() >= MatchOptions::m_carsPerTeam)

    //iterate over cars on team
    for (int j = 0; j < (*m_cars)[i].size(); j++)
    {
      controllersUsed.insert((*m_cars)[i][j]->getController());
      if ((*m_cars)[i][j]->getBypassed())
      {
        bypassedCars.push_back(std::make_pair(i, j));
      } //end  if ((*m_cars)[i][j]->getBypassed())
    } //end  for (int j = 0; j < (*m_cars)[i].size(); j++)
  } //end  for (int i = 0; i < m_cars->size(); i++)

  if (!tooLargeTeams.isEmpty())
  {
    if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_ONLY)
    {
      cout << "ERORR: CarSettings: Can't close, there are teams that have too many cars" << endl;
    } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_ONLY)
    m_ui->lblErrorList->setText("One team has too many cars");
    return false;
  } //end  if (!tooLargeTeams.isEmpty())

  if (controllersUsed.size() != MatchOptions::m_carsPerTeam * MatchOptions::m_numberOfTeams)
  {
    if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_ONLY)
    {
      cout << "ERROR: CarSettings: There is at least one controller being used more than once" << endl;
    } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_ONLY)
    m_ui->lblErrorList->setText("At least one controller is used more than once");
    return false;
  }//end if(controllersUsed.size() != MatchOptions::m_carsPerTeam * MatchOptions::m_numberOfTeams)

  if (!bypassedCars.isEmpty())
  {
    if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_AND_WARNINGS)
    {
      cout << "WARNING: CarSettings: There are cars that are set to be bypassed" << endl;
    } //end  if (CmdOptions::verbosity > +CmdOptions::DEBUG_LEVEL::ERRORS_AND_WARNINGS)
  } //end  if (!bypassedCars.isEmpty())
  m_ui->lblErrorList->setText("");
  return true;
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

  //call base class (this is why i don't have to accept the event)
  QWidget::resizeEvent(event);
}
void CarSettings::closeEvent(QCloseEvent* event)
{
  if (optionsGood())
  {
    QWidget::closeEvent(event);
  } //end  if (optionsGood())
  else
  {
    event->ignore();
  } //end  else
}

//constructors
CarSettings::CarSettings(std::shared_ptr<TeamList_t> cars, QWidget* parent) :
  QWidget(parent)
{
  //force deconstruction on close
  setAttribute(Qt::WA_DeleteOnClose);

  //store the current car settings
  m_cars = cars;

  //configure timer that will check if the options are good
  m_tmrOptionsCheck = new QTimer(this);
  m_tmrOptionsCheck->setInterval(100);
  m_tmrOptionsCheck->start();

  //configure the UI
  m_ui = new Ui_CarSettings;
  m_ui->setupUi(this);

  //setup the table
  m_ui->tblTeamOrg->horizontalHeader()->setVisible(false);
  m_ui->tblTeamOrg->verticalHeader()->setVisible(false);
  m_ui->tblTeamOrg->setSelectionMode(QAbstractItemView::SelectionMode::NoSelection);

  //create the grid
  setupCarOptionsWidgets();

  makeConnections();
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