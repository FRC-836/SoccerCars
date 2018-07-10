#ifndef SOCCER_CARS_FMS_USEFUL_TYPES_H
#define SOCCER_CARS_FMS_USEFUL_TYPES_H

#include <memory>

#include <qvector.h>

#include "CarOptions.h"

//types aliasses
using Team_t = QVector<std::shared_ptr<CarOptions>>;
using TeamList_t = QVector<Team_t>;

#endif