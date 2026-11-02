#ifndef SHAPEFACTORY_H
#define SHAPEFACTORY_H

#include <QString>
#include <functional>
#include <memory>
#include <utility>
#include <vector>

class Shape;

struct ShapeEntry {
  QString id;
  QString name;
  QString iconPath;
  std::function<std::unique_ptr<Shape>()> create;
};

class ShapeFactory {
  ShapeFactory();
  ~ShapeFactory() = default;
  std::vector<ShapeEntry> shapes;
  void add(QString id, QString name, QString iconPath,
           std::function<std::unique_ptr<Shape>()> create) {
    shapes.push_back(
        {std::move(id), std::move(name), std::move(iconPath),
         std::move(create)});
  }

public:
  ShapeFactory(const ShapeFactory&) = delete;
  ShapeFactory& operator=(const ShapeFactory&) = delete;

  static const ShapeFactory &instance() {
    static ShapeFactory factory;
    return factory;
  }
  std::unique_ptr<Shape> create(const QString &id) const;
  const std::vector<ShapeEntry> &registry() const { return shapes; }
};

#endif // SHAPEFACTORY_H
