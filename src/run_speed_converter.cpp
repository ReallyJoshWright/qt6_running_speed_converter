#include "run_speed_converter.h"

RunSpeedConverter::RunSpeedConverter(QWidget* parent) : QMainWindow(parent) {
  central_widget = new QWidget();
  layout = new QGridLayout();
  vertical_layout = new QVBoxLayout();
  horizontal_layout = new QHBoxLayout();
  form_layout = new QFormLayout();
  min_per_mile_le = new QLineEdit();
  mph_le = new QLineEdit();
  result_le = new QLineEdit();
  min_per_mile_lb = new QLabel("Enter min per mile");
  mph_lb = new QLabel("Enter mph");
  result_lb = new QLabel();
  calculate_pb = new QPushButton("Calculate");
  reset_pb = new QPushButton("Reset");
  quit_action = new QAction("Quit");
  file = menuBar()->addMenu("File");
  form_spacer = new QSpacerItem(0, 350,QSizePolicy::Fixed, QSizePolicy::Maximum);
  horizontal_spacer = new QSpacerItem(280, 0,QSizePolicy::Maximum, QSizePolicy::Fixed);
  warning_msg = new QMessageBox();

  central_widget->setLayout(layout);
  setCentralWidget(central_widget);
  resize(800, 600);
  setWindowTitle("Run Speed Converter");

  min_per_mile_le->setPlaceholderText("8:35");
  min_per_mile_le->setClearButtonEnabled(true);
  mph_le->setPlaceholderText("6.4");
  mph_le->setClearButtonEnabled(true);
  result_le->setReadOnly(true);
  file->addAction(quit_action);
  warning_msg->setText("The input format is wrong");

  horizontal_layout->addSpacerItem(horizontal_spacer);
  horizontal_layout->addWidget(calculate_pb);
  horizontal_layout->addWidget(reset_pb);

  vertical_layout->addLayout(form_layout);

  form_layout->insertRow(0, min_per_mile_lb, min_per_mile_le);
  form_layout->insertRow(1, mph_lb, mph_le);
  form_layout->setItem(2, QFormLayout::SpanningRole, form_spacer);
  form_layout->insertRow(3, result_lb, result_le);

  layout->addLayout(vertical_layout, 0, 0);
  layout->addLayout(horizontal_layout, 1, 0);

  // Signals
  connect(min_per_mile_le, &QLineEdit::textChanged, this, &RunSpeedConverter::select);
  connect(mph_le, &QLineEdit::textChanged, this, &RunSpeedConverter::select);
  connect(calculate_pb, &QPushButton::clicked, this, &RunSpeedConverter::calculate);
  connect(reset_pb, &QPushButton::clicked, this, &RunSpeedConverter::reset);
  connect(quit_action, &QAction::triggered, this, &QCoreApplication::quit);
}

RunSpeedConverter::~RunSpeedConverter() {
}

void RunSpeedConverter::select() {
  if (min_per_mile_le == sender()) {
    mph_le->clear();
  }
  else if (mph_le == sender()) {
    min_per_mile_le->clear();
  }
}

void RunSpeedConverter::calculate() {
  QString min_per_mile = min_per_mile_le->text();
  QString mph = mph_le->text();
  if (min_per_mile != "") {
    bool verify = verify_input_min_per_mile(min_per_mile);
    if (verify) {
      double result = get_mph(min_per_mile);
      QString result_str = QString::number(result);
      result_le->setText(result_str);
      result_lb->setText("mph");
    }
    else {
      return;
    }
  }
  else if (mph != "") {
    bool verify = verify_input_mph(mph);
    if (verify) {
      MinSec minsec = get_min_per_mile(mph);
      QString min = QString::number(minsec.minutes);
      QString sec = QString::number(minsec.seconds);
      if (sec.length() == 1) {
        sec = "0" + sec;
      }
      QString result = min + ":" + sec;
      result_le->setText(result);
      result_lb->setText("min per mile");
    }
    else {
      return;
    }
  }
  else {
    return;
  }
}

bool RunSpeedConverter::verify_input_min_per_mile(QString min_per_mile) {
  QRegularExpression re("\\w+\\:\\w+");
  QRegularExpressionMatch match = re.match(min_per_mile);
  bool has_match = match.hasMatch();
  if (!has_match) {
    warning_msg->exec();
    reset();
    return false;
  }
  else {
    QList<QString> time = min_per_mile.split(":");
    int min = time[0].toInt();
    int sec = time[1].toInt();
    if (min > 60) {
      warning_msg->exec();
      reset();
      return false;
    }
    else if (sec > 60) {
      warning_msg->exec();
      reset();
      return false;
    }
    else {
      return true;
    }
  }
}

bool RunSpeedConverter::verify_input_mph(QString mph) {
  bool ok(false);
  double mph_double = mph.toDouble(&ok);
  if (ok) {
    qDebug() << mph_double;
    return true;
  }
  else {
    warning_msg->exec();
    reset();
    return false;
  }
}

double RunSpeedConverter::get_mph(QString min_per_mile) {
  QList<QString> time = min_per_mile.split(":");
  int min = time[0].toInt();
  int sec = time[1].toInt();
  min = min + (sec / 60);
  double mph = 60.0 / min;
  mph = std::ceil(mph * 100.0) / 100.0;
  return mph;
}

MinSec RunSpeedConverter::get_min_per_mile(QString mph) {
  double min_per_mile = 60 / mph.toDouble();
  int min = min_per_mile;
  double min_to_convert = min_per_mile - min;
  double sec = min_to_convert * 60;
  sec = std::ceil(sec * 100.0) / 100.0;
  MinSec minsec;
  minsec.minutes = min;
  minsec.seconds = sec;
  return minsec;
}

void RunSpeedConverter::reset() {
  min_per_mile_le->clear();
  mph_le->clear();
  result_le->clear();
  result_lb->clear();
  min_per_mile_le->setFocus();
}

void RunSpeedConverter::closeEvent(QCloseEvent* event) {
  event->accept();
}
