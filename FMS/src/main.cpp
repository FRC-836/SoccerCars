#include <iostream>

#include <qapplication.h>
#include <qtextedit.h>

#include "MainMenu.h"

int main(int argc, char** argv)
{
  QApplication app(argc, argv);

  QTextEdit edit;
  edit.show();

  return app.exec();
}