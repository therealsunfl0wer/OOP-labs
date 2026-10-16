#ifndef SHAPE_H
#define SHAPE_H

#include <QPainter>
#include <cstdlib>

class Shape {
protected:
  virtual void setStyle(QPainter &painter) const;
  int xs1 = 0, ys1 = 0, xs2 = 0, ys2 = 0;

public:
  bool isDrawing = false;
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
