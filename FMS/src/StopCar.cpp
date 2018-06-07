#include "StopCar.h"

extern OutputManager cout;

StopCar::StopCar(QWidget* parent)
{
  m_ui = new Ui_EmergencyCarStop();
  m_ui->setupUi(this);
}
StopCar::~StopCar()
{
  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    cout << "INFO: StopCar: deconstructing..." << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)

  delete m_ui;
}
