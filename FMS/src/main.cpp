#include <iostream>

#include <qapplication.h>
#include <qcommandlineparser.h>

#include "MainMenu.h"
#include "OutputManager.h"
#include "CmdOptions.h"

OutputManager cout(stdout);

bool parseCmd(QCommandLineParser& parser);

int main(int argc, char** argv)
{
  QApplication app(argc, argv);

  MainMenu mainMenu;
  mainMenu.show();

  return app.exec();
}
bool parseCmd(QCommandLineParser& parser)
{
  //--------------------------------------------------
  //setup the cmd parser
  //--------------------------------------------------
  parser.addHelpOption();
  parser.setApplicationDescription("Used to create and modify QCP projects");

  //debug level option
  QCommandLineOption debugOption({ "v", "verbosity" }, "Verbosity of the info printed",
                                 "debugLevel", "2");
  parser.addOption(debugOption);

  //--------------------------------------------------
  //parse the arguments into structure
  //--------------------------------------------------
  parser.process(QCoreApplication::arguments());
  bool convesionSuccess;

  //handle debug level processing
  int debugLevel = parser.value("verbosity").toInt(&convesionSuccess);
  if (convesionSuccess)
  {
  } //end  if (convesionSuccess)
  else
  {
    return false;
  } //end  else

    //all command args processed sucessfully
  return true;
}  //end bool parseCmd(QCommandLineParser& parser)

