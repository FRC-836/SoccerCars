#include "MatchSettings.h"

extern OutputManager cout;

//private functions
void MatchSettings::itemToGui(std::shared_ptr<MatchOptions> item)
{
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

  itemToGui(options);
}
MatchSettings::~MatchSettings()
{
  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    cout << "INFO: MatchSettings: deconstructing..." << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)

  delete m_ui;
}
