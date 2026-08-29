#include "editor.h"
#include "shape.h"

void ShapeEditor::OnLBDown(QPoint pt) {
  xstart = pt.x();
  ystart = pt.y();
  xend = xstart;
  yend = ystart;
  isDrawing = true;
}

void ShapeEditor::OnMouseMove(QPoint pt) {
  if (!isDrawing)
    return;
  xend = pt.x();
  yend = pt.y();
}

Shape *ShapeEditor::OnLBUp(QPoint pt) {
  if (!isDrawing)
    return nullptr;
  xend = pt.x();
  yend = pt.y();
  isDrawing = false;

  Shape *s = MakeShape();
  s->Set(xstart, ystart, xend, yend);
  return s;
}

void ShapeEditor::OnPaint(QPainter &painter) const {
  if (isDrawing)
    DrawPreview(painter);
}

namespace {

class PointEditor : public ShapeEditor {
protected:
  Shape *MakeShape() const override { return CreatePointShape(0, 0, 0, 0); }
  void DrawPreview(QPainter &painter) const override {
    painter.setPen(QPen(Qt::blue, 2));
    painter.drawEllipse(QPoint(xend, yend), 2, 2);
  }
};

class LineEditor : public ShapeEditor {
protected:
  Shape *MakeShape() const override { return CreateLineShape(0, 0, 0, 0); }
  void DrawPreview(QPainter &painter) const override {
    painter.setPen(QPen(Qt::blue, 1));
    painter.drawLine(xstart, ystart, xend, yend);
  }
};

class RectEditor : public ShapeEditor {
protected:
  Shape *MakeShape() const override { return CreateRectShape(0, 0, 0, 0); }
  void DrawPreview(QPainter &painter) const override {
    painter.setPen(QPen(Qt::blue, 1));
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(
        QRect(QPoint(xstart, ystart), QPoint(xend, yend)).normalized());
  }
};

class EllipseEditor : public ShapeEditor {
protected:
  Shape *MakeShape() const override { return CreateEllipseShape(0, 0, 0, 0); }
  void DrawPreview(QPainter &painter) const override {
    painter.setPen(QPen(Qt::blue, 1));
    painter.setBrush(Qt::NoBrush);
    painter.drawEllipse(
        QRect(QPoint(xstart, ystart), QPoint(xend, yend)).normalized());
  }
};

} // namespace

ShapeEditor *CreatePointEditor() { return new PointEditor; }
ShapeEditor *CreateLineEditor() { return new LineEditor; }
ShapeEditor *CreateRectEditor() { return new RectEditor; }
ShapeEditor *CreateEllipseEditor() { return new EllipseEditor; }
