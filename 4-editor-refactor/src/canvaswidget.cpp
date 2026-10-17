#include "canvaswidget.h"
#include "shape.h"
#include <QMouseEvent>
#include <QPainter>

CanvasWidget::CanvasWidget(QWidget *parent) : QWidget(parent) {
  setMinimumSize(600, 400);
  editor = new Editor;
}

CanvasWidget::~CanvasWidget() { delete editor; }

void CanvasWidget::selectPoint() { editor->Start(CreatePointShape()); }
void CanvasWidget::selectLine() { editor->Start(CreateLineShape()); }
void CanvasWidget::selectRect() { editor->Start(CreateRectShape()); }
void CanvasWidget::selectEllipse() { editor->Start(CreateEllipseShape()); }
void CanvasWidget::selectLineOO() { editor->Start(CreateLineOOShape()); }
void CanvasWidget::selectCube() { editor->Start(CreateCubeShape()); }

void CanvasWidget::paintEvent(QPaintEvent *) {
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);
  painter.fillRect(rect(), Qt::white);
  editor->onPaint(painter);
}

void CanvasWidget::mousePressEvent(QMouseEvent *event) {
  switch (event->button()) {
  case Qt::LeftButton:
    editor->onLBDown(event->pos());
    update();
    break;
  case Qt::RightButton:
    break;
  default:
    break;
  }
}

void CanvasWidget::mouseMoveEvent(QMouseEvent *event) {
  editor->onMouseMove(event->pos());
  update();
}

void CanvasWidget::mouseReleaseEvent(QMouseEvent *event) {
  switch (event->button()) {
  case Qt::LeftButton:
    editor->onLBUp(event->pos());
    update();
    break;
  case Qt::RightButton:
    break;
  default:
    break;
  }
}
