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
}
void MatchSettings::btnCancelClickHandler()
{
}
void MatchSettings::btnDefaultClickhandler()
{
}
