#include "MatchSettings.h"

extern OutputManager cout;

MatchSettings::MatchSettings(std::shared_ptr<MatchOptions> options, QWidget* parent) :
  QWidget(parent)
{
  m_ui = new Ui_MatchSettings();
  m_ui->setupUi(this);

  //TODO: handle match options, set values on the UI to these values
}
MatchSettings::~MatchSettings()
{
  delete m_ui;
}
