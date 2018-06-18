#ifndef SOCCER_CARS_FMS_CONNECT_H
#define SOCCER_CARS_FMS_CONNECT_H

#include <qwidget.h>
#include <qvector.h>

#include "ui_CarSettings.h"
#include "CmdOptions.h"
#include "OutputManager.h"
#include "CarOptionsWidget.h"
#include "UsefulTypes.h"

class CarSettings : public QWidget
{
  Q_OBJECT

private:
  //member data
  Ui_CarSettings* m_ui;
  QVector<CarOptionsWidget*> m_carOptionsWidgets;
  std::shared_ptr<TeamList_t> m_cars;

  //private functions
  void setupCarOptionsWidgets();

public:
  //constructors
  CarSettings(std::shared_ptr<TeamList_t> cars, QWidget* parent = nullptr);
  ~CarSettings();

signals:

public slots:

};

#endif