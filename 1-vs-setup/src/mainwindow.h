#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QObject>

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow();

private:
  QLabel *label;
};

#endif
