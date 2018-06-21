#include "MainMenu.h"

extern OutputManager cout;

//member initialization
const QMap<MainMenu::Windows, QString> MainMenu::WINDOWS_STR_MAP = {
  {Windows::CAR_SETTINGS,   "Car Settings"},
  {Windows::DIAGNOSTICS,    "Diagnostics"},
  {Windows::MATCH_SETTINGS, "Match Settings"}
};

//private functions
void MainMenu::makeConnections()
{
  //ui connections
  connect(m_ui->btnStartStop, &QPushButton::clicked, this, &MainMenu::btnStartStopClickHandler);
  connect(m_ui->btnCarSettings, &QPushButton::clicked, this, &MainMenu::btnCarSettingsClickHandler);
  connect(m_ui->btnDiag, &QPushButton::clicked, this, &MainMenu::btnDiagnosticsClickHandler);
  connect(m_ui->btnMatchSettings, &QPushButton::clicked, this, &MainMenu::btnMatchSettingsClickHandler);

  //timer connections
  connect(m_tmrMatchTimer, &QTimer::timeout, this, &MainMenu::tmrMatchTimerTimeoutHandler);
  connect(m_tmrSecondTimer, &QTimer::timeout, this, &MainMenu::tmrSecondTimerTimeoutHandler);
}
void MainMenu::stopMatch(bool hasWinner)
{
  //update button text
  m_ui->btnStartStop->setText("Start Match");

  //TODO: add code to stop all the cars and kill the match

  //stop the timers
  m_tmrMatchTimer->stop();
  m_tmrSecondTimer->stop();

  //clear the timer value
  m_ui->lcdTimer->display(0);

  //TODO: make this more permanent buzzer playing sound (also find different sound bite)
  m_mediaPlayer->setMedia(QUrl::fromLocalFile("C:/Users/Cheeto/Robotics/FRC/RocketLeagueCars/Code/FMS/res/alarm-buzzer.mp3"));
  m_mediaPlayer->setVolume(100); //TODO: make configurable setting
  m_mediaPlayer->play();

  //this should maybe be the first thing done in this function, but its last for now
  m_matchRunning = false;
}
void MainMenu::startMatch()
{
  //update button text
  m_ui->btnStartStop->setText("Stop Match");

  //TODO: add code to make sure all the cars are functional and start the match

  //set the timer value to the start of the match number of seconds
  m_ui->lcdTimer->display((int)MatchOptions::m_seconds);

  //start the timers
  m_tmrMatchTimer->start(MatchOptions::m_seconds * 1000);
  m_tmrSecondTimer->start(1000);

  //this should be the last thing done in this function
  m_matchRunning = true;
}
void MainMenu::windowClosed(Windows closedWindow)
{
  if (m_openWindows.contains(closedWindow))
  {
    if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
    {
      cout << "Info: MainMenu: removing " << closedWindow << " from list of open windows" << endl;
    } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
    m_openWindows.remove(closedWindow);
  } //end  if (m_openWindows.contains(closedWindow))
  else
  {
    if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_ONLY)
    {
      cout << "ERROR: MainMenu: Can't remove " << closedWindow <<
              " from list of open windows because it wasn't open" << endl;
    } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_ONLY)
  } //end  else
}

//private slots
void MainMenu::carSettingsClosed()
{
  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    cout << "INFO: MainMenu: Recieved signal that Car Settings was closed" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  windowClosed(Windows::CAR_SETTINGS);
}
void MainMenu::matchSettingsClosed()
{
  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    cout << "INFO: MainMenu: Recieved signal that Match Settings was closed" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  windowClosed(Windows::MATCH_SETTINGS);
}
void MainMenu::diagnosticsClosed()
{
  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    cout << "INFO: MainMenu: Recieved signal that Diagnostics was closed" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  windowClosed(Windows::DIAGNOSTICS);
}

