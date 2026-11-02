#include "canvaswidget.h"
#include "shape.h"
#include "shapefactory.h"
#include <QMouseEvent>
#include <QPainter>
#include <utility>

void CanvasWidget::selectShape(const QString &id) {
  std::unique_ptr<Shape> shape = ShapeFactory::instance().create(id);
  if (!shape) {
    qWarning(
        "ShapeFactory::instance().create(id): shape not found in registry");
    return;
  }
  editor->setShape(std::move(shape));
}

CanvasWidget::CanvasWidget(QWidget *parent) : QWidget(parent) {
  setMinimumSize(600, 400);
  setAutoFillBackground(true);
  setPalette(QPalette(QPalette::Window, Qt::white));
  editor->subscribe([this] { update(); });
}

void CanvasWidget::paintEvent(QPaintEvent *) {
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);
  editor->onPaint(painter);
}

void CanvasWidget::mousePressEvent(QMouseEvent *event) {
  switch (event->button()) {
  case Qt::LeftButton:
    editor->onLeftButtonPress(event->pos());
    break;
  case Qt::RightButton:
    break;
  default:
    break;
  }
}

void CanvasWidget::mouseMoveEvent(QMouseEvent *event) {
  editor->onMouseMove(event->pos());
}

void CanvasWidget::mouseReleaseEvent(QMouseEvent *event) {
  switch (event->button()) {
  case Qt::LeftButton:
    editor->onLeftButtonRelease(event->pos());
    break;
  case Qt::RightButton:
    break;
  default:
    break;
  }
}
