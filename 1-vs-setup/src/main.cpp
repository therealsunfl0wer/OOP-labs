#include "mainwindow.h"
#include <QApplication>
#include <QStyle>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  app.setWindowIcon(
      QApplication::style()->standardIcon(QStyle::SP_ComputerIcon));
  MainWindow window;
  window.show();

  return app.exec();
}
