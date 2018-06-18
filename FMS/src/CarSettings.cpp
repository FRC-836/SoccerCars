#include "CarSettings.h"

extern OutputManager cout;

//private functions
void CarSettings::setupCarOptionsWidgets()
{
  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    cout << "INFO: CarSettings: Setting up layout for being able to edit car options" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)

  //create each of the CarOptionsWidgets
  for (int i = 0; i < m_cars->size(); i++)
  {
    m_carOptionsWidgets.push_back(new CarOptionsWidget(std::make_shared<CarOptions>((*m_cars)[i])));
  } //end  for (int i = 0; i < m_cars->size(); i++)

  //TEMP
  for (int i = 0; i < m_cars->size(); i++)
  {
    m_carOptionsWidgets[i]->show();
  }
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

  //delete all the car options widgets TEMP until the parent system is used
  for (auto carWidget : m_carOptionsWidgets)
  {
    delete carWidget;
  }
}
