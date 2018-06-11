#include "MatchSettings.h"

extern OutputManager cout;

//private functions
void MatchSettings::makeConnections()
{
  connect(m_ui->btnCancel, &QPushButton::clicked, this, &MatchSettings::btnCancelClickHandler);
  connect(m_ui->btnDefault, &QPushButton::clicked, this, &MatchSettings::btnDefaultClickhandler);
  connect(m_ui->btnSave, &QPushButton::clicked, this, &MatchSettings::btnSaveClickHandler);
}
void MatchSettings::itemToGui()
{
  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    cout << "INFO: MatchSettings: recieved call to update the GUI values" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)

  m_ui->spnMatchLength->setValue(MatchOptions::m_seconds);
  m_ui->spnScoreLimit->setValue(MatchOptions::m_scoreLimit);
  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    cout << "INFO: MatchSettings: updated gui to represent the values specified" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
}
void MatchSettings::guiToItem()
{
  MatchOptions::m_scoreLimit = m_ui->spnScoreLimit->value();
  MatchOptions::m_seconds = m_ui->spnMatchLength->value();
  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::USER_INFO)
  {
    cout << "INFO: Match Settings: Saved match settings" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
}
bool MatchSettings::unsavedChanges()
{
  if (MatchOptions::m_scoreLimit != m_ui->spnScoreLimit->value())
  {
    return true;
  }
  if (MatchOptions::m_seconds != m_ui->spnMatchLength->value())
  {
    return true;
  }
  return false;
}

//event handlers
void MatchSettings::closeEvent(QCloseEvent * e)
{
  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    cout << "INFO: MainMenu: handling close event" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)

  int msgBoxSelection = QMessageBox::Discard; //if there aren't unsaved changes close like normal
  if (unsavedChanges())
  {
    if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_AND_WARNINGS)
    {
      cout << "WARNING: MatchSettings: attempting to close with unsaved changes" << endl;
    } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ERRORS_AND_WARNINGS)
    QMessageBox msgBox(this);
    msgBox.setText("There are unsaved changes");
    msgBox.setInformativeText("Would you like to save changes?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    msgBoxSelection = msgBox.exec();
  } //end  if (m_matchRunning)

  switch (msgBoxSelection)
  {
    case QMessageBox::Save:
      guiToItem();
      //intentional fallthrough
    case QMessageBox::Discard:
      e->accept();
      QWidget::closeEvent(e);
      break;
    case QMessageBox::Cancel:
      //reject the event, not ready to close yet
      if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
      {
        cout << "INFO: MatchSettings: canceling close event" << endl;
      } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
      e->ignore();
      break;
  } //end  switch (msgBoxSelection)
}

//constructors
MatchSettings::MatchSettings(QWidget* parent) :
  QWidget(parent)
{
  setAttribute(Qt::WA_DeleteOnClose);

  m_ui = new Ui_MatchSettings();
  m_ui->setupUi(this);

  itemToGui();

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
  guiToItem();
  close();
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
  itemToGui();
}
