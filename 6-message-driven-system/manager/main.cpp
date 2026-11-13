#include "../reusable/protocol.h"

#include <QApplication>
#include <QCloseEvent>
#include <QDoubleSpinBox>
#include <QFormLayout>
#include <QLabel>
#include <QLocalSocket>
#include <QMessageBox>
#include <QProcess>
#include <QPushButton>
#include <QSpinBox>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>

class Lab6Window : public QWidget {
  enum class State { Idle, WaitingObject2, WaitingObject3 };
  State state = State::Idle;
  QLocalSocket object2Socket;
  QLocalSocket object3Socket;
  QProcess object2Process;
  QProcess object3Process;
  QTimer retryTimer;
  int attempts = 0;
  int count = 0;
  double minimum = 0;
  double maximum = 0;
  bool closing = false;
  QSpinBox *countInput = nullptr;
  QDoubleSpinBox *minimumInput = nullptr;
  QDoubleSpinBox *maximumInput = nullptr;

  QLocalSocket *socketFor(State target) {
    return target == State::WaitingObject2 ? &object2Socket : &object3Socket;
  }

  void fail(const QString &message) {
    retryTimer.stop();
    state = State::Idle;
    QMessageBox::warning(this, "Помилка", message);
  }

  void send(QLocalSocket &socket, const QString &message) {
    socket.write(message.toUtf8());
    socket.flush();
  }

  void startChild(State target) {
    QProcess &process =
        target == State::WaitingObject2 ? object2Process : object3Process;
    if (process.state() == QProcess::NotRunning) {
      const QString name =
          target == State::WaitingObject2 ? "/object2" : "/object3";
      process.start(QCoreApplication::applicationDirPath() + name);
    }
  }

  void tryConnect(State target) {
    if (closing || state != target)
      return;
    QLocalSocket *socket = socketFor(target);
    if (socket->state() != QLocalSocket::UnconnectedState)
      return;
    const bool object2 = target == State::WaitingObject2;
    socket->connectToServer(object2 ? Lab6Protocol::Object2Server
                                    : Lab6Protocol::Object3Server);
    ++attempts;
    if (attempts >= 80)
      fail(object2 ? "Не вдалося запустити Object2."
                   : "Не вдалося запустити Object3.");
  }

  void beginConnection(State target) {
    state = target;
    attempts = 0;
    tryConnect(target);
    retryTimer.start(100);
  }

  void handleReply(QLocalSocket &socket) {
    while (socket.canReadLine()) {
      const QString reply = QString::fromUtf8(socket.readLine()).trimmed();
      if (reply.startsWith("ERROR")) {
        fail(reply.mid(6).trimmed());
      } else if (reply == "DONE" && state == State::WaitingObject2) {
        retryTimer.stop();
        beginConnection(State::WaitingObject3);
      } else if (reply == "DONE" && state == State::WaitingObject3) {
        retryTimer.stop();
        state = State::Idle;
      }
    }
  }

  void runTask() {
    if (state != State::Idle)
      return;
    if (minimumInput->value() > maximumInput->value()) {
      QMessageBox::warning(this, "Помилка", "Min має бути не більшим за Max.");
      return;
    }
    count = countInput->value();
    minimum = minimumInput->value();
    maximum = maximumInput->value();
    beginConnection(State::WaitingObject2);
  }

public:
  Lab6Window() {
    setWindowTitle("Lab6 - Менеджер");
    QVBoxLayout *layout = new QVBoxLayout(this);
    QFormLayout *form = new QFormLayout;

    countInput = new QSpinBox(this);
    countInput->setRange(1, 100000);
    countInput->setValue(20);

    minimumInput = new QDoubleSpinBox(this);
    minimumInput->setRange(-1e9, 1e9);
    minimumInput->setDecimals(2);

    maximumInput = new QDoubleSpinBox(this);
    maximumInput->setRange(-1e9, 1e9);
    maximumInput->setDecimals(2);
    maximumInput->setValue(100);

    form->addRow("n:", countInput);
    form->addRow("Min:", minimumInput);
    form->addRow("Max:", maximumInput);

    layout->addLayout(form);
    
    QPushButton *button = new QPushButton("Виконати", this);
    layout->addWidget(button);
    connect(button, &QPushButton::clicked, this, &Lab6Window::runTask);
    
    connect(&retryTimer, &QTimer::timeout, this, [this] {
      if (state == State::WaitingObject2 || state == State::WaitingObject3)
        tryConnect(state);
    });
    connect(&object2Socket, &QLocalSocket::connected, this, [this] {
      if (state == State::WaitingObject2)
        send(object2Socket,
             Lab6Protocol::command("GENERATE",
                                   {QString::number(count),
                                    QString::number(minimum, 'f', 2),
                                    QString::number(maximum, 'f', 2)}));
    });
    connect(&object3Socket, &QLocalSocket::connected, this, [this] {
      if (state == State::WaitingObject3)
        send(object3Socket, Lab6Protocol::command("SORT"));
    });
    connect(&object2Socket, &QLocalSocket::readyRead, this,
            [this] { handleReply(object2Socket); });
    connect(&object3Socket, &QLocalSocket::readyRead, this,
            [this] { handleReply(object3Socket); });
    connect(&object2Socket, &QLocalSocket::errorOccurred, this, [this] {
      if (state == State::WaitingObject2)
        startChild(state);
    });
    connect(&object3Socket, &QLocalSocket::errorOccurred, this, [this] {
      if (state == State::WaitingObject3)
        startChild(state);
    });
    adjustSize();
  }

protected:
  void closeEvent(QCloseEvent *event) override {
    closing = true;
    retryTimer.stop();
    if (object2Socket.state() == QLocalSocket::ConnectedState)
      send(object2Socket, Lab6Protocol::command("QUIT"));
    if (object3Socket.state() == QLocalSocket::ConnectedState)
      send(object3Socket, Lab6Protocol::command("QUIT"));
    object2Socket.disconnectFromServer();
    object3Socket.disconnectFromServer();
    event->accept();
  }
};

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  Lab6Window window;
  window.show();
  return app.exec();
}