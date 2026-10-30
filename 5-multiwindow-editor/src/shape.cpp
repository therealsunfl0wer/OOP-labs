#include "shape.h"
#include "shapefactory.h"
#include <QBrush>
#include <QPainter>
#include <QPen>
#include <QPoint>

void Shape::setStyle(QPainter &painter) const {
  if (isDrawing) {
    painter.setPen(QPen(Qt::black, 1, Qt::DashLine));
    painter.setBrush(Qt::NoBrush);
  } else {
    painter.setPen(QPen(Qt::black, 3));
    painter.setBrush(Qt::NoBrush);
  }
}

class PointShape : public virtual Shape {
public:
  void show(QPainter &painter) const override {
    setStyle(painter);
    show(painter, xs1, ys1, xs2, ys2);
  }
  void show(QPainter &painter, int x1, int y1, int x2, int y2) const {
    painter.drawPoint(QPoint(x2, y2));
  }
  Shape *clone() const override { return new PointShape(*this); }
};

class LineShape : public virtual Shape {
public:
  void show(QPainter &painter) const override {
    setStyle(painter);
    show(painter, xs1, ys1, xs2, ys2);
  }
  void show(QPainter &painter, int x1, int y1, int x2, int y2) const {
    painter.drawLine(QLine(QPoint(x1, y1), QPoint(x2, y2)));
  }
  Shape *clone() const override { return new LineShape(*this); }
};

class RectShape : public virtual Shape {
protected:
  // needed for composite shapes to avoid calculation mishaps
  // draws corner-to-corner
  void ShowBaseShape(QPainter &painter, int x1, int y1, int x2, int y2) const {
    Shape::setStyle(painter);
    painter.drawRect(QRect(QPoint(x1, y1), QPoint(x2, y2)).normalized());
  }

public:
  void show(QPainter &painter) const override {
    setStyle(painter);
    show(painter, xs1, ys1, xs2, ys2);
  }
  void setStyle(QPainter &painter) const override {
    if (isDrawing) {
      painter.setPen(QPen(Qt::black, 1, Qt::DashLine));
      painter.setBrush(Qt::NoBrush);
    } else {
      painter.setPen(QPen(Qt::black, 3));
      painter.setBrush(QBrush(Qt::gray, Qt::SolidPattern));
    }
  }
  // draws center-to-corner
  void show(QPainter &painter, int x1, int y1, int x2, int y2) const {
    painter.drawRect(QRect(QPoint(x1 - abs(x2 - x1), y1 - abs(y2 - y1)),
                           QPoint(x1 + abs(x2 - x1), y1 + abs(y2 - y1)))
                         .normalized());
  }
  Shape *clone() const override { return new RectShape(*this); }
};

class EllipseShape : public virtual Shape {
public:
  void show(QPainter &painter) const override {
    setStyle(painter);
    show(painter, xs1, ys1, xs2, ys2);
  }
  void setStyle(QPainter &painter) const override {
    if (isDrawing) {
      painter.setPen(QPen(Qt::black, 1, Qt::DashLine));
      painter.setBrush(Qt::NoBrush);
    } else {
      painter.setPen(QPen(Qt::black, 3));
      painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
    }
  }
  void show(QPainter &painter, int x1, int y1, int x2, int y2) const {
    painter.drawEllipse(QRect(QPoint(x1, y1), QPoint(x2, y2)).normalized());
  }
  Shape *clone() const override { return new EllipseShape(*this); }
};

class LineOOShape : public LineShape, public EllipseShape {
public:
  void show(QPainter &painter) const override {
    setStyle(painter);
    show(painter, xs1, ys1, xs2, ys2);
  }
  void setStyle(QPainter &painter) const override {
    if (isDrawing) {
      painter.setPen(QPen(Qt::black, 1, Qt::DashLine));
      painter.setBrush(Qt::NoBrush);
    } else {
      painter.setPen(QPen(Qt::black, 3));
      painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
    }
  }
  void show(QPainter &painter, int x1, int y1, int x2, int y2) const {
    LineShape::show(painter);

    int r = 4;
    EllipseShape::show(painter, x1 - r, y1 - r, x1 + r, y1 + r);
    EllipseShape::show(painter, x2 - r, y2 - r, x2 + r, y2 + r);
  }
  Shape *clone() const override { return new LineOOShape(*this); }
};

class CubeShape : public LineShape, public RectShape {
public:
  void show(QPainter &painter) const override {
    setStyle(painter);
    show(painter, xs1, ys1, xs2, ys2);
  }

  void show(QPainter &painter, int x1, int y1, int x2, int y2) const {
    int d = 20;

    RectShape::ShowBaseShape(painter, x1, y1, x2, y2);
    RectShape::ShowBaseShape(painter, x1 + d, y1 - d, x2 + d, y2 - d);
    LineShape::show(painter, x1, y1, x1 + d, y1 - d);
    LineShape::show(painter, x2, y1, x2 + d, y1 - d);
    LineShape::show(painter, x1, y2, x1 + d, y2 - d);
    LineShape::show(painter, x2, y2, x2 + d, y2 - d);
  }
  Shape *clone() const override { return new CubeShape(*this); }
};

ShapeFactory::ShapeFactory() {
  add("point", QString("Точка"), QString(":point"),
      []() -> Shape * { return new PointShape(); });

  add("line", QString("Лінія"), QString(":line"),
      []() -> Shape * { return new LineShape(); });

  add("rectangle", QString("Прямокутник"), QString(":rectangle"),
      []() -> Shape * { return new RectShape(); });

  add("ellipse", QString("Еліпс"), QString(":ellipse"),
      []() -> Shape * { return new EllipseShape(); });

  add("line-oo", QString("Лінія з кружечками"), QString(":o-o-line"),
      []() -> Shape * { return new LineOOShape(); });

  add("cube", QString("Куб"), QString(":cuboid"),
      []() -> Shape * { return new CubeShape(); });
}