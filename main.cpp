#include <QApplication>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "socoban.hpp"

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);

  AppSettings::instance();

  Socoban app;
  app.setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
  app.setFixedSize(800, 600);
  app.show();

  return a.exec();
  return 0;
}
