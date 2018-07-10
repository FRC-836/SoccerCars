#ifndef SOCCER_CARS_FMS_CONNECT_H
#define SOCCER_CARS_FMS_CONNECT_H

#include <utility>

#include <qwidget.h>
#include <qvector.h>
#include <qevent.h>
#include <qset.h>
#include <qpointer.h>
#include <qtimer.h>

#include "ui_CarSettings.h"
#include "CmdOptions.h"
#include "OutputManager.h"
#include "CarOptionsWidget.h"
#include "UsefulTypes.h"

class CarSettings : public QWidget
{
  Q_OBJECT

private:
  //member data
  Ui_CarSettings* m_ui;
  QVector<CarOptionsWidget*> m_carOptionsWidgets;
  std::shared_ptr<TeamList_t> m_cars;
  QPointer<QTimer> m_tmrOptionsCheck;;

  //private functions
  void setupCarOptionsWidgets();
  void makeConnections();

private slots:
  bool optionsGood();

protected:
  void resizeEvent(QResizeEvent* event) override;
  void closeEvent(QCloseEvent* event) override;

public:
  //constructors
  CarSettings(std::shared_ptr<TeamList_t> cars, QWidget* parent = nullptr);
  ~CarSettings();

signals:

public slots:
  void teamChangeHandler(int newTeam, int oldTeam);
  void bypassStateChangedHandler(bool bypassed);
  void controllerChangedHandler(int newController);
  void indicateRequestedHandler();

};

#endif