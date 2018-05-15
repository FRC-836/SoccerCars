#include "StopCar.h"

StopCar::StopCar(QWidget* parent)
{
  m_ui = new Ui_EmergencyCarStop();
  m_ui->setupUi(this);
}
StopCar::~StopCar()
{
  delete m_ui;
}
