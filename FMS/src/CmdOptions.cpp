#include "CmdOptions.h"

extern OutputManager cout;

//debug level enum to string conversion map
const QMap<CmdOptions::DEBUG_LEVEL, QString> CmdOptions::DEBUG_STR_MAP = {
  {DEBUG_LEVEL::NO_INFO,     "No Output"},
  {DEBUG_LEVEL::ERRORS_ONLY, "Errors Only"},
  {DEBUG_LEVEL::USER_INFO,   "User Information"},
  {DEBUG_LEVEL::NO_INFO,     "Errors And Warnings"},
  {DEBUG_LEVEL::ALL_INFO,    "All Information"},
};

//cmd options default values
CmdOptions::DEBUG_LEVEL CmdOptions::verbosity = CmdOptions::DEBUG_LEVEL::USER_INFO;
QString CmdOptions::configPath = "";

OutputManager& operator<<(OutputManager& out, CmdOptions::DEBUG_LEVEL toPrint)
{
  out << CmdOptions::DEBUG_STR_MAP.value(toPrint, "Invalid");
  return out;
}
