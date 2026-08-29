#ifndef EDITOR_H
#define EDITOR_H

#include <QPainter>
#include <QPoint>

class Shape; // forward declaration, Editor doesn't know about Shape

class Editor {
public:
  virtual void OnLBDown(QPoint pt) = 0;
  virtual Shape *OnLBUp(QPoint pt) = 0;
  virtual void OnMouseMove(QPoint pt) = 0;
  virtual void OnPaint(QPainter &painter) const = 0;
  virtual ~Editor() = default;
};

class ShapeEditor : public Editor {
protected:
  int xstart, ystart, xend, yend;
  bool isDrawing;
  virtual Shape *MakeShape() const = 0;
  virtual void DrawPreview(QPainter &painter) const = 0;

public:
  void OnLBDown(QPoint pt) override;
  Shape *OnLBUp(QPoint pt) override;
  void OnMouseMove(QPoint pt) override;
  void OnPaint(QPainter &painter) const override;
};

ShapeEditor *CreatePointEditor();
ShapeEditor *CreateLineEditor();
ShapeEditor *CreateRectEditor();
ShapeEditor *CreateEllipseEditor();

#endif // EDITOR_H
