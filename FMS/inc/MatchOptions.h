#ifndef SOCCER_CARS_FMS_MATCH_OPTIONS_H
#define SOCCER_CARS_FMS_MATCH_OPTIONS_H

class MatchOptions
{
public:
  //values
  static unsigned int m_seconds;
  static unsigned int m_scoreLimit;
};

bool operator==(const MatchOptions& lhs, const MatchOptions& rhs);
bool operator!=(const MatchOptions& lhs, const MatchOptions& rhs);

#endif