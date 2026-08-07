#include "module2.h"
#include "groups.h"
#include <QApplication>
#include <QDialog>
#include <QListWidget>
#include <QObject>
#include <QPushButton>
#include <QStyle>
#include <QVBoxLayout>
#include <QWidget>

namespace {

class ListBoxDialog : public QDialog {
public:
  ListBoxDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Модуль 2");
    setMinimumSize(200, 100);
    setWindowIcon(
        QApplication::style()->standardIcon(QStyle::SP_MessageBoxQuestion));

    QListWidget *groupsList = new QListWidget(this);
    groupsList->addItems(GROUPS);
    connect(groupsList, &QListWidget::itemDoubleClicked, this,
            [this]() { done(QDialog::Accepted); });

    QPushButton *confirmButton = new QPushButton("Так", this);
    connect(confirmButton, &QPushButton::clicked, this,
            [this]() { done(QDialog::Accepted); });
    QPushButton *cancelButton = new QPushButton("Відміна", this);
    connect(cancelButton, &QPushButton::clicked, this,
            [this]() { done(QDialog::Rejected); });

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(groupsList);
    layout->addWidget(confirmButton);
    layout->addWidget(cancelButton);

    adjustSize();
  }
  QString selectedGroup() const {

    QListWidget *groupsList = findChild<QListWidget *>();
    if (groupsList) {
      QListWidgetItem *selectedItem = groupsList->selectedItems().value(0);
      if (selectedItem) {
        return selectedItem->text();
      }
    }
    return QString();
  }
};

} // namespace

bool RunModule2(QWidget *parent, QString &selectedGroup) {
  ListBoxDialog dialog(parent);
  if (dialog.exec() == QDialog::Accepted) {
    selectedGroup = dialog.selectedGroup();
    return true;
  }
  return false;
}
