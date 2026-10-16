#include "editor.h"
#include "shape.h"

Editor::~Editor() {
  delete current;
  for (Shape *s : shapes) {
    delete s;
  }
}

void Editor::Start(Shape *selected) {
  delete current;
  current = selected;
}

void Editor::onLBDown(QPoint pt) {
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
  current->Set(xstart, ystart, pt.x(), pt.y());
}

void Editor::onLBUp(QPoint pt) {
  if (current == nullptr)
    return;
  if (!current->isDrawing)
    return;

  current->isDrawing = false;
  current->Set(xstart, ystart, pt.x(), pt.y());

  shapes.push_back(current->Clone());
  return;
}

void Editor::onPaint(QPainter &painter) const {
  for (Shape *s : shapes)
    s->Show(painter);
  if (current == nullptr)
    return;
  if (current->isDrawing) {
    current->Show(painter);
  }
}