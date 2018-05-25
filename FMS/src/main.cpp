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

  QCommandLineParser parser;
  if (!parseCmd(parser))
  {
    parser.showHelp(1);
  } //end  if (!parseCmd(parser))

  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    cout << "INFO: main: verbosity   = " << CmdOptions::verbosity << endl;;
    cout << "INFO: main: config file = " << CmdOptions::configPath << endl;;
  } //end  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)

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
  parser.addOptions({ { {"v", "verbosity"}, "Verbosit of the info displayed", "debugLevel", "2"},
                      { {"c", "config"}, "Location of the config file", "configPath", ""} });

  //--------------------------------------------------
  //parse the arguments into structure
  //--------------------------------------------------
  parser.process(QCoreApplication::arguments());
  bool convesionSuccess;

  //handle debug level processing
  int debugLevel = parser.value("verbosity").toInt(&convesionSuccess);
  if (convesionSuccess)
  {
    debugLevel = (debugLevel < static_cast<int>(CmdOptions::DEBUG_LEVEL::NO_INFO)) ? 
                  static_cast<int>(CmdOptions::DEBUG_LEVEL::NO_INFO) : debugLevel;
    debugLevel = (debugLevel > static_cast<int>(CmdOptions::DEBUG_LEVEL::ALL_INFO)) ? 
                  static_cast<int>(CmdOptions::DEBUG_LEVEL::ALL_INFO) : debugLevel;
    CmdOptions::verbosity = static_cast<CmdOptions::DEBUG_LEVEL>(debugLevel);
  } //end  if (convesionSuccess)
  else
  {
    return false;
  } //end  else

  //handle config file path processing
  CmdOptions::configPath = parser.value("config");

    //all command args processed sucessfully
  return true;
}  //end bool parseCmd(QCommandLineParser& parser)

