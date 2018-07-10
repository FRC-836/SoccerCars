#include "MatchOptions.h"

//TODO: switch back to 150, temporarily 10 for ease of testing quickly
unsigned int MatchOptions::m_seconds = 150; //default length of a match
unsigned int MatchOptions::m_scoreLimit = 15; //default score needed to win a match
unsigned int MatchOptions::m_numberOfTeams = 2; //default number of teams
unsigned int MatchOptions::m_carsPerTeam = 3; //default number of cars on each team
