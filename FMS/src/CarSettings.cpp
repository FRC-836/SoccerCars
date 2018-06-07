#include "CarSettings.h"

extern OutputManager cout;

CarSettings::CarSettings(QWidget* parent) :
  QWidget(parent)
{
  m_ui = new Ui_CarSettings;
  m_ui->setupUi(this);
}
CarSettings::~CarSettings()
{
}
