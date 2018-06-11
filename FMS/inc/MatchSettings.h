#ifndef SOCCER_CARS_FMS_MATCH_SETTINGS_H
#define SOCCER_CARS_FMS_MATCH_SETTINGS_H

#include <memory>

#include <qwidget.h>
#include <qevent.h>
#include <qmessagebox.h>

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

  //private functions
  void makeConnections();
  void itemToGui();
  void guiToItem();
  bool unsavedChanges();

protected:
  void closeEvent(QCloseEvent* e) override;

public:
  //constructors
  MatchSettings(QWidget* parent = nullptr);
  ~MatchSettings();

signals:
  void settingsUpdated();

public slots:
  void btnSaveClickHandler();
  void btnCancelClickHandler();
  void btnDefaultClickhandler();

};

#endif