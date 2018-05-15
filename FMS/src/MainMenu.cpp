#include "MainMenu.h"

MainMenu::MainMenu()
{
  ui = new Ui_MainMenu();
  ui->setupUi(this);
}
MainMenu::~MainMenu()
{
  delete ui;
}
