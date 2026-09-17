#include "dialog2.h"
#include <QApplication>
#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>

namespace {

class SecondDialog : public QDialog {
public:
  enum Result { Back = -1, Cancelled = 0, Confirmed = 1 };
  SecondDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Крок 2");
    setMinimumSize(200, 100);

    QPushButton *backButton = new QPushButton("< Назад", this);
    connect(backButton, &QPushButton::clicked, this, [this]() { done(Back); });
    QPushButton *confirmButton = new QPushButton("Так", this);
    connect(confirmButton, &QPushButton::clicked, this,
            [this]() { done(Confirmed); });
    QPushButton *cancelButton = new QPushButton("Відміна", this);
    connect(cancelButton, &QPushButton::clicked, this,
            [this]() { done(Cancelled); });

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(backButton);
    layout->addWidget(confirmButton);
    layout->addWidget(cancelButton);

    adjustSize();
  }
};

} // namespace

int RunModule1Dialog2(QWidget *parent) {
  SecondDialog second(parent);
  int result = second.exec();
  return result;
}