#ifndef SHAPE_H
#define SHAPE_H

#include <QPainter>

class Shape {
protected:
  int xs1 = 0, ys1 = 0, xs2 = 0, ys2 = 0;

public:
  void Set(int x1, int y1, int x2, int y2);
  virtual void Show(QPainter &painter) const = 0;
  virtual Shape *Clone() const = 0;
  virtual ~Shape() = default;
};

Shape *CreatePointShape();
Shape *CreateLineShape();
Shape *CreateRectShape();
Shape *CreateEllipseShape();
Shape *CreateLineOOShape();
Shape *CreateCubeShape();

#endif // SHAPE_H
