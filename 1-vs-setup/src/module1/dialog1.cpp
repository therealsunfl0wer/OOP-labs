#include "dialog1.h"
#include "dialog2.h"
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

} // namespace

bool RunModule1(QWidget *parent) {
  enum Result { Back = -1, Cancelled = 0, Confirmed = 1 };
  while (true) {
    FirstDialog first(parent);
    if (first.exec() != QDialog::Accepted)
      return false;
    int dialog2SIG = RunModule1Dialog2(parent);
    if ((Result)dialog2SIG == Confirmed)
      return true;
    if ((Result)dialog2SIG == Back)
      continue;
    return false;
  };
}
