#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H

#include "shapeobjectseditor.h"
#include <QWidget>

class CanvasWidget : public QWidget {
  Q_OBJECT
public:
  explicit CanvasWidget(QWidget *parent = nullptr);

  void selectPointMode();
  void selectLineMode();
  void selectRectMode();
  void selectEllipseMode();

protected:
  void paintEvent(QPaintEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;

private:
  ShapeObjectsEditor editor;
};

#endif // CANVASWIDGET_H
