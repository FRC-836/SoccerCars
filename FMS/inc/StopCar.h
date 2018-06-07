#ifndef SOCCER_CARS_FMS_STOP_CAR_H
#define SOCCER_CARS_FMS_STOP_CAR_H

#include <qwidget.h>

#include "ui_StopCar.h"
#include "CmdOptions.h"

class StopCar : public QWidget
{
  Q_OBJECT

private:
  Ui_EmergencyCarStop* m_ui;
  
public:
  StopCar(QWidget* parent = nullptr);
  ~StopCar();

signals:

public slots:

};

#endif