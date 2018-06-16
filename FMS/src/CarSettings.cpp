#include "CarSettings.h"

extern OutputManager cout;

CarSettings::CarSettings(QWidget* parent) :
  QWidget(parent)
{
  setAttribute(Qt::WA_DeleteOnClose);

  m_ui = new Ui_CarSettings;
  m_ui->setupUi(this);

  //TEMP: to test display code for the car options widget
  std::shared_ptr<CarOptions> temp = std::make_shared<CarOptions>();
  m_temp = new CarOptionsWidget(temp);
  m_temp->show();
}
CarSettings::~CarSettings()
{
  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    cout << "INFO: CarSettings: deconstructing..." << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)

  delete m_ui;

  //TEMP
  delete m_temp;
}
