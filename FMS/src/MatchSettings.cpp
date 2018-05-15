#include "MatchSettings.h"

MatchSettings::MatchSettings(QWidget* parent) :
  QWidget(parent)
{
  m_ui = new Ui_MatchSettings();
  m_ui->setupUi(this);
}
MatchSettings::~MatchSettings()
{
  delete m_ui;
}
