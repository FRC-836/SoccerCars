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
  if (m_carOptions->getBypassed())
  {
    m_ui->cmbEnabled->setCurrentIndex(static_cast<int>(CmbEnableOptions::BYPASSED));
  } //end  if (m_carOptions->getBypassed())
  else
  {
    m_ui->cmbEnabled->setCurrentIndex(static_cast<int>(CmbEnableOptions::PLAYING));
  } //end  else

  //setup the controller combobox
  int numControllers = MatchOptions::m_carsPerTeam * MatchOptions::m_numberOfTeams;
  for (int i = 0; i < numControllers; i++)
  {
    m_ui->cmbController->addItem("Controller " + QString::number(i + 1));
  } //end  for (int i = 0; i < numControllers; i++

  //set the text for the labels
  m_ui->lblTeamName->setText("Team " + QString::number(m_carOptions->getTeam() + 1));
  m_ui->lblCarName->setText("Car " + m_carOptions->getName());

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

  //determine new team number and check if its too low
  //don't need to check if too high because team is decreasing
  int newTeam = m_carOptions->getTeam() - 1;
  if (newTeam < 0)
  {
    if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_ONLY)
    {
      cout << "ERROR: CarOptionsWidget: attempting to set team too low" << endl;
    } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_ONLY)
  } //end  if (newTeam < 0)
  else
  {
    //set new team and update label
    m_carOptions->setTeam(newTeam);
    m_ui->lblTeamName->setText("Team " + QString::number(newTeam + 1));

    //emit the team chaged signal
    if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
    {
      cout << "INFO: CarOptionsWidget: emitting team change signal with new team " << newTeam << endl;
    } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
    emit teamChange(newTeam);
  } //end  else
}
void CarOptionsWidget::btnUpTeamClickHandler()
{
  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    cout << "INFO: CarOptionsWidget: up team button clicked" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)

  //determine new team number and check if its too high
  //don't need to check if too low because team is increasing`
  int newTeam = m_carOptions->getTeam() + 1;
  if (newTeam >= MatchOptions::m_numberOfTeams)
  {
    if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_ONLY)
    {
      cout << "ERROR: CarOptionsWidget: Attempting to set team too high" << endl;
    } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_ONLY)
  } //end  if (newTeam >= MatchOptions::m_numberOfTeams)
  else
  {
    //set new team and update label
    m_carOptions->setTeam(newTeam);
    m_ui->lblTeamName->setText("Team " + QString::number(newTeam + 1));

    //emit the team chaged signal
    if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
    {
      cout << "INFO: CarOptionsWidget: emitting team change signal with new team " << newTeam << endl;
    } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
    emit teamChange(newTeam);
  } //end  else
}
void CarOptionsWidget::btnIndicateClickHandler()
{
  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    cout << "INFO: CarOptionsWidget: indicate button clicked" << endl;
    cout << "INFO: CarOptionsWidget: sending indicate signal" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  emit indicateRequested();
}
void CarOptionsWidget::cmbControllerValChangeHandler(int newIndex)
{
  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    cout << "INFO: CarOptionsWidget: controller combo box value changed" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
}
void CarOptionsWidget::cmbBypassValChangeHandler(int newIndex)
{
  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    cout << "INFO: CarOptionsWidget: car enable status combo box value changed" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)

  switch (static_cast<CmbEnableOptions>(newIndex))
  {
    case CmbEnableOptions::BYPASSED:
      m_carOptions->bypass();
      if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
      {
        cout << "INFO: CarOptionsWidget: sending bypass signal with bypass = true" << endl;
      } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
      emit bypassStateChanged(true);
      break;
    case CmbEnableOptions::PLAYING:
      m_carOptions->enable();
      if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
      {
        cout << "INFO: CarOptionsWidget: sending bypass signal with bypass = false" << endl;
      } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
      emit bypassStateChanged(false);
      break;
  }
}
