#ifndef SOCCER_CARS_FMS_MATCH_SETTINGS_H
#define SOCCER_CARS_FMS_MATCH_SETTINGS_H

#include <memory>

#include <qwidget.h>
#include <qevent.h>

#include "ui_MatchSettings.h"
#include "OutputManager.h"
#include "CmdOptions.h"
#include "MatchOptions.h"

class MatchSettings : public QWidget
{
  Q_OBJECT

private:
  //member data
  Ui_MatchSettings* m_ui;
  std::shared_ptr<MatchOptions> m_matchSettings;

  //private functions
  void makeConnections();
  void itemToGui(std::shared_ptr<MatchOptions> item);
  void guiToItem();

protected:
  void closeEvent(QCloseEvent* e) override;

public:
  //constructors
  MatchSettings(std::shared_ptr<MatchOptions> options, QWidget* parent = nullptr);
  ~MatchSettings();

signals:
  void settingsUpdated();

public slots:
  void btnSaveClickHandler();
  void btnCancelClickHandler();
  void btnDefaultClickhandler();

};

#endif