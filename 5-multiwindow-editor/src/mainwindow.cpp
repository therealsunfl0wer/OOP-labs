#include "mainwindow.h"
#include "canvaswidget.h"
#include "shape.h"
#include <QActionGroup>
#include <QMenuBar>
#include <QMessageBox>
#include <QSvgRenderer>
#include <QToolBar>
#include <QVBoxLayout>

// This helper does not handle dynamic theme switching,
// so it only picks the color for icons when the program has started
const QIcon tintedIcon(const QString &svgPath, const QColor &color,
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

  static const ShapeFactory &factory = ShapeFactory::instance();
  static const QColor iconColor = palette().color(QPalette::WindowText);

  CanvasWidget *canvas = new CanvasWidget(this);
  setCentralWidget(canvas);


  QMenu *fileMenu = menuBar()->addMenu("Файл");
  fileMenu->addAction("Вихід", this, &QWidget::close);

  QMenu *helpMenu = menuBar()->addMenu("Довідка");
  helpMenu->addAction("Про програму", this, [this]() {
    QMessageBox::about(this, "Про програму",
                       "Лабораторна робота №5, варіант 10");
  });

  QToolBar *toolBar = addToolBar("Об'єкти");
  QActionGroup *toolBarActionGroup = new QActionGroup(toolBar);
  toolBarActionGroup->setExclusive(true);

  for (const ShapeEntry &entry : factory.registry()) {

    QAction *action =
        toolBar->addAction(tintedIcon(entry.iconPath, iconColor), entry.name,
                           [this, canvas, entry]() {
                             canvas->selectShape(entry.id);
                             setWindowTitle("Вибрано об'єкт: " + entry.name);
                           });
    toolBarActionGroup->addAction(action);
  }

  if (!toolBarActionGroup->actions().isEmpty())
    toolBarActionGroup->actions().first()->trigger();

  adjustSize();
}
