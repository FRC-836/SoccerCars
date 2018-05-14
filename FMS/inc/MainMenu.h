#ifndef SOCCER_CARS_FMS_MAIN_MENU_H
#define SOCCER_CARS_FMS_MAIN_MENU_H

#include <qmainwindow.h>

#include "ui_MainMenu.h"

class MainMenu : QMainWindow
{
  Q_OBJECT

private:
  //member variables
  Ui_MainMenu* ui;

public:
  //constructors
  MainMenu();
  ~MainMenu();

signals:

public slots:

};

#endif