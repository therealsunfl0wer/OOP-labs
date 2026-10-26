#include "mainwindow.h"
#include "shape.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  MainWindow window;
  window.show();

  return app.exec();
}
