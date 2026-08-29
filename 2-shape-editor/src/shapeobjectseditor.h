#ifndef SHAPEOBJECTSEDITOR_H
#define SHAPEOBJECTSEDITOR_H

#include "editor.h"
#include "shape.h"

class ShapeObjectsEditor {
  Shape *shapes[110] = {};
  int count = 0;

  ShapeEditor *currentEditor = nullptr;
  void setEditor(ShapeEditor *editor);

public:
  ShapeObjectsEditor();
  ~ShapeObjectsEditor();

  void StartPointEditor();
  void StartLineEditor();
  void StartRectEditor();
  void StartEllipseEditor();

  void OnLBdown(QPoint pt);
  void OnLBup(QPoint pt);
  void OnMouseMove(QPoint pt);
  void OnPaint(QPainter &painter) const;
};
#endif // SHAPEOBJECTSEDITOR_H
