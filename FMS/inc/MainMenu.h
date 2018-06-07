#ifndef SOCCER_CARS_FMS_MAIN_MENU_H
#define SOCCER_CARS_FMS_MAIN_MENU_H

#include <memory>

#include <qmainwindow.h>
#include <qtimer.h>
#include <qpointer.h>
#include <qmediaplayer.h>
#include <qmap.h>

#include "ui_MainMenu.h"
#include "CmdOptions.h"
#include "MatchOptions.h"
#include "MatchSettings.h"
#include "Diagnostics.h"
#include "CarSettings.h"

class MainMenu : public QMainWindow
{
  Q_OBJECT

private:
  //enum of windows that can be opened from this one
  enum class Windows
  {
    MATCH_SETTINGS,
    DIAGNOSTICS,
    CAR_SETTINGS
  };

  //member variables
  Ui_MainMenu* m_ui;
  QPointer<QTimer> m_tmrMatchTimer;
  QPointer<QTimer> m_tmrSecondTimer;
  std::shared_ptr<MatchOptions> m_matchSettings;
  std::unique_ptr<QMediaPlayer> m_mediaPlayer;
  QMap<Windows, QWidget*> m_openWindows;
  bool m_matchRunning;

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