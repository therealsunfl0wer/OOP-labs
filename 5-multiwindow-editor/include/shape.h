#ifndef SHAPE_H
#define SHAPE_H

#include <QPainter>

class Shape {
protected:
  virtual void setStyle(QPainter &painter) const;
  int xs1 = 0, ys1 = 0, xs2 = 0, ys2 = 0;

public:
  bool isDrawing = false;
  void Set(int x1, int y1, int x2, int y2) {
    xs1 = x1;
    ys1 = y1;
    xs2 = x2;
    ys2 = y2;
  }
  virtual void Show(QPainter &painter) const = 0;
  virtual Shape *Clone() const = 0;
  virtual ~Shape() = default;
};

#endif // SHAPE_H
