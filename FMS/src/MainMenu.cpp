#include "MainMenu.h"

extern OutputManager cout;

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

  //TODO: make this more permanent buzzer playing sound
  QMediaPlayer* player = new QMediaPlayer;
  player->setMedia(QUrl::fromLocalFile("C:/Users/Cheeto/Robotics/FRC/RocketLeagueCars/Code/FMS/res/alarm-buzzer.mp3"));
  player->setVolume(100);
  player->play();
  //intentional memory leak. sound won't play if the object is deconstructed

  //this should maybe be the first thing done in this function, but its last for now
  m_matchRunning = false;
}
void MainMenu::startMatch()
{
  //update button text
  m_ui->btnStartStop->setText("Stop Match");

  //TODO: add code to make sure all the cars are functional and start the match

  //set the timer value to the start of the match number of seconds
  m_ui->lcdTimer->display((int)m_matchSettings->m_seconds);

  //start the timers
  m_tmrMatchTimer->start(m_matchSettings->m_seconds * 1000);
  m_tmrSecondTimer->start(1000);

  //this should be the last thing done in this function
  m_matchRunning = true;
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
  m_matchSettings = std::make_shared<MatchOptions>();
  m_matchRunning = false;

  makeConnections();
}
MainMenu::~MainMenu()
{
  delete m_ui;
}

//public functions

//public slots
void MainMenu::btnMatchSettingsClickHandler()
{
  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    cout << "INFO: MainMenu: match settings button clicked" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)

  //TODO: add call to match settings editor window
}
void MainMenu::btnCarSettingsClickHandler()
{
  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    cout << "INFO: MainMenu: car settings button clicked" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)

  //TODO: add call to car settings editor window
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

  //TODO: add call to diagnostics window
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
