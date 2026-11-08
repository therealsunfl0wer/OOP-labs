#include "shapefile.h"
#include "editor.h"
#include "shape.h"
#include "shapefactory.h"
#include <QFile>
#include <QSaveFile>
#include <QString>
#include <QTextStream>

int constexpr TABLE_ROW_LENGTH = 5;

static const ShapeFactory &factory = ShapeFactory::instance();
inline Editor *editor = Editor::instance();

namespace ShapeFile {

Result create() {
  Result r;
  editor->clear();
  editor->onReload();
  r.ok = true;
  return r;
}

Result save(const QString &filePath) {
  Result r;

  QSaveFile file(filePath);
  if (!file.open(QIODeviceBase::WriteOnly | QIODevice::Text)) {
    r.errorMessage = file.errorString();
    return r;
  }
  QTextStream out(&file);

  for (int i = 0; i < editor->entries(); ++i) {
    const Shape *shape = editor->getShape(i);
    const ShapeParams params = shape->getParams();
    out << params.id << ',' << params.x1 << ',' << params.y1 << ',' << params.x2
        << ',' << params.y2 << '\n';
    ++r.lines;
  }

  if (!file.commit()) {
    r.ok = false;
    r.errorMessage = file.errorString();
  } else
    r.ok = true;

  return r;
}

Result load(const QString &filePath) {
  Result r;

  QFile file(filePath);
  if (!file.open(QIODeviceBase::ReadOnly | QIODevice::Text)) {
    r.ok = false;
    r.errorMessage = file.errorString();
    return r;
  }
  QTextStream in(&file);

  std::vector<std::unique_ptr<Shape>> loadedShapes;

  while (!in.atEnd()) {
    QString line = in.readLine();
    r.lines++;
    QStringList split = line.split(',');

    if (split.length() != TABLE_ROW_LENGTH) {
      r.ok = false;
      r.errorMessage = QString("line %1: row count: %2, expected %3")
                           .arg(r.lines)
                           .arg(split.length())
                           .arg(TABLE_ROW_LENGTH);
      return r;
    }

    int coords[4] = {};

    for (int i = 1; i < TABLE_ROW_LENGTH; i++) {
      coords[i - 1] = split[i].toInt(&r.ok);
      if (!r.ok) {
        r.errorMessage = QString("line %1, argument %2 is not a "
                                 "valid coordinate value")
                             .arg(r.lines)
                             .arg(i);
        return r;
      }
    }

    std::unique_ptr<Shape> s = factory.create(split[0]);

    if (s == nullptr) {
      r.ok = false;
      r.errorMessage =
          QString("failed to create a shape at line %1").arg(r.lines);
      return r;
    }

    s->setCoords(coords[0], coords[1], coords[2], coords[3]);

    loadedShapes.push_back(std::move(s));
  }
  editor->clear();
  for (std::unique_ptr<Shape> &s : loadedShapes) {
    editor->addShape(std::move(s));
  }
  editor->onReload();
  r.ok = true;
  return r;
}
} // namespace ShapeFile
