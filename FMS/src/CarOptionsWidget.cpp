#include "CarOptionsWidget.h"

extern OutputManager cout;

//UI helper data
const QMap<CarOptionsWidget::CmbEnableOptions, QString> CarOptionsWidget::CMB_ENABLE_STR = {
  {CmbEnableOptions::PLAYING,  "Playing"},
  {CmbEnableOptions::BYPASSED, "Bypassed"}
};

//private functions
void CarOptionsWidget::makeConnections()
{
  connect(m_ui->btnDownTeam, &QPushButton::clicked, this, &CarOptionsWidget::btnDownTeamClickHandler);
  connect(m_ui->btnIndicate, &QPushButton::clicked, this, &CarOptionsWidget::btnIndicateClickHandler);
  connect(m_ui->btnUpTeam, &QPushButton::clicked, this, &CarOptionsWidget::btnUpTeamClickHandler);
  connect(m_ui->cmbController, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
          this, &CarOptionsWidget::cmbControllerValChangeHandler);
  connect(m_ui->cmbEnabled, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
          this, &CarOptionsWidget::cmbBypassValChangeHandler);
}

//constructors
CarOptionsWidget::CarOptionsWidget(std::shared_ptr<CarOptions> carOptions, QWidget* parent) :
  QWidget(parent)
{
  //store the car options to be modified by this widget
  m_carOptions = carOptions;

  //setup the UI
  m_ui = new Ui_CarOptionsWidget;
  m_ui->setupUi(this);

  //set the text for the buttons that need unicode characters
  m_ui->btnUpTeam->setText(QChar(0x25B2));
  m_ui->btnDownTeam->setText(QChar(0x25BC));

  //setup the enable/bypass combobox
  for (auto option : CMB_ENABLE_STR)
  {
    m_ui->cmbEnabled->addItem(option);
  } //end  for (auto option : CMB_ENABLE_STR
  m_ui->cmbEnabled->setCurrentIndex(static_cast<int>(CmbEnableOptions::PLAYING));

  //setup the controller combobox
  int numControllers = MatchOptions::m_carsPerTeam * MatchOptions::m_numberOfTeams;
  for (int i = 0; i < numControllers; i++)
  {
    m_ui->cmbController->addItem("Controller " + QString::number(i + 1));
  } //end  for (int i = 0; i < numControllers; i++

  makeConnections();
}
CarOptionsWidget::~CarOptionsWidget()
{
  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    cout << "INFO: CarOptionsWidget: deconstructing..." << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)

  delete m_ui;
}

//public slots
void CarOptionsWidget::btnDownTeamClickHandler()
{
  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    cout << "INFO: CarOptionsWidget: down team button clicked" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
}
void CarOptionsWidget::btnUpTeamClickHandler()
{
  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    cout << "INFO: CarOptionsWidget: up team button clicked" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
}
void CarOptionsWidget::btnIndicateClickHandler()
{
  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    cout << "INFO: CarOptionsWidget: indicate button clicked" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
}
void CarOptionsWidget::cmbControllerValChangeHandler()
{
  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    cout << "INFO: CarOptionsWidget: controller combo box value changed" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
}
void CarOptionsWidget::cmbBypassValChangeHandler()
{
  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    cout << "INFO: CarOptionsWidget: car enable status combo box value changed" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
}
