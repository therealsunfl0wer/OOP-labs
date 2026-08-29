#include "canvaswidget.h"
#include <QMouseEvent>
#include <QPainter>

CanvasWidget::CanvasWidget(QWidget *parent) : QWidget(parent) {
  setMinimumSize(600, 400);
}

void CanvasWidget::selectPointMode() { editor.StartPointEditor(); }
void CanvasWidget::selectLineMode() { editor.StartLineEditor(); }
void CanvasWidget::selectRectMode() { editor.StartRectEditor(); }
void CanvasWidget::selectEllipseMode() { editor.StartEllipseEditor(); }

void CanvasWidget::paintEvent(QPaintEvent *) {
  QPainter painter(this);
  editor.OnPaint(painter);
}

void CanvasWidget::mousePressEvent(QMouseEvent *event) {
  editor.OnLBdown(event->pos());
  update();
}

void CanvasWidget::mouseMoveEvent(QMouseEvent *event) {
  editor.OnMouseMove(event->pos());
  update();
}

void CanvasWidget::mouseReleaseEvent(QMouseEvent *event) {
  editor.OnLBup(event->pos());
  update();
}
