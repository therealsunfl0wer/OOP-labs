#ifndef EDITOR_H
#define EDITOR_H

#include <vector>
#include <QPainter>
#include <QPoint>

class Shape; // forward declaration, Editor doesn't know about Shape

class Editor {
  // no point in constructor when using a vector class
  std::vector<Shape *> shapes;
  bool isDrawing = false;
  int xstart, ystart;
  
  public:
  Shape *current = nullptr;
  ~Editor();
  
  void Start(Shape *selected);
  void onLBDown(QPoint pt);
  void onLBUp(QPoint pt);
  void onMouseMove(QPoint pt);
  void onPaint(QPainter &painter) const;
};

#endif // EDITOR_H