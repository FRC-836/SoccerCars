#ifndef SOCCER_CARS_FMS_DIAGNOSTICS_H
#define SOCCER_CARS_FMS_DIAGNOSTICS_H

#include <qwidget.h>

#include "ui_Diagnostics.h"
#include "CmdOptions.h"
#include "OutputManager.h"

class Diagnostics : public QWidget
{
  Q_OBJECT

private:
  Ui_Diagnostics* m_ui;

public:
  Diagnostics(QWidget* parent = nullptr);
  ~Diagnostics();

signals:

public slots:
  
};

#endif