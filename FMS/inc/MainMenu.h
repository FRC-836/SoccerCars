#ifndef SOCCER_CARS_FMS_MAIN_MENU_H
#define SOCCER_CARS_FMS_MAIN_MENU_H

#include <memory>

#include <qmainwindow.h>
#include <qtimer.h>

#include "ui_MainMenu.h"
#include "CmdOptions.h"
#include "MatchOptions.h"

class MainMenu : public QMainWindow
{
  Q_OBJECT

private:
  //member variables
  Ui_MainMenu* m_ui;
  std::unique_ptr<QTimer> m_tmrMatchTimer;
  std::unique_ptr<QTimer> m_tmrSecondTimer;
  std::shared_ptr<MatchOptions> m_matchSettings;

  //private functions
  void makeConnections();
  void stopMatch(bool hasWinner);
  void startMatch();

public:
  //constructors
  MainMenu();
  ~MainMenu();

signals:
  void matchStopped();
  void matchStarted();
  void destroyed();

public slots:
  void btnMatchSettingsClickHandler();
  void btnCarSettingsClickHandler();
  void btnStartStopClickHandler();
  void btnDiagnosticsClickHandler();
  void tmrMatchTimerTimeoutHandler();
  void tmrSecondTimerTimeoutHandler();
};

#endif