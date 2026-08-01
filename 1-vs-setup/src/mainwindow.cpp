#include "mainwindow.h"
#include "module1.h"
// #include "module2.h"
#include <QLabel>
#include <QMenu>
#include <QMenuBar>

MainWindow::MainWindow() {
  setWindowTitle("Лабораторна робота 1");
  setMinimumSize(400, 300);

  QLabel *label = new QLabel("Виберіть модуль для запуску", this);
  label->setAlignment(Qt::AlignCenter);
  label->setStyleSheet("font-size: 18px; font-weight: 500;");
  setCentralWidget(label);

  QMenu *menu = menuBar()->addMenu("Запустити");
  menu->addAction("Модуль 1, В1 = 2", this, [this, label]() {
    if (RunModule1(this)) {
      label->setText("Модуль 1 завершено успішно!");
    } else {
      label->setText("Модуль 1 був скасований.");
    }
  });

  // menu->addAction("Модуль 2, В2 = 3", this, [this]() { RunModule2(this); });
  adjustSize();
};
