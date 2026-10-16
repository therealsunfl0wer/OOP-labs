#include "shape.h"
#include <QBrush>
#include <QPainter>
#include <QPen>
#include <QPoint>

void Shape::Set(int x1, int y1, int x2, int y2) {
  xs1 = x1;
  ys1 = y1;
  xs2 = x2;
  ys2 = y2;
}

class PointShape : public virtual Shape {
public:
  void Show(QPainter &painter) const override {
    painter.setPen(QPen(Qt::black, 3));
    Show(painter, xs1, ys1, xs2, ys2);
  }
  void Show(QPainter &painter, int x1, int y1, int x2, int y2) const {
    painter.drawPoint(QPoint(x2, y2));
  }
  Shape *Clone() const override { return new PointShape(*this); }
};

class LineShape : public virtual Shape {
public:
  void Show(QPainter &painter) const override {
    painter.setPen(QPen(Qt::black, 3));
    Show(painter, xs1, ys1, xs2, ys2);
  }
  void Show(QPainter &painter, int x1, int y1, int x2, int y2) const {
    painter.drawLine(QLine(QPoint(x1, y1), QPoint(x2, y2)));
  }
  Shape *Clone() const override { return new LineShape(*this); }
};

class RectShape : public virtual Shape {
protected:
  // needed for composite shapes to avoid calculation mishaps
  // draws corner-to-corner
  void ShowBaseShape(QPainter &painter, int x1, int y1, int x2, int y2) const {
    painter.drawRect(QRect(QPoint(x1, y1), QPoint(x2, y2)).normalized());
  }

public:
  void Show(QPainter &painter) const override {
    painter.setPen(QPen(Qt::black, 3));
    painter.setBrush(QBrush(Qt::gray, Qt::SolidPattern));
    Show(painter, xs1, ys1, xs2, ys2);
    painter.setBrush(Qt::NoBrush);
  }
  // draws center-to-corner
  void Show(QPainter &painter, int x1, int y1, int x2, int y2) const {
    painter.drawRect(
        QRect(QPoint(x1 - std::abs(x2 - x1), y1 - std::abs(y2 - y1)),
              QPoint(x1 + std::abs(x2 - x1), y1 + std::abs(y2 - y1)))
            .normalized());
  }
  Shape *Clone() const override { return new RectShape(*this); }
};

class EllipseShape : public virtual Shape {
public:
  void Show(QPainter &painter) const override {
    painter.setPen(QPen(Qt::black, 3));
    painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
    Show(painter, xs1, ys1, xs2, ys2);
    painter.setBrush(Qt::NoBrush);
  }
  void Show(QPainter &painter, int x1, int y1, int x2, int y2) const {
    painter.drawEllipse(QRect(QPoint(x1, y1), QPoint(x2, y2)).normalized());
  }
  Shape *Clone() const override { return new EllipseShape(*this); }
};

class LineOOShape : public LineShape, public EllipseShape {
public:
  void Show(QPainter &painter) const override {
    LineShape::Show(painter);

    int r = 4;
    EllipseShape::Show(painter, LineShape::xs1 - r, LineShape::ys1 - r,
                       LineShape::xs1 + r, LineShape::ys1 + r);
    EllipseShape::Show(painter, LineShape::xs2 - r, LineShape::ys2 - r,
                       LineShape::xs2 + r, LineShape::ys2 + r);
  }
  Shape *Clone() const override { return new LineOOShape(*this); }
};

class CubeShape : public LineShape, public RectShape {
public:
  void Show(QPainter &painter) const override {
    painter.setPen(QPen(Qt::black, 3));
    Show(painter, xs1, ys1, xs2, ys2);
  }

  void Show(QPainter &painter, int x1, int y1, int x2, int y2) const {
    int d = 20;

    RectShape::ShowBaseShape(painter, x1, y1, x2, y2);
    RectShape::ShowBaseShape(painter, x1 + d, y1 - d, x2 + d, y2 - d);
    LineShape::Show(painter, x1, y1, x1 + d, y1 - d);
    LineShape::Show(painter, x2, y1, x2 + d, y1 - d);
    LineShape::Show(painter, x1, y2, x1 + d, y2 - d);
    LineShape::Show(painter, x2, y2, x2 + d, y2 - d);
  }
  Shape *Clone() const override { return new CubeShape(*this); }
};

Shape *CreatePointShape() { return new PointShape; }
Shape *CreateLineShape() { return new LineShape; }
Shape *CreateRectShape() { return new RectShape; }
Shape *CreateEllipseShape() { return new EllipseShape; }
Shape *CreateLineOOShape() { return new LineOOShape; }
Shape *CreateCubeShape() { return new CubeShape; }