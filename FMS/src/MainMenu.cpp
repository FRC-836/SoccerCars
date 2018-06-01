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
}
void MainMenu::startMatch()
{
  //update button text
  m_ui->btnStartStop->setText("Stop Match");
}

//constructors
MainMenu::MainMenu()
{
  m_ui = new Ui_MainMenu();
  m_ui->setupUi(this);

  //make timers
  m_tmrMatchTimer = new QTimer(this);
  m_tmrSecondTimer = new QTimer(this);

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
}
void MainMenu::btnCarSettingsClickHandler()
{
  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    cout << "INFO: MainMenu: car settings button clicked" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
}
void MainMenu::btnStartStopClickHandler()
{
  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    cout << "INFO: MainMenu: " <<  m_ui->btnStartStop->text() << " button clicked" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
}
void MainMenu::btnDiagnosticsClickHandler()
{
  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    cout << "INFO: MainMenu: diagnostics button clicked" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
}
void MainMenu::tmrMatchTimerTimeoutHandler()
{
  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::USER_INFO)
  {
    cout << "INFO: MainMenu: Match timer has ended." << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::USER_INFO)
}
void MainMenu::tmrSecondTimerTimeoutHandler()
{
  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    cout << "INFO: MainMenu: second timer ticked" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
}
