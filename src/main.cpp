#include <QApplication>
#include "run_speed_converter.h"

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  RunSpeedConverter window;
  window.show();
  return app.exec();
}
