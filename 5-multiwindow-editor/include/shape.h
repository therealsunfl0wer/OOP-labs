#ifndef SHAPE_H
#define SHAPE_H

#include <QPainter>
#include <QString>
#include <memory>

struct ShapeParams {
  QString id;
  int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
};

class Shape {
  friend class ShapeFactory;
  QString id;

protected:
  virtual void setStyle(QPainter &painter) const;
  int xs1 = 0, ys1 = 0, xs2 = 0, ys2 = 0;

public:
  bool isDrawing = false;
  ShapeParams const getParams() const { return {id, xs1, ys1, xs2, ys2}; }
  void setCoords(int x1, int y1, int x2, int y2) {
    xs1 = x1;
    ys1 = y1;
    xs2 = x2;
    ys2 = y2;
  }
  virtual void show(QPainter &painter) const = 0;
  virtual std::unique_ptr<Shape> clone() const = 0;
  virtual ~Shape() = default;
};

#endif // SHAPE_H
