#ifndef SOCCER_CARS_FMS_MAIN_MENU_H
#define SOCCER_CARS_FMS_MAIN_MENU_H

#include <memory>

#include <qmainwindow.h>
#include <qtimer.h>
#include <qpointer.h>
#include <qmediaplayer.h>
#include <qmap.h>
#include <qevent.h>

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
  static const QMap<Windows, QString> WINDOWS_STR_MAP;

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
  void windowClosed(Windows closedWindow);

private slots:
  void carSettingsClosed();
  void matchSettingsClosed();
  void diagnosticsClosed();

protected:
  void closeEvent(QCloseEvent* event) override;

public:
  //constructors
  MainMenu();
  ~MainMenu();

  //operator overloads
  friend OutputManager& operator<<(OutputManager& out, Windows toPrint);

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