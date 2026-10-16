#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H

#include "editor.h"
#include <QWidget>

class CanvasWidget : public QWidget {
  Q_OBJECT
public:
  ~CanvasWidget();
  explicit CanvasWidget(QWidget *parent = nullptr);

  void selectPoint();
  void selectLine();
  void selectRect();
  void selectEllipse();
  void selectLineOO();
  void selectCube();

protected:
  void paintEvent(QPaintEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;

private:
  Editor *editor;
};

#endif // CANVASWIDGET_H
