#ifndef EDITOR_H
#define EDITOR_H

#include <QPainter>
#include <QPoint>
#include <vector>

class Shape; // forward declaration, Editor doesn't know about Shape

class Editor {
  Editor() = default; // constructors and destructors are public by default
  ~Editor();
  static Editor *singleton;
  std::vector<Shape *> shapes;
  int xstart, ystart;
  Shape *current = nullptr;

public:
  static Editor *instance() {
    if (singleton == nullptr)
      singleton = new Editor();
    return singleton;
  }
  static void destroy() {
    delete singleton;
    singleton = nullptr;
  }

  Editor(const Editor &) = delete;
  Editor &operator=(const Editor &) = delete;

  void Start(Shape *selected);
  void onLBDown(QPoint pt);
  void onLBUp(QPoint pt);
  void onMouseMove(QPoint pt);
  void onPaint(QPainter &painter) const;
};

#endif // EDITOR_H