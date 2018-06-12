#include "CarOptionsWidget.h"

extern OutputManager cout;

CarOptionsWidget::CarOptionsWidget(QWidget* parent = nullptr) :
  QWidget(parent)
{
  m_ui = new Ui_CarOptionsWidget;
  m_ui->setupUi(this);
}
CarOptionsWidget::~CarOptionsWidget()
{
  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    cout << "INFO: CarOptionsWidget: deconstructing..." << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)

  delete m_ui;
}
