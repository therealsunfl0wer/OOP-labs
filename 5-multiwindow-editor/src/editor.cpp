#include "editor.h"
#include "shape.h"
#include <utility>

Editor *Editor::singleton = nullptr;

Editor::Editor() = default;
Editor::~Editor() = default;

void Editor::clear() { shapes.clear(); }

void Editor::setShape(std::unique_ptr<Shape> selected) {
  current = std::move(selected);
}

void Editor::addShape(std::unique_ptr<Shape> s) {
  shapes.push_back(std::move(s));
}

void Editor::onLeftButtonPress(QPoint pt) {
  if (current == nullptr)
    return;
  current->isDrawing = true;

  xstart = pt.x();
  ystart = pt.y();

  notify();
}

void Editor::onLeftButtonRelease(QPoint pt) {
  if (current == nullptr)
    return;
  if (!current->isDrawing)
    return;

  current->isDrawing = false;
  current->setCoords(xstart, ystart, pt.x(), pt.y());

  shapes.push_back(current->clone());

  notify();
}

void Editor::onMouseMove(QPoint pt) {
  if (current == nullptr)
    return;
  if (!current->isDrawing)
    return;
  current->setCoords(xstart, ystart, pt.x(), pt.y());

  notify();
}

void Editor::onPaint(QPainter &painter) const {
  for (const std::unique_ptr<Shape> &s : shapes)
    s->show(painter);
  if (current == nullptr)
    return;
  if (current->isDrawing) {
    current->show(painter);
  }
}