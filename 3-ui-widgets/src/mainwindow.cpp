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

  static const QColor iconColor = palette().color(QPalette::WindowText);

  QAction *pointAction = toolBar->addAction(
      tintedIcon(":point", iconColor), "Точка", this, [this, canvas]() {
        canvas->selectPointMode();
        setWindowTitle("Вибрано об'єкт: Точка");
      });
  pointAction->setCheckable(true);
  toolBarActionGroup->addAction(pointAction);
  QAction *lineAction = toolBar->addAction(
      tintedIcon(":line", iconColor), "Лінія", this, [this, canvas]() {
        canvas->selectLineMode();
        setWindowTitle("Вибрано об'єкт: Лінія");
      });
  lineAction->setCheckable(true);
  toolBarActionGroup->addAction(lineAction);
  QAction *rectangleAction =
      toolBar->addAction(tintedIcon(":rectangle", iconColor), "Прямокутник",
                         this, [this, canvas]() {
                           canvas->selectRectMode();
                           setWindowTitle("Вибрано об'єкт: Прямокутник");
                         });
  rectangleAction->setCheckable(true);
  toolBarActionGroup->addAction(rectangleAction);
  QAction *ellipseAction = toolBar->addAction(
      tintedIcon(":ellipse", iconColor), "Еліпс", this, [this, canvas]() {
        canvas->selectEllipseMode();
        setWindowTitle("Вибрано об'єкт: Еліпс");
      });
  ellipseAction->setCheckable(true);
  toolBarActionGroup->addAction(ellipseAction);

  pointAction->trigger();
  adjustSize();
}
