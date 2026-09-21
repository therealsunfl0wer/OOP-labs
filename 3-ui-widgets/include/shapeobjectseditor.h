#ifndef SHAPEOBJECTSEDITOR_H
#define SHAPEOBJECTSEDITOR_H

#include "editor.h"
#include "shape.h"

class ShapeObjectsEditor {
  static constexpr int MAX_SHAPES = 111;
  Shape *shapes[MAX_SHAPES] = {};
  int bufferIndex = 0;
  bool full = false;

  int validShapes() const { return full ? MAX_SHAPES : bufferIndex; }
 
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
