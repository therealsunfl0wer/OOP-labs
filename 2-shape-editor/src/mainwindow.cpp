#include "mainwindow.h"
#include "canvaswidget.h"
#include <QActionGroup>
#include <QLabel>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) {
  setWindowTitle("Лабораторна робота №2, варіант 10");
  setMinimumSize(640, 480);
  CanvasWidget *canvas = new CanvasWidget(this);
  setCentralWidget(canvas);
  QLabel *modeLabel = new QLabel(this);
  statusBar()->addPermanentWidget(modeLabel);

  QMenu *fileMenu = menuBar()->addMenu("Файл");
  fileMenu->addAction("Вихід", this, &QWidget::close);

  QMenu *objectsMenu = menuBar()->addMenu("Об'єкти");
  QActionGroup *objectsMenuActionGroup = new QActionGroup(objectsMenu);
  objectsMenuActionGroup->setExclusive(true);

  QAction *pointAction =
      objectsMenu->addAction("Точка", this, [this, modeLabel, canvas]() {
        canvas->selectPointMode();
        modeLabel->setText("Вибрано об'єкт: Точка");
      });
  pointAction->setCheckable(true);
  objectsMenuActionGroup->addAction(pointAction);
  QAction *lineAction =
      objectsMenu->addAction("Лінія", this, [this, modeLabel, canvas]() {
        canvas->selectLineMode();
        modeLabel->setText("Вибрано об'єкт: Лінія");
      });
  lineAction->setCheckable(true);
  objectsMenuActionGroup->addAction(lineAction);
  QAction *rectangleAction =
      objectsMenu->addAction("Прямокутник", this, [this, modeLabel, canvas]() {
        canvas->selectRectMode();
        modeLabel->setText("Вибрано об'єкт: Прямокутник");
      });
  rectangleAction->setCheckable(true);
  objectsMenuActionGroup->addAction(rectangleAction);
  QAction *ellipseAction =
      objectsMenu->addAction("Еліпс", this, [this, modeLabel, canvas]() {
        canvas->selectEllipseMode();
        modeLabel->setText("Вибрано об'єкт: Еліпс");
      });
  ellipseAction->setCheckable(true);
  objectsMenuActionGroup->addAction(ellipseAction);

  QMenu *helpMenu = menuBar()->addMenu("Довідка");
  helpMenu->addAction("Про програму", this, [this]() {
    QMessageBox::about(this, "Про програму",
                       "Лабораторна робота №2, варіант 10");
  });

  pointAction->trigger();
  adjustSize();
}
