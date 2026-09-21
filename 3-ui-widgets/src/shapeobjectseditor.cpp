#include "shapeobjectseditor.h"
#include "shape.h"

ShapeObjectsEditor::ShapeObjectsEditor() {
  currentEditor = CreatePointEditor();
}

ShapeObjectsEditor::~ShapeObjectsEditor() {
  delete currentEditor;
  for (int i = 0; i < bufferIndex; ++i)
    delete shapes[i];
}

void ShapeObjectsEditor::setEditor(ShapeEditor *editor) {
  delete currentEditor;
  currentEditor = editor;
}

void ShapeObjectsEditor::StartPointEditor() { setEditor(CreatePointEditor()); }
void ShapeObjectsEditor::StartLineEditor() { setEditor(CreateLineEditor()); }
void ShapeObjectsEditor::StartRectEditor() { setEditor(CreateRectEditor()); }
void ShapeObjectsEditor::StartEllipseEditor() {
  setEditor(CreateEllipseEditor());
}

void ShapeObjectsEditor::OnLBdown(QPoint pt) { currentEditor->OnLBDown(pt); }

void ShapeObjectsEditor::OnLBup(QPoint pt) {
  Shape *finished = currentEditor->OnLBUp(pt);
  if (!finished)
    return;
  if (full)
    delete shapes[bufferIndex];

  shapes[bufferIndex++] = finished;
  if (bufferIndex == MAX_SHAPES) {
    bufferIndex = 0;
    full = true;
  }
}

void ShapeObjectsEditor::OnMouseMove(QPoint pt) {
  currentEditor->OnMouseMove(pt);
}

void ShapeObjectsEditor::OnPaint(QPainter &painter) const {
  for (int i = 0; i < validShapes(); ++i)
    shapes[i]->Show(painter);

  currentEditor->OnPaint(painter);
}
