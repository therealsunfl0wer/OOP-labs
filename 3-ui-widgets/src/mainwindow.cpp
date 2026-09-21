#include "mainwindow.h"
#include "canvaswidget.h"
#include <QActionGroup>
#include <QMenuBar>
#include <QMessageBox>
#include <QToolBar>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  setMinimumSize(640, 480);

  CanvasWidget *canvas = new CanvasWidget(this);
  setCentralWidget(canvas);

  QMenu *fileMenu = menuBar()->addMenu("Файл");
  fileMenu->addAction("Вихід", this, &QWidget::close);

  QMenu *helpMenu = menuBar()->addMenu("Довідка");
  helpMenu->addAction("Про програму", this, [this]() {
    QMessageBox::about(this, "Про програму",
                       "Лабораторна робота №3, варіант 10");
  });

  QToolBar *toolBar = addToolBar("Об'єкти");
  QActionGroup *toolBarActionGroup = new QActionGroup(toolBar);
  toolBarActionGroup->setExclusive(true);

  QAction *pointAction = toolBar->addAction("Точка", this, [this, canvas]() {
    canvas->selectPointMode();
    setWindowTitle("Вибрано об'єкт: Точка");
  });
  pointAction->setCheckable(true);
  toolBarActionGroup->addAction(pointAction);
  QAction *lineAction = toolBar->addAction("Лінія", this, [this, canvas]() {
    canvas->selectLineMode();
    setWindowTitle("Вибрано об'єкт: Лінія");
  });
  lineAction->setCheckable(true);
  toolBarActionGroup->addAction(lineAction);
  QAction *rectangleAction =
      toolBar->addAction("Прямокутник", this, [this, canvas]() {
        canvas->selectRectMode();
        setWindowTitle("Вибрано об'єкт: Прямокутник");
      });
  rectangleAction->setCheckable(true);
  toolBarActionGroup->addAction(rectangleAction);
  QAction *ellipseAction = toolBar->addAction("Еліпс", this, [this, canvas]() {
    canvas->selectEllipseMode();
    setWindowTitle("Вибрано об'єкт: Еліпс");
  });
  ellipseAction->setCheckable(true);
  toolBarActionGroup->addAction(ellipseAction);

  pointAction->trigger();
  adjustSize();
}
