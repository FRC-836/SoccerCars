#include "CarSettings.h"

CarSettings::CarSettings(QWidget* parent) :
  QWidget(parent)
{
  m_ui = new Ui_CarSettings;
  m_ui->setupUi(this);
}
CarSettings::~CarSettings()
{
}
