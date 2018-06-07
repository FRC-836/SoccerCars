#ifndef SOCCER_CARS_FMS_MATCH_SETTINGS_H
#define SOCCER_CARS_FMS_MATCH_SETTINGS_H

#include <qwidget.h>

#include "ui_MatchSettings.h"
#include "OutputManager.h"
#include "CmdOptions.h"
#include "MatchOptions.h"

class MatchSettings : public QWidget
{
  Q_OBJECT

private:
  Ui_MatchSettings* m_ui;

public:
  MatchSettings(std::shared_ptr<MatchOptions> options, QWidget* parent = nullptr);
  ~MatchSettings();

signals:

public slots:

};

#endif