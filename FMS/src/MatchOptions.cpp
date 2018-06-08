#include "MatchOptions.h"

//TODO: switch back to 150, temporarily 10 for ease of testing quickly
unsigned int MatchOptions::m_seconds = 10; //default length of a match
unsigned int MatchOptions::m_scoreLimit = 15; //default score needed to win a match

//operators
bool operator==(const MatchOptions& lhs, const MatchOptions& rhs)
{
  if (lhs.m_scoreLimit != rhs.m_scoreLimit)
  {
    return false;
  } //end  if (lhs.m_scoreLimit != rhs.m_scoreLimit)
  if (lhs.m_seconds != rhs.m_seconds)
  {
    return false;
  } //end  if (lhs.m_seconds != rhs.m_seconds)
  return true;
}
bool operator!=(const MatchOptions& lhs, const MatchOptions& rhs)
{
  return !(lhs == rhs);
}