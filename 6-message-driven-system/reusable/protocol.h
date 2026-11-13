#ifndef LAB6_PROTOCOL_H
#define LAB6_PROTOCOL_H

#include <QString>
#include <QStringList>

namespace Lab6Protocol {
inline const QString Object2Server = "lab6-object2";
inline const QString Object3Server = "lab6-object3";

inline QString command(const QString &name, const QStringList &arguments = {}) {
  return (QStringList{name} + arguments).join(' ') + '\n';
}
} // namespace Lab6Protocol

#endif