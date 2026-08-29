#include "mainwindow.h"
#include "canvaswidget.h"
#include <QActionGroup>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) {
  setWindowTitle("Лабораторна робота №2, варіант 10");
  setMinimumSize(640, 480);

  CanvasWidget *canvas = new CanvasWidget(this);
  setCentralWidget(canvas);

  QMenu *fileMenu = menuBar()->addMenu("Файл");
  fileMenu->addAction("Вихід", this, &QWidget::close);

  QMenu *objectsMenu = menuBar()->addMenu("Об'єкти");
  QActionGroup *objectsMenuActionGroup = new QActionGroup(objectsMenu);
  objectsMenuActionGroup->setExclusive(true);

  QAction *pointAction =
      objectsMenu->addAction("Точка", this, [this, canvas]() {
        canvas->selectPointMode();
        statusBar()->showMessage("Вибрано об'єкт: Точка");
      });
  pointAction->setCheckable(true);
  objectsMenuActionGroup->addAction(pointAction);
  QAction *lineAction = objectsMenu->addAction("Лінія", this, [this, canvas]() {
    canvas->selectLineMode();
    statusBar()->showMessage("Вибрано об'єкт: Лінія");
  });
  lineAction->setCheckable(true);
  objectsMenuActionGroup->addAction(lineAction);
  QAction *rectangleAction =
      objectsMenu->addAction("Прямокутник", this, [this, canvas]() {
        canvas->selectRectMode();
        statusBar()->showMessage("Вибрано об'єкт: Прямокутник");
      });
  rectangleAction->setCheckable(true);
  objectsMenuActionGroup->addAction(rectangleAction);
  QAction *ellipseAction =
      objectsMenu->addAction("Еліпс", this, [this, canvas]() {
        canvas->selectEllipseMode();
        statusBar()->showMessage("Вибрано об'єкт: Еліпс");
      });
  ellipseAction->setCheckable(true);
  objectsMenuActionGroup->addAction(ellipseAction);

  QMenu *helpMenu = menuBar()->addMenu("Довідка");
  helpMenu->addAction("Про програму", this, [this]() {
    QMessageBox::about(this, "Про програму",
                       "Лабораторна робота №2, варіант 10");
  });

  statusBar()->showMessage("Готово");
  adjustSize();
}
