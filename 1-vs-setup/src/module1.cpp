#include "module1.h"
#include <QApplication>
#include <QDialog>
#include <QPushButton>
#include <QStyle>
#include <QVBoxLayout>

namespace {

class FirstDialog : public QDialog {
public:
  FirstDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Крок 1");
    setMinimumSize(200, 100);
    setWindowIcon(
        QApplication::style()->standardIcon(QStyle::SP_MessageBoxQuestion));

    QPushButton *nextButton = new QPushButton("Далі >", this);
    connect(nextButton, &QPushButton::clicked, this,
            [this]() { done(QDialog::Accepted); });
    QPushButton *cancelButton = new QPushButton("Відміна", this);
    connect(cancelButton, &QPushButton::clicked, this,
            [this]() { done(QDialog::Rejected); });

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(nextButton);
    layout->addWidget(cancelButton);

    adjustSize();
  }
};

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

bool RunModule1(QWidget *parent) {
  while (true) {
    FirstDialog first(parent);
    if (first.exec() != QDialog::Accepted)
      return false;

    SecondDialog second(parent);
    int result = second.exec();
    if (result == SecondDialog::Confirmed)
      return true;
    if (result == SecondDialog::Back)
      continue;
    return false;
  }
}
