#ifndef SOCCER_CARS_FMS_CONNECT_H
#define SOCCER_CARS_FMS_CONNECT_H

#include <qwidget.h>

#include "ui_CarSettings.h"
#include "CmdOptions.h"
#include "OutputManager.h"

class CarSettings : public QWidget
{
  Q_OBJECT

private:
  Ui_CarSettings* m_ui;

public:
  CarSettings(QWidget* parent = nullptr);
  ~CarSettings();

signals:

public slots:

};

#endif