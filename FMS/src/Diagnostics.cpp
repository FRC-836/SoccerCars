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
  delete m_ui;
}
