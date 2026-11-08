#include "editor.h"
#include "shape.h"
#include <utility>

Editor *Editor::singleton = nullptr;

Editor::Editor() = default;
Editor::~Editor() = default;

void Editor::select(int i) {
  if (i == selectedIdx)
    return;
  if (i < -1 || i >= entries())
    return;
  if (selectedIdx >= 0)
    shapes[static_cast<size_t>(selectedIdx)]->setState(ShapeState::Final);
  if (i >= 0)
    shapes[static_cast<size_t>(i)]->setState(ShapeState::Selected);
  selectedIdx = i;
  notify();
}

void Editor::removeAt(int i) {
  if (i < 0 || i >= entries())
    return;
  shapes.erase(shapes.begin() + i);
  ++drawingRevision;
  if (i == selectedIdx)
    selectedIdx = -1;
  else if (i < selectedIdx)
    selectedIdx--;
  notify();
}

void Editor::clear() {
  if (shapes.empty())
    return;
  shapes.clear();
  selectedIdx = -1;
  ++drawingRevision;
}

void Editor::setShape(std::unique_ptr<Shape> selected) {
  current = std::move(selected);
}

void Editor::addShape(std::unique_ptr<Shape> s) {
  shapes.push_back(std::move(s));
  ++drawingRevision;
}

void Editor::onLeftButtonPress(QPoint pt) {
  if (current == nullptr)
    return;
  current->setState(ShapeState::Preview);

  xstart = pt.x();
  ystart = pt.y();

  notify();
}

void Editor::onLeftButtonRelease(QPoint pt) {
  if (current == nullptr)
    return;
  if (current->getState() != ShapeState::Preview)
    return;

  current->setState(ShapeState::Final);
  current->setCoords(xstart, ystart, pt.x(), pt.y());

  shapes.push_back(current->clone());
  ++drawingRevision;

  notify();
}

void Editor::onMouseMove(QPoint pt) {
  if (current == nullptr)
    return;
  if (current->getState() != ShapeState::Preview)
    return;
  current->setCoords(xstart, ystart, pt.x(), pt.y());

  notify();
}

void Editor::onPaint(QPainter &painter) const {
  for (const std::unique_ptr<Shape> &s : shapes)
    s->show(painter);
  if (current == nullptr)
    return;
  if (current->getState() == ShapeState::Preview) {
    current->show(painter);
  }
}