//event handlers
void MainMenu::closeEvent(QCloseEvent* event)
{
  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    cout << "INFO: MainMenu: handling close event" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)

  int msgBoxSelection = QMessageBox::Ok; //if the match isn't running, want to close like normal
  if (m_matchRunning)
  {
    if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_AND_WARNINGS)
    {
      cout << "WARNING: MainMenu: attempting to close the FMS while a match is running." << endl;
      cout << "\tThis operation is unsupported and will have unpredictable consequences." << endl;
    } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_AND_WARNINGS)
    QMessageBox msgBox(this);
    msgBox.setText("There is a match running");
    msgBox.setInformativeText("Closing the FMS while a match is running isn't a good idea\n" +
                              QString("It will have unpredictable consequences."));
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    msgBoxSelection = msgBox.exec();
  } //end  if (m_matchRunning)

  switch (msgBoxSelection)
  {
    case QMessageBox::Ok:
      event->accept();
      if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
      {
        cout << "INFO: MainMenu: closing all open windows" << endl;
      } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
      for (auto window : m_openWindows)
      {
        window->close();
      } //end  for (auto window : m_openWindows)
      QMainWindow::closeEvent(event);
      break;
    case QMessageBox::Cancel:
      //reject the event, not ready to close yet
      if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
      {
        cout << "INFO: MainMenu: canceling close event" << endl;
      } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
      event->ignore();
      break;
  } //end  switch (msgBoxSelection)
}

//constructors
MainMenu::MainMenu()
{
  m_ui = new Ui_MainMenu();
  m_ui->setupUi(this);

  //make timers
  m_tmrMatchTimer = new QTimer(this);
  m_tmrSecondTimer = new QTimer(this);

  //initialize variables
  m_mediaPlayer = std::make_unique<QMediaPlayer>();
  m_cars = std::make_shared<TeamList_t>();
  m_matchRunning = false;

  matchSettingsUpdateHandler(); //initial creation of teams and cars

  makeConnections();
}
MainMenu::~MainMenu()
{
  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    cout << "INFO: MainMenu: Deconstructing..." << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)

  delete m_ui;
}

//operator overloads
OutputManager& operator<<(OutputManager& out, MainMenu::Windows toPrint)
{
  out << MainMenu::WINDOWS_STR_MAP.value(toPrint, "INVALID");
  return out;
}

