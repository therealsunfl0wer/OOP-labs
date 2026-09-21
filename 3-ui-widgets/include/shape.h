#ifndef SHAPE_H
#define SHAPE_H

#include <QPainter>

class Shape {
protected:
  int xs1, ys1, xs2, ys2;

public:
  void Set(int x1, int y1, int x2, int y2);
  virtual void Show(QPainter &painter) const = 0;
  virtual ~Shape() = default;
};

Shape *CreatePointShape(int x1, int y1, int x2, int y2);
Shape *CreateLineShape(int x1, int y1, int x2, int y2);
Shape *CreateRectShape(int x1, int y1, int x2, int y2);
Shape *CreateEllipseShape(int x1, int y1, int x2, int y2);

#endif // SHAPE_H
