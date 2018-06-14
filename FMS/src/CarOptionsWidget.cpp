#include "CarOptionsWidget.h"

extern OutputManager cout;

//private functions
void CarOptionsWidget::makeConnections()
{
}

//constructors
CarOptionsWidget::CarOptionsWidget(QWidget* parent) :
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

//public slots
void CarOptionsWidget::btnDownTeamClickHandler()
{
}
void CarOptionsWidget::btnUpTeamClickHandler()
{
}
void CarOptionsWidget::btnIndicateClickHandler()
{
}
void CarOptionsWidget::cmbControllerValChangeHandler()
{
}
void CarOptionsWidget::cmbBypassValChangeHandler()
{
}
