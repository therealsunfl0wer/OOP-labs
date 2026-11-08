#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H

#include "editor.h"
#include <QString>
#include <QWidget>

class CanvasWidget : public QWidget {
  Q_OBJECT

  Editor &editor = *Editor::instance();

public:
  explicit CanvasWidget(QWidget *parent = nullptr);

  void selectShape(const QString &id);

protected:
  void paintEvent(QPaintEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif // CANVASWIDGET_H
