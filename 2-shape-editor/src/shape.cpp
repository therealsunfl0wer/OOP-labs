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

class PointShape : public Shape {
public:
  void Show(QPainter &painter) const override {
    painter.setPen(QPen(Qt::black, 3));
    painter.drawPoint(xs1, ys1);
  }
};

class LineShape : public Shape {
public:
  void Show(QPainter &painter) const override {
    painter.setPen(QPen(Qt::black, 3));
    painter.drawLine(xs1, ys1, xs2, ys2);
  }
};

class RectangleShape : public Shape {
public:
  void Show(QPainter &painter) const override {
    QRect rect(QPoint(xs1, ys1), QPoint(xs2, ys2));
    painter.setPen(QPen(Qt::black, 3));
    painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
    painter.drawRect(rect.normalized());
    painter.setBrush(Qt::NoBrush);
  }
};

class EllipseShape : public Shape {
public:
  void Show(QPainter &painter) const override {
    QRect rect(QPoint(xs1, ys1), QPoint(xs2, ys2));
    painter.setPen(QPen(Qt::black, 3));
    painter.setBrush(Qt::NoBrush);
    painter.drawEllipse(rect.normalized());
  }
};

Shape *CreatePointShape(int x1, int y1, int x2, int y2) {
  Shape *p = new PointShape;
  p->Set(x1, y1, x2, y2);
  return p;
}
Shape *CreateLineShape(int x1, int y1, int x2, int y2) {
  Shape *l = new LineShape;
  l->Set(x1, y1, x2, y2);
  return l;
}
Shape *CreateRectShape(int x1, int y1, int x2, int y2) {
  Shape *r = new RectangleShape;
  r->Set(x1, y1, x2, y2);
  return r;
}
Shape *CreateEllipseShape(int x1, int y1, int x2, int y2) {
  Shape *e = new EllipseShape;
  e->Set(x1, y1, x2, y2);
  return e;
}
