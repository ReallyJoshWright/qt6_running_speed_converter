#pragma once

#include <QWidget>
#include <QMainWindow>
#include <QGridLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QMenu>
#include <QMenuBar>
#include <QCloseEvent>
#include <QCoreApplication>
#include <QRegularExpression>
#include <QMessageBox>
#include <QDebug>
#include <cmath>

struct MinSec {
  int minutes;
  int seconds;
};

class RunSpeedConverter : public QMainWindow {
  public:
    RunSpeedConverter(QWidget* parent = nullptr);
    ~RunSpeedConverter();
    MinSec get_min_per_mile(QString);
    double get_mph(QString);
    bool verify_input_mph(QString);
    bool verify_input_min_per_mile(QString);

  public slots:
    void select();
    void calculate();
    void reset();
    void closeEvent(QCloseEvent* event);

  private:
    QWidget* central_widget;
    QGridLayout* layout;
    QVBoxLayout* vertical_layout;
    QHBoxLayout* horizontal_layout;
    QFormLayout* form_layout;
    QLineEdit* min_per_mile_le;
    QLineEdit* mph_le;
    QLineEdit* result_le;
    QLabel* min_per_mile_lb;
    QLabel* mph_lb;
    QLabel* result_lb;
    QPushButton* calculate_pb;
    QPushButton* reset_pb;
    QAction* quit_action;
    QMenu* file;
    QSpacerItem* form_spacer;
    QSpacerItem* horizontal_spacer;
    QMessageBox* warning_msg;
};
