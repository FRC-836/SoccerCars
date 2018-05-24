#ifndef SOCCER_CARS_FMS_CMD_OPTIONS_H
#define SOCCER_CARS_FMS_CMD_OPTIONS_H

#include <qmap.h>
#include <qstring.h>

#include "OutputManager.h"

class CmdOptions
{
public:
  //enums
  enum class DEBUG_LEVEL
  {
    NO_INFO,
    ERRORS_ONLY,
    USER_INFO,
    ERRORS_AND_WARNINGS,
    ALL_INFO
  };

  //enum to string translation map
  static const QMap<DEBUG_LEVEL, QString> DEBUG_STR_MAP;

  //cmd options
  static DEBUG_LEVEL verbosity;
  static QString configPath;
};

OutputManager& operator<<(OutputManager& out, CmdOptions::DEBUG_LEVEL toPrint);

#endif