//public slots
void MainMenu::btnMatchSettingsClickHandler()
{
  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    cout << "INFO: MainMenu: match settings button clicked" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)

  if (!m_openWindows.contains(Windows::MATCH_SETTINGS))
  {
    MatchSettings* toOpen = new MatchSettings();
    m_openWindows.insert(Windows::MATCH_SETTINGS, toOpen);
    connect(toOpen, &MatchSettings::settingsUpdated, this, &MainMenu::matchSettingsUpdateHandler);
    connect(toOpen, &MatchSettings::destroyed, this, &MainMenu::matchSettingsClosed);
    toOpen->show();
  } //end  if (m_openWindows.contains(Windows::MATCH_SETTINGS))
  else
  {
    if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
    {
      cout << "INFO: MainMenu: Can't open Match Settings because it's already open." << endl;
      cout << "\tShifting focus to open Match Settings window." << endl;
    } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
    m_openWindows[Windows::MATCH_SETTINGS]->activateWindow();
  } //end  else
}
void MainMenu::btnCarSettingsClickHandler()
{
  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    cout << "INFO: MainMenu: car settings button clicked" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)

  if (!m_openWindows.contains(Windows::CAR_SETTINGS))
  {
    CarSettings* toOpen = new CarSettings(m_cars);
    m_openWindows.insert(Windows::CAR_SETTINGS, toOpen);
    connect(toOpen, &CarSettings::destroyed, this, &MainMenu::carSettingsClosed);

    toOpen->resize(658, 480); //TEMP until resize algo based on team/cars is established
    toOpen->show();
  } //end  if (!m_openWindows.contains(Windows::CAR_SETTINGS))
  else
  {
    if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
    {
      cout << "INFO: MainMenu: Can't open Car Settings because it's already open." << endl;
      cout << "\tShifting focus to open Car Settings window." << endl;
    } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
    m_openWindows[Windows::CAR_SETTINGS]->activateWindow();
  } //end  else
}
void MainMenu::btnStartStopClickHandler()
{
  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    cout << "INFO: MainMenu: " <<  m_ui->btnStartStop->text() << " button clicked" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)

  if (m_matchRunning)
  {
    stopMatch(false);
  } //end  if (m_matchRunning)
  else
  {
    startMatch();
  } //end  else
}
void MainMenu::btnDiagnosticsClickHandler()
{
  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    cout << "INFO: MainMenu: diagnostics button clicked" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)

  if (!m_openWindows.contains(Windows::DIAGNOSTICS))
  {
    Diagnostics* toOpen = new Diagnostics();
    m_openWindows.insert(Windows::DIAGNOSTICS, toOpen);
    connect(toOpen, &Diagnostics::destroyed, this, &MainMenu::diagnosticsClosed);
    toOpen->show();
  } //end  if (!m_openWindows.contains(Windows::DIAGNOSTICS))
  else
  {
    if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
    {
      cout << "INFO: MainMenu: Can't open Diagnostics because it's already open." << endl;
      cout << "\tShifting focus to open Diagnostics window." << endl;
    } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
    m_openWindows[Windows::DIAGNOSTICS]->activateWindow();
  } //end  else
}
void MainMenu::tmrMatchTimerTimeoutHandler()
{
  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::USER_INFO)
  {
    cout << "INFO: MainMenu: Match timer has ended." << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::USER_INFO)

  //stop match TODO: determine if winner
  stopMatch(true);
}
void MainMenu::tmrSecondTimerTimeoutHandler()
{
  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    cout << "INFO: MainMenu: second timer ticked" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)

  //set timer to one less than it currently is
  m_ui->lcdTimer->display(m_ui->lcdTimer->value() - 1);
}
void MainMenu::matchSettingsUpdateHandler()
{
  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    cout << "INFO: MainMenu: recieved match settings update signal" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)

  //------------------------------------------------------------------------------------
  //modify the car settings vector as appropriate to accomadate new/removed teams
  //------------------------------------------------------------------------------------
  if (m_cars->size() < MatchOptions::m_numberOfTeams)
  {
    //not enough teams
    if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::USER_INFO)
    {
      cout << "INFO: MainMenu: not enough teams, adding more" << endl;
    } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::USER_INFO)

    while (m_cars->size() < MatchOptions::m_numberOfTeams)
    {
      Team_t toAdd;
      for (int i = 0; i < MatchOptions::m_carsPerTeam; i++)
      {
        toAdd.push_back(CarOptions(m_cars->size() + 1));
      }
      m_cars->push_back(toAdd);
    } //end  while (m_cars->size() < MatchOptions::m_numberOfTeams)
  } //end  if (m_cars < MatchOptions::m_numberOfTeams)
  else if (m_cars->size() > MatchOptions::m_numberOfTeams)
  {
    //too many teams
    if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::USER_INFO)
    {
      cout << "INFO: MainMenu: too many teams, removing the extra ones" << endl;
    } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::USER_INFO)

    int teamsToRemove = m_cars->size() - MatchOptions::m_numberOfTeams;
    for (int i = 0; i < teamsToRemove; i++)
    {
      m_cars->removeLast();
    } //end  for (int i = 0; i < teamsToRemove; i++)
  } //end  else if (m_cars->size() > MatchOptions::m_numberOfTeams)

  int index = 0;
  for (auto team : (*m_cars))
  {
    if (team.size() > MatchOptions::m_carsPerTeam)
    {
      //too many cars on this team
      if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::USER_INFO)
      {
        cout << "INFO: MainMenu: too many cars on team " << team[0].getTeam() 
             << " removing extra" << endl;
      } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::USER_INFO)

      while (team.size() > MatchOptions::m_carsPerTeam)
      {
        team.removeLast();
      } //end  while (teams.size() > MatchOptions::m_carsPerTeam)
    } //end  if (team.size() > MatchOptions::m_carsPerTeam)
    else if (team.size() < MatchOptions::m_carsPerTeam)
    {
      //not enough cars on this team
      if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::USER_INFO)
      {
        cout << "INFO: MainMenu: not enough cars on team " << team[0].getTeam()
             << " adding cars" << endl;
      }

      while (team.size() < MatchOptions::m_carsPerTeam)
      {
        CarOptions toAdd(index);
        team.push_back(toAdd);
      }
    } //end  else if (team.size() < MatchOptions::m_carsPerTeam)
    index++;
  } //end  for (auto team : m_cars)
}
