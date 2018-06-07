#include "Diagnostics.h"

extern OutputManager cout;

Diagnostics::Diagnostics(QWidget* parent) :
  QWidget(parent)
{
  m_ui = new Ui_Diagnostics();
  m_ui->setupUi(this);
}
Diagnostics::~Diagnostics()
{
  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    cout << "INFO: Diagnostics: deconstructing..." << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)

  delete m_ui;
}
