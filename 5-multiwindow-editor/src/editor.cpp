#include "editor.h"
#include "shape.h"

Editor *Editor::singleton = nullptr;

Editor::~Editor() {
  delete current;
  for (Shape *s : shapes) {
    delete s;
  }
}

void Editor::setShape(Shape *selected) {
  delete current;
  current = selected;
}

void Editor::onLeftButtonPress(QPoint pt) {
  if (current == nullptr)
    return;
  current->isDrawing = true;

  xstart = pt.x();
  ystart = pt.y();
}

void Editor::onMouseMove(QPoint pt) {
  if (current == nullptr)
    return;
  if (!current->isDrawing)
    return;
  current->set(xstart, ystart, pt.x(), pt.y());
}

void Editor::onLeftButtonRelease(QPoint pt) {
  if (current == nullptr)
    return;
  if (!current->isDrawing)
    return;

  current->isDrawing = false;
  current->set(xstart, ystart, pt.x(), pt.y());

  shapes.push_back(current->clone());
  return;
}

void Editor::onPaint(QPainter &painter) const {
  for (Shape *s : shapes)
    s->show(painter);
  if (current == nullptr)
    return;
  if (current->isDrawing) {
    current->show(painter);
  }
}