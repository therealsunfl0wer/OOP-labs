#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H

#include "editor.h"
#include "shapefactory.h"
#include <QWidget>
#include <iostream>
#include <string>

class CanvasWidget : public QWidget {
  Q_OBJECT
public:
  explicit CanvasWidget(QWidget *parent = nullptr);

  void selectShape(const std::string &id) {
    Shape *shape = ShapeFactory::instance().create(id);
    if (shape == nullptr)
      std::cerr
          << "ShapeFactory::instance().create(id): Shape not found in registry!"
          << std::endl;
    else
      editor->Start(shape);
  }

protected:
  void paintEvent(QPaintEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;

private:
  Editor *editor = Editor::instance();
};

#endif // CANVASWIDGET_H
