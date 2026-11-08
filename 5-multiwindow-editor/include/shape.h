#ifndef SHAPE_H
#define SHAPE_H

#include <QPainter>
#include <QBrush>
#include <QString>
#include <memory>

enum class ShapeState { Final, Preview, Selected };

struct ShapeParams {
  QString id;
  int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
};

class Shape {
  friend class ShapeFactory;
  QString id;
  ShapeState state = ShapeState::Final;

protected:
  void setStyle(QPainter &painter) const;
  virtual QBrush fill() const;
  int xs1 = 0, ys1 = 0, xs2 = 0, ys2 = 0;

public:
  ShapeParams const getParams() const { return {id, xs1, ys1, xs2, ys2}; }
  void setCoords(int x1, int y1, int x2, int y2) {
    xs1 = x1;
    ys1 = y1;
    xs2 = x2;
    ys2 = y2;
  }
  ShapeState getState() const { return state; }
  void setState(ShapeState s) { state = s; }
  virtual void show(QPainter &painter) const = 0;
  virtual std::unique_ptr<Shape> clone() const = 0;
  virtual ~Shape() = default;
};

#endif // SHAPE_H
