#include "CarSettings.h"

extern OutputManager cout;

//private functions
void CarSettings::setupCarOptionsWidgets()
{
}

//constructors
CarSettings::CarSettings(std::shared_ptr<QVector<CarOptions>> cars, QWidget* parent) :
  QWidget(parent)
{
  setAttribute(Qt::WA_DeleteOnClose);

  m_cars = cars;

  m_ui = new Ui_CarSettings;
  m_ui->setupUi(this);

  //create the grid
  setupCarOptionsWidgets();
}
CarSettings::~CarSettings()
{
  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    cout << "INFO: CarSettings: deconstructing..." << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)

  delete m_ui;
}
