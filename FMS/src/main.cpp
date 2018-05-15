#include <iostream>

#include <qapplication.h>

#include "MainMenu.h"

int main(int argc, char** argv)
{
  QApplication app(argc, argv);

  MainMenu mainMenu;
  mainMenu.show();

  return app.exec();
}