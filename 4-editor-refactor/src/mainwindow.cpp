#include "mainwindow.h"
#include "canvaswidget.h"
#include <QActionGroup>
#include <QMenuBar>
#include <QMessageBox>
#include <QSvgRenderer>
#include <QToolBar>
#include <QVBoxLayout>

// This helper does not handle dynamic theme switching,
// so it only picks the color for icons when the program has started
QIcon tintedIcon(const QString &svgPath, const QColor &color,
                 QSize size = QSize(24, 24)) {
  QPixmap pixmap(size);
  pixmap.fill(Qt::transparent);

  QSvgRenderer renderer(svgPath);
  QPainter painter(&pixmap);
  renderer.render(&painter);

  painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
  painter.fillRect(pixmap.rect(), color);
  painter.end();

  return QIcon(pixmap);
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  setMinimumSize(640, 480);

  CanvasWidget *canvas = new CanvasWidget(this);
  setCentralWidget(canvas);

  static const QColor iconColor = palette().color(QPalette::WindowText);

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

  QAction *pointAction = toolBar->addAction(
      tintedIcon(":point", iconColor), "Точка", this, [this, canvas]() {
        canvas->selectPoint();
        setWindowTitle("Вибрано об'єкт: Точка");
      });
  pointAction->setCheckable(true);
  toolBarActionGroup->addAction(pointAction);
  QAction *lineAction = toolBar->addAction(
      tintedIcon(":line", iconColor), "Лінія", this, [this, canvas]() {
        canvas->selectLine();
        setWindowTitle("Вибрано об'єкт: Лінія");
      });
  lineAction->setCheckable(true);
  toolBarActionGroup->addAction(lineAction);
  QAction *rectangleAction =
      toolBar->addAction(tintedIcon(":rectangle", iconColor), "Прямокутник",
                         this, [this, canvas]() {
                           canvas->selectRect();
                           setWindowTitle("Вибрано об'єкт: Прямокутник");
                         });
  rectangleAction->setCheckable(true);
  toolBarActionGroup->addAction(rectangleAction);
  QAction *ellipseAction = toolBar->addAction(
      tintedIcon(":ellipse", iconColor), "Еліпс", this, [this, canvas]() {
        canvas->selectEllipse();
        setWindowTitle("Вибрано об'єкт: Еліпс");
      });
  ellipseAction->setCheckable(true);
  toolBarActionGroup->addAction(ellipseAction);
  QAction *lineOOAction =
      toolBar->addAction(tintedIcon(":o-o-line", iconColor),"Лінія з кружечками", this, [this, canvas]() {
        canvas->selectLineOO();
        setWindowTitle("Вибрано об'єкт: Лінія з кружечками");
      });
  lineOOAction->setCheckable(true);
  toolBarActionGroup->addAction(lineOOAction);
  QAction *cubeAction = toolBar->addAction(tintedIcon(":cuboid", iconColor),"Куб", this, [this, canvas]() {
    canvas->selectCube();
    setWindowTitle("Вибрано об'єкт: Куб");
  });
  cubeAction->setCheckable(true);
  toolBarActionGroup->addAction(cubeAction);

  pointAction->trigger();
  adjustSize();
}
