#include "shapefactory.h"
#include <algorithm>

Shape *ShapeFactory::create(const std::string &id) const {
  const auto iterator =
      std::find_if(shapes.begin(), shapes.end(),
                   [&id](const ShapeEntry &entry) { return entry.id == id; });
  if (iterator == shapes.end() || !iterator->create())
    return nullptr;
  return iterator->create();
}