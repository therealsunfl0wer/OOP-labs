#ifndef SHAPEFACTORY_H
#define SHAPEFACTORY_H

#include <QString>
#include <functional>
#include <string>
#include <utility>
#include <vector>

class Shape;

struct ShapeEntry {
  std::string id;
  QString name;
  QString iconPath;
  std::function<Shape *()> create;
};

class ShapeFactory {
  ShapeFactory();
  ~ShapeFactory() = default;
  std::vector<ShapeEntry> shapes;
  void add(std::string id, QString name, QString iconPath,
           std::function<Shape *()> create) {
    shapes.push_back(
        {std::move(id), std::move(name), std::move(iconPath), create});
  }

public:
  ShapeFactory(const ShapeFactory&) = delete;
  ShapeFactory& operator=(const ShapeFactory&) = delete;

  static const ShapeFactory &instance() {
    static ShapeFactory factory;
    return factory;
  }
  Shape *create(const std::string &id) const;
  const std::vector<ShapeEntry> &registry() const { return shapes; }
};

#endif // SHAPEFACTORY_H
