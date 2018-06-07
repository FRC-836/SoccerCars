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
  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    cout << "INFO: CarSettings: deconstructing..." << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)

  delete m_ui;
}
