#include "MatchSettings.h"

extern OutputManager cout;

//private functions
void MatchSettings::makeConnections()
{
  connect(m_ui->btnCancel, &QPushButton::clicked, this, &MatchSettings::btnCancelClickHandler);
  connect(m_ui->btnDefault, &QPushButton::clicked, this, &MatchSettings::btnDefaultClickhandler);
  connect(m_ui->btnSave, &QPushButton::clicked, this, &MatchSettings::btnSaveClickHandler);
}
void MatchSettings::itemToGui(std::shared_ptr<MatchOptions> item)
{
  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    cout << "INFO: MatchSettings: recieved call to update the GUI values" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)

  if (item != nullptr)
  {
    m_ui->spnMatchLength->setValue(item->m_seconds);
    m_ui->spnScoreLimit->setValue(item->m_scoreLimit);
    if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
    {
      cout << "INFO: MatchSettings: updated gui to represent the values specified" << endl;
    } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  } //end  if (item != nullptr)
  else
  {
    if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_ONLY)
    {
      cout << "ERROR: MatchSettings: Can't update GUI based on a null item" << endl;
    } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_ONLY)
  } //end  else
}
std::shared_ptr<MatchOptions> MatchSettings::guiToItem()
{
  return nullptr;
}

//constructors
MatchSettings::MatchSettings(std::shared_ptr<MatchOptions> options, QWidget* parent) :
  QWidget(parent)
{
  setAttribute(Qt::WA_DeleteOnClose);

  m_ui = new Ui_MatchSettings();
  m_ui->setupUi(this);

  //if the options passed in is a nullptr, disable the GUI
  if (options == nullptr)
  {
    if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_AND_WARNINGS)
    {
      cout << "WARNING: MatchSettings: window called without any settings to edit." << endl;
      cout << "\tDisabling user input because not sure what to do" << endl;
    } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_AND_WARNINGS)
    m_ui->spnMatchLength->setEnabled(false);
    m_ui->spnScoreLimit->setEnabled(false);
  } //end  if (options == nullptr)

  m_matchSettings = options;
  itemToGui(options);

  makeConnections();
}
MatchSettings::~MatchSettings()
{
  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    cout << "INFO: MatchSettings: deconstructing..." << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)

  delete m_ui;
}

//public slots
void MatchSettings::btnSaveClickHandler()
{
  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    cout << "INFO: MatchSettings: save button clicked" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  m_matchSettings = guiToItem();
}
void MatchSettings::btnCancelClickHandler()
{
  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    cout << "INFO: MatchSettings: cancel button clicked" << endl;
    cout << "INFO: MatchSettings: Closing window without saving settings" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  close();
}
void MatchSettings::btnDefaultClickhandler()
{
  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    cout << "INFO: MatchSettings: return to default button clicked" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::USER_INFO)
  {
    cout << "INFO: MatchSettings: Returning the GUI to the most recently saved settings" << endl;
  }
  itemToGui(m_matchSettings);
}
