#ifndef EDITOR_H
#define EDITOR_H

#include <QPainter>
#include <QPoint>
#include <functional>
#include <memory>
#include <vector>

class Shape; // forward declaration, Editor doesn't know about Shape

class Editor {
  Editor();
  ~Editor();

  static Editor *singleton;

  std::vector<std::unique_ptr<Shape>> shapes;
  int xstart, ystart;
  std::unique_ptr<Shape> current;

  std::vector<std::function<void()>> subscribed;
  void notify() {
    for (std::function<void()> sub : subscribed) {
      sub();
    }
  }

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

  // TODO: add ids for subscribed callbacks
  // fine for now as the lifetime of CanvasWidget is same as MainWindow's
  void subscribe(std::function<void()> callback) {
    subscribed.push_back(callback);
  }

  // TODO:
  // void unsubscribe(const &id) const {}

  void clear();
  size_t entries() const { return shapes.size(); }
  const Shape *getShape(size_t shapeAt) const {
    return shapes.at(shapeAt).get();
  }

  void setShape(std::unique_ptr<Shape> selected);
  void addShape(std::unique_ptr<Shape> s);
  void onLeftButtonPress(QPoint pt);
  void onLeftButtonRelease(QPoint pt);
  void onMouseMove(QPoint pt);
  void onPaint(QPainter &painter) const;
  void onReload() { notify(); }
};

#endif // EDITOR_H