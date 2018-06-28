#ifndef SOCCER_CARS_FMS_CAR_OPTIONS_WIDGET_H
#define SOCCER_CARS_FMS_CAR_OPTIONS_WIDGET_H

#include <memory>

#include <qwidget.h>
#include <qmap.h>
#include <qtablewidget.h>

#include "ui_CarOptionsWidget.h"
#include "OutputManager.h"
#include "CmdOptions.h"
#include "MatchOptions.h"
#include "CarOptions.h"

class CarOptionsWidget : public QWidget, public QTableWidgetItem
{
  Q_OBJECT
private:
  //enums for combo box selection options
  enum class CmbEnableOptions
  {
    PLAYING,
    BYPASSED
  };
  static const QMap<CmbEnableOptions, QString> CMB_ENABLE_STR;

  //member data
  Ui_CarOptionsWidget* m_ui;
  std::shared_ptr<CarOptions> m_carOptions;

  //private functions
  void makeConnections();

public:
  //constructors
  CarOptionsWidget(std::shared_ptr<CarOptions> carOptions, QWidget* parent = nullptr);
  ~CarOptionsWidget();

  //getters
  const CarOptions& getCar() const;

signals:
  /**
   * emitted when the user has clicked a button to change which team this car
   * is on.
   *
   * @param newTeam: the number of the team the car is being assigned to
   */
  void teamChange(int newTeam, int oldTeam);
  /**
   * emitted when the user changes wether or not this car is bypassed
   *
   * @param bypassed: true if the car is now bypassed, false otherwise
   */
  void bypassStateChanged(bool bypassed);
  /**
   * emitted when the user chnages which controller is associated with this car
   *
   * @param newController: number of the controller now assigned to this car
   */
  void controllerChanged(int newController, int oldController);
  /**
   * emitted when the user presses the "indicate" button, requesting the car
   * enter the state where it is identifiable. Possibly by lighting up some
   * lights or something
   */
  void indicateRequested();

public slots:
  void btnDownTeamClickHandler();
  void btnUpTeamClickHandler();
  void btnIndicateClickHandler();
  void cmbControllerValChangeHandler(int newIndex);
  void cmbBypassValChangeHandler(int newIndex);
  
};

#endif