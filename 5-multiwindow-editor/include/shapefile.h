#ifndef SHAPEFILE_H
#define SHAPEFILE_H

#include "editor.h"
#include <QString>

namespace ShapeFile { // stateless OOP in its glory

struct Result {
  bool ok = false;
  int lines = 0;
  QString errorMessage;
};

Result create();
Result save(const QString &filePath);
Result load(const QString &filePath);

} // namespace ShapeFile

#endif // SHAPEFILE_H