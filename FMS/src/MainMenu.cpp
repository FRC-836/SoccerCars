#include "MainMenu.h"

//private functions
void MainMenu::stopMatch(bool hasWinner)
{
}
void MainMenu::startMatch()
{
}

//constructors
MainMenu::MainMenu()
{
  m_ui = new Ui_MainMenu();
  m_ui->setupUi(this);
}
MainMenu::~MainMenu()
{
  delete m_ui;
}

//public functions

//public slots
void MainMenu::btnMatchSettingsClickHandler()
{
}
void MainMenu::btnCarSettingsClickHandler()
{
}
void MainMenu::btnStartStopClickHandler()
{
}
void MainMenu::btnDiagnosticsClickHandler()
{
}
void MainMenu::tmrMatchTimerTimeoutHandler()
{
}
void MainMenu::tmrSecondTimerTimeoutHandler()
{
}
