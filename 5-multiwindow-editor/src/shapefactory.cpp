#include "shapefactory.h"
#include "shape.h"
#include <algorithm>

std::unique_ptr<Shape> ShapeFactory::create(const QString &id) const {
  const auto iterator =
      std::find_if(shapes.begin(), shapes.end(),
                   [&id](const ShapeEntry &entry) { return entry.id == id; });
  if (iterator == shapes.end())
    return nullptr;
  std::unique_ptr<Shape> shape = iterator->create();
  if (!shape)
    return nullptr;
  shape->id = id;
  return shape;
